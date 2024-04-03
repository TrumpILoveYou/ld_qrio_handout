import os
import sys

if('-c' not in sys.argv):
	print('Please use parameter -c n to specify channel!')
else:
	a=sys.argv.index('-c')
	channel_num=int(sys.argv[a+1])
home=os.getenv('HOME')
Offset_file=home+f'/qr/{channel_num}/dynamic_link_offset.txt'
offset_file = open(Offset_file)
LineTemp = offset_file.readline()[:-1]
offset = int(LineTemp,base=16)
if offset==0x400000 or offset==0x20000000:
	offset=0

if('-tid' not in sys.argv):
	print('Please use parameter -tid n to specify thread_id!')
else:
	a=sys.argv.index('-tid')
	target_tid=sys.argv[a+1]
#os.system(f"grep 'tid={target_tid}' call_pattern_trace.txt| awk 'BEGIN {{FS=\"|\"}} {{print $2}}'  >  call_pattern_trace-tid={target_tid}.txt")

if('-f' not in sys.argv and '-addr' not in sys.argv):
	print('Please use parameter -f fuction_name or -addr fuction_address to specify fuction!')
else:
	if '-f' in sys.argv:
		a=sys.argv.index('-f')
		target_function=sys.argv[a+1]
	if '-addr' in sys.argv:
		a=sys.argv.index('-addr')
		target_function_addr=int(sys.argv[a+1],16)
		print(f"target_function_addr:{target_function_addr:x}")

FileAddr= "callgraph.addr"
Fileaddr = open(FileAddr)

address_to_address={}
address_to_name={}

LineTemp = Fileaddr.readline()
while LineTemp: 
	if 'addr="{' in LineTemp:
		a=LineTemp.find('{0x')
		b=LineTemp.find('label=')
		c=LineTemp.find('}",addr=')
		d=LineTemp.find(',0x')
		KeyStr1 = int(LineTemp[a+3:d],16)   #键  起始地址
		KeyStr2 = int(LineTemp[d+3:-5],16) #值1  终止地址
		KeyStr3 = LineTemp[b+8:c] #值2  函数名
		if '-f' in sys.argv:
			if KeyStr3 == target_function:
 				target_function_addr=KeyStr1
		address_to_address[KeyStr1]=KeyStr2
		address_to_name[KeyStr1]=KeyStr3
	LineTemp=Fileaddr.readline()	
Fileaddr.close()

if '-addr' in sys.argv:
	target_function=address_to_name.get(target_function_addr,f"function_{target_function_addr:x}")
	print(target_function)
################################################################建字典
def serialize(cur_pattern):
	res_string=''
	for i in cur_pattern:
		res_string+=str(i[0])+'-'+str(i[1])+':'+str(current_pattern_calltime_map[i])+'|'
	return res_string

#distinct pattern列表：   列表[列表[元组]]
distinct_patterns=[]
#distinct pattern次数字典：   字典[列表[元组]]
distinct_pattern_map={}
#列表[元组]  每一次   对列表先排序后与每个distinct pattern比较
distinct_name_pattern_map={}
#把地址换成函数后的字典
current_pattern=[]

#记录current_pattern中每个call的次数的字典
current_pattern_calltime_map={}

from collections import deque
stack = deque()    #用于维护当前调用链位置的栈
stack.append(99999999)
#item=stack[-1]
#stack.pop()

Trace_file=f"call_graph_trace.txt"
trace_file=open(Trace_file)

distinct_flag=1
start_flag=0 #in a pattern
depth=0

LineTemp = trace_file.readline()
while LineTemp:
	w=LineTemp.find('|')
	trace_tid=LineTemp[:w]
	if trace_tid == target_tid:#

		if start_flag==0:   #还在等待目标函数被调用
		 	if LineTemp[w+1]=='c':
		 		x=LineTemp.find(';')
		 		end_address = int(LineTemp[w+3:x],16)

		 		if end_address == target_function_addr:
		 			start_flag=1
		 			start_address = stack[-1]
		 			tuple_tmp=(start_address,end_address)
		 			current_pattern.append(tuple_tmp)
		 			current_pattern_calltime_map[tuple_tmp]=1
		 			depth+=1
		 		stack.append(end_address)
		 	else:
		 		stack.pop()
		else:   #目标函数被调用 记录路径并等待返回
			if LineTemp[w+1]=='c':
				depth+=1
				x=LineTemp.find(';')
				end_address = int(LineTemp[w+3:x],16)
				start_address = stack[-1]
				tuple_tmp=(start_address,end_address)
				if tuple_tmp not in current_pattern:
					current_pattern.append(tuple_tmp)
					current_pattern_calltime_map[tuple_tmp]=1
				else:
					current_pattern_calltime_map[tuple_tmp]+=1
				stack.append(end_address)
			else:
				depth-=1
				if depth==0:
					tmp_element=serialize(current_pattern)
					#current_pattern.sort()    #不sort之后 列表中的顺序即代表该分支第一次出现时的顺序   abc和acb将表示两种不同的pattern
					for distinct_element in distinct_patterns:  ###############检查这种pattern之前是否出现过并计数
						if distinct_element == tmp_element:
							distinct_pattern_map[tmp_element[:]]+=1	
							distinct_flag=0
							break;
					if distinct_flag == 1:
						distinct_patterns.append(tmp_element[:])
						distinct_pattern_map[tmp_element[:]]=1
					else:
						distinct_flag = 1
					start_flag=0
					current_pattern_calltime_map.clear();
					current_pattern.clear()
				stack.pop()
	LineTemp=trace_file.readline()
