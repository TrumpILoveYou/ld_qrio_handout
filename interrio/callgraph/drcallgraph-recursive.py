import os
import sys

#使用此脚本分析递归环的前置条件  
#已有 1.trace文件call_graph_trace.txt   2. 已将地址翻译为函数名并进行了重整的统计结果  xx-reformed.dot  3.用户名字典
#用法  python3 drcallgraph-recursive.py target_process -tid target_tid

if '-tid' in sys.argv:  #可用用-tid指定只分析哪个线程
	a=sys.argv.index('-tid')
	target_tid=sys.argv[a+1]
else:
	print('must use -tid to specify a target_tid!')
#########################################################

import networkx
G=networkx.DiGraph()


FileReformedCg=rf"{sys.argv[1]}-tid={target_tid}-reformed.dot"
Filereformedcg=open(FileReformedCg)
LineTemp = Filereformedcg.readline()
while LineTemp: 
	if ' -> ' in LineTemp:#边
		a=LineTemp.find('" -> "')
		b=LineTemp.find('" [label=')
		KeyStr1 = LineTemp[1:a] #起始地址
		KeyStr2 = LineTemp[a+6:b] #终止地址
		G.add_node(KeyStr1)
		G.add_node(KeyStr2)
		G.add_edge(KeyStr1,KeyStr2)
	else:#节点
		a=LineTemp.find('" [label="')
		if a>0:   #有几行=0的不是函数
			KeyStr1 = LineTemp[1:a]
			if not G.has_node(KeyStr1):
				G.add_node(KeyStr1)
	LineTemp=Filereformedcg.readline()	
Filereformedcg.close()

recursion_function_list=[]   #哪些函数是递归相关函数需要标为紫色
for i in networkx.simple_cycles(G):   #以列表的形式返回有向图中的环，每个环是一个列表
	for j in i:
		if j not in recursion_function_list:
			recursion_function_list.append(j)

#for i in recursion_function_list:
	#print(i)
######################################################### 第一步，静态分析找出哪些是递归函数

FileAddr= rf"callgraph.addr"

address_to_name={}
name_to_address={}
Fileaddr = open(FileAddr)

LineTemp = Fileaddr.readline()
while LineTemp: 
 	if 'addr="{' in LineTemp:
 		a=LineTemp.find('{0x')
 		b=LineTemp.find('label=')
 		c=LineTemp.find('}",addr=')
 		d=LineTemp.find(',0x')
 		e=LineTemp.find('}"];')
 		KeyStr1 = int(LineTemp[a+3:d],16)   #键  起始地址,在这里加上了从offset文件中获取的offset，后续不需要再处理了
 		KeyStr3 = LineTemp[b+8:c] #值2  函数名
 		address_to_name[f'{KeyStr1}']=KeyStr3
 		name_to_address[KeyStr3]=KeyStr1
 	LineTemp=Fileaddr.readline()	
Fileaddr.close()


#找出递归函数的地址表示，并用列表保存
recursion_addr_list=[]
for i in recursion_function_list:
	recursion_addr_list.append(name_to_address[i])

#for i in recursion_addr_list:
	#print(i)

######################################################### 第二步，从"callgraph.addr"中读取并创建字典
from collections import deque
call_stack=deque() 
cur_loop_stack=deque()  #记录并隔离递归环的栈,空元素定义为'-'，每个元素为A->B的字符串，不包含重复元素
cur_element_stack=deque()  #维护当前环所含元素，用于判断当前元素是否是环开头元素,空元素定义为空列表[]，可包含重复元素

loop_map={} #统计记录的loop出现的次数

Trace_file=f"call_graph_trace.txt"
trace_file=open(Trace_file)

LineTemp = trace_file.readline()
while LineTemp:
	w=LineTemp.find('|')
	trace_tid=LineTemp[:w]
	if trace_tid == target_tid:#
		if LineTemp[w+1]=='c':  #调用
			a=LineTemp.find(':')
			b=LineTemp.find(';')

			func_name=int(LineTemp[a+1:b],16)
			father_name=0
			if len(cur_loop_stack)>0:
				father_name=call_stack[-1]
			tuple_name=f'{father_name}->{func_name}'

			if func_name in recursion_addr_list:
				if len(cur_loop_stack)==0 or cur_loop_stack[-1][0]=='-':
					cur_loop_stack.append([f'{func_name}'])
					cur_element_stack.append([func_name])
				else:
					if '->' not in cur_loop_stack[-1][0]:
						cur_loop_stack[-1][0]=tuple_name
					else:
						if tuple_name not in cur_loop_stack[-1]:  #不记录重复路径
							cur_loop_stack[-1].append(tuple_name)
					cur_element_stack[-1].append(func_name)
				
			else:
				cur_loop_stack.append(['-'])
				cur_element_stack.append([])

			call_stack.append(func_name)

		else:   #返回
		 	func_name=call_stack[-1]
		 	call_stack.pop()
		 	if len(cur_element_stack[-1])==0:
		 		cur_element_stack.pop()
		 		cur_loop_stack.pop()
		 	else:
		 		del cur_element_stack[-1][-1]
		 		if len(cur_element_stack[-1])==0: #删除完元素归零，表明递归环的第一个元素已经退出
		 			cur_loop=cur_loop_stack[-1][:]
		 			cur_loop.sort()
		 			cur_loop_stack.pop()

		 			cur_loop_str=''  #将列表字符串化后再进行映射
		 			for i in cur_loop:
		 				cur_loop_str+=i+'|'

		 			if cur_loop_str not in loop_map:
		 				loop_map[cur_loop_str]=1
		 			else:
		 				loop_map[cur_loop_str]+=1
	LineTemp = trace_file.readline()

#print(loop_map)
######################################################### 第三步，动态分析找出递归环
loop_map2={} #统计通过检验的loop出现的次数

for i in loop_map:
	if '->' not in i:  #只有一个节点，并且没有调用自身，必无环
		continue

	#print(i)
	G=networkx.DiGraph()
	for j in i.split('|'):
		if j == '':
			continue

		a=j.find('->')
		KeyStr1=j[:a]
		KeyStr2=j[a+2:]
		G.add_node(KeyStr1)
		G.add_node(KeyStr2)
		G.add_edge(KeyStr1,KeyStr2)

	if len( list(networkx.simple_cycles(G)) )>0:   #以列表的形式返回有向图中的环，每个环是一个列表
		loop_map2[i]=loop_map[i]	

#print(loop_map2)
######################################################### 第四步，对map中的每个环进行判定，因为有时递归函数并未展现出递归性
name_list=""  #用与于合并命令的字符串
rm_list=[] #用于删除命令的列表
num=0

for i in loop_map2:

	num+=1
	PatternTmp=rf"Recursive-Loop-{num}.dot"
	rm_list.append(PatternTmp)
	name_list+=f'Recursive-Loop-{num}.pdf'+' '
	rm_list.append(f'Recursive-Loop-{num}.pdf')
	patterntmp=open(PatternTmp,'w')

	patterntmp.write('strict digraph {\n')
	patterntmp.write(f'graph[ordering="out",overlap="false",label="Loop-{num}occur-num={loop_map2[i]}",labelloc=t];\n')
	patterntmp.write('edge[arrowsize=0.6,fontsize=12];\n')

	for j in i.split('|'):
		if j == '':
			continue

		a=j.find('->')
		KeyStr1=j[:a]
		func_name1=address_to_name.get(KeyStr1,f'function_{str(hex(int(KeyStr1)))}')

		KeyStr2=j[a+2:]
		func_name2=address_to_name.get(KeyStr2,f'function_{str(hex(int(KeyStr2)))}')

		#print(f'{func_name1}->{func_name2}')
		patterntmp.write(f'"{func_name1}"->"{func_name2}"')

	patterntmp.write('}')
	patterntmp.close()

	os.system(rf'dot -Tpdf {PatternTmp} -o Recursive-Loop-{num}.pdf')

os.system(rf'pdftk {name_list}output Recursive-Loop.pdf')
for i in rm_list:
	os.system(rf'rm {i}')
######################################################### 第五步，对map中的每个环转换回函数名，并绘图