trace_file.close()

#####################################################已经建成了独特pattern到数量的映射，但地址还需要函数名，而且可能有重复
distinct_name_map_element=''
for distinct_map_element in distinct_pattern_map:
	for once_call in distinct_map_element.split('|')[:-1]:
		a=once_call.find('-')
		b=once_call.find(':')
		KeyStr1 = once_call[0:a]  #起
		KeyStr1=int(KeyStr1,base=10)-offset
		KeyStr2 = once_call[a+1:b] #止
		KeyStr2=int(KeyStr2,base=10)-offset
		KeyStr3 = once_call[b:]  #次数

		mykey=0
		for i in sorted(address_to_address,reverse=True):
			if(KeyStr1>=i):   #大与等于某一段函数的起始地址
				if(KeyStr1<=address_to_address[i]):  #并且小于这段的终止地址
					mykey=i
					break
		if(mykey==0):#失败    必要时调试打开print
			distinct_name_map_element+=f'function_{KeyStr1:x}'
		else:
			#distinct_name_map_element+=f'{address_to_name[mykey]}'
			distinct_name_map_element+=f'{address_to_name.get(mykey,f"function_{KeyStr1:x}")}'
		distinct_name_map_element+=f'-{address_to_name.get(KeyStr2,f"function_{KeyStr2:x}")}{KeyStr3}|'

	if distinct_name_map_element not in distinct_name_pattern_map:
		distinct_name_pattern_map[distinct_name_map_element[:]]= distinct_pattern_map[distinct_map_element]
	else:
		distinct_name_pattern_map[distinct_name_map_element[:]]+= distinct_pattern_map[distinct_map_element]
	distinct_name_map_element=''

distinct_pattern_num=len(distinct_name_pattern_map)
print(f'distinct_pattern_num={len(distinct_name_pattern_map)}')
#print(distinct_name_pattern_map)
#####################################################新字典已经建好
shared_function_call_map={}
shared_function_call=[]    

for distinct_name_map_element in distinct_name_pattern_map:
	for once_call in distinct_name_map_element.split('|')[:-1]:
		if once_call in shared_function_call_map:
			shared_function_call_map[once_call]+=1
		else:
			shared_function_call_map[once_call]=1

for shared_function_call_map_element in shared_function_call_map:   #通过出现次数判断，与distinct_pattern_num数量相同的才是所有共有的
	if shared_function_call_map[shared_function_call_map_element] == distinct_pattern_num:
		a=shared_function_call_map_element.find(':')
		caller_callee=shared_function_call_map_element[:a]
		shared_function_call.append(caller_callee)

#print('shared_function_call')
#print(shared_function_call)
#####################################################找出各个pattern之间的公有路径
name_list=""  #用与于合并命令的字符串
rm_list=[] #用于删除命令的列表
num=0
for distinct_name_map_element in distinct_name_pattern_map:
	num+=1
	PatternTmp=rf"{target_function}-pattern-{num}.dot"
	rm_list.append(PatternTmp)
	patternTmp=open(PatternTmp,'w')

	patternTmp.write('strict digraph {\n')
	patternTmp.write(f'graph[ordering="out",overlap="false",label="pattern-{num}出现次数={distinct_name_pattern_map[distinct_name_map_element]}",labelloc=t];\n')
	patternTmp.write('edge[arrowsize=0.6,fontsize=12];\n')

	for once_call in distinct_name_map_element.split('|')[:-1]:
		a=once_call.find('-')
		b=once_call.find(':')
		patternTmp.write(f'"{once_call[:a]}" -> "{once_call[a+1:b]}" [label="time={once_call[b+1:]}"]')
		if once_call[:b] in shared_function_call:
			patternTmp.write(f' [color=red];\n')
		else:
			patternTmp.write(f';\n')

	patternTmp.write('}')
	patternTmp.close()
	os.system(rf'dot -Tpdf {PatternTmp} -o {target_function}-pattern-{num}.pdf')
	name_list+=f'{target_function}-pattern-{num}.pdf'+' '
	rm_list.append(f'{target_function}-pattern-{num}.pdf')

print(f'printing {target_function}-pattern.pdf...')
#os.system(rf'pdfunite {name_list}{target_function}-pattern.pdf')
#print(rf'pdftk {name_list}{target_function}-pattern.pdf')
os.system(rf'pdftk {name_list}output {target_function}-pattern.pdf')
for i in rm_list:
	os.system(rf'rm {i}')
#####################################################将新字典元素打印到dot文件,每个pattern是一个图，再将所有图合并

