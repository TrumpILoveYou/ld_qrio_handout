import os
import sys

if '-tid' in sys.argv:  #可用用-tid指定只分析哪个线程
	a=sys.argv.index('-tid')
	target_tid=sys.argv[a+1]
if '-offline' in sys.argv:   #只有在offline模式下，要从trace生成调用信息，不加此参数直接用运行时生成的call_and_insn_result.dot
	from collections import deque   #每个tid一个栈，一个全局计数器，一个函数调用信息map，调用边信息map
	tid_list=[]
	tid2stack={}
	tid2function_callinfo_map={}  #tid->字典[ 函数->列表[总支令数，次数，上一次没有子函数的时刻(指令数count)，单次最大指令数，单次最小指令数,栈-单次调用时的self指令数(用于更新单次最大最小值，用栈准确计算递归调用)] ]  #[2]元素初始值为调用时count，每当有子函数返回时更新，当栈顶元素发生子函数调用或是自身返回时更新总指令数
	tid2edge_callinfo_map={}  #tid->字典[ (父函数,子函数))->列表[总支令数，次数，单次最大指令数，单次最小指令数] ]

	Trace_file=f"call_graph_trace.txt"
	trace_file=open(Trace_file)

	LineTemp = trace_file.readline()
	while LineTemp:
		w=LineTemp.find('|')
		trace_tid=LineTemp[:w]
		if ('-tid' not in sys.argv) or ('-tid' in sys.argv and trace_tid == target_tid):#如果没用-tid指定要处理的tid就处理所有tid
			if trace_tid not in tid2stack:#新出现的tid，做初始化
				tid_list.append(trace_tid)
				stack1 = deque()    #用于维护当前调用链位置的栈
				stack1.append('0')
				stack2 = deque()    #用于维护当前调用链位置的栈
				stack2.append(0)
				tid2stack[trace_tid]=stack1
				tid2function_callinfo_map[trace_tid]={}   
				tid2function_callinfo_map[trace_tid]['0']=[0,0,0,0,100000000,stack2]  #找不到父函数的都归给0
				tid2edge_callinfo_map[trace_tid]={}

			if LineTemp[w+1]=='c':
				a=LineTemp.find(':')
				b=LineTemp.find(';')
				func_name=LineTemp[a+1:b]
				insn_count=int(LineTemp[b+1:-1])
				father_func_name=tid2stack[trace_tid][-1]

				cur_increment=insn_count-tid2function_callinfo_map[trace_tid][father_func_name][2]#发生子函数调用时只会增加父函数的单次self计数

				if func_name not in tid2function_callinfo_map[trace_tid]:
					stack2 = deque()    #用于维护当前调用链位置的栈
					stack2.append(0)
					tid2function_callinfo_map[trace_tid][func_name]=[0,1,insn_count,0,100000000,stack2]
				else:
					tid2function_callinfo_map[trace_tid][func_name][1]+=1
					tid2function_callinfo_map[trace_tid][func_name][2]=insn_count
					tid2function_callinfo_map[trace_tid][func_name][5].append(0)
				
				tid2function_callinfo_map[trace_tid][father_func_name][0]+=cur_increment
				if father_func_name == func_name:
					tid2function_callinfo_map[trace_tid][father_func_name][5][-2]+=cur_increment
				else:
					tid2function_callinfo_map[trace_tid][father_func_name][5][-1]+=cur_increment

				if len(tid2stack[trace_tid])>1: 
					grand_father_func_name=tid2stack[trace_tid][-2]
					tuple_cur=(grand_father_func_name,father_func_name)
					tid2edge_callinfo_map[trace_tid][tuple_cur][0]+=cur_increment

				tid2stack[trace_tid].append(func_name)

				tuple_cur=(father_func_name,func_name)
				if tuple_cur not in tid2edge_callinfo_map[trace_tid]:
					tid2edge_callinfo_map[trace_tid][tuple_cur]=[0,1,0,100000000]
				else:
					tid2edge_callinfo_map[trace_tid][tuple_cur][1]+=1

			else:
				if len(tid2stack[trace_tid])==1:   #目前存在着空栈仍有ret的情况，当栈大小为1时只有'0'存在，相当于空栈，跳过此ret
					continue
				a=LineTemp.find(';')
				insn_count=int(LineTemp[a+1:-1])

				func_name=tid2stack[trace_tid][-1]  #自身返回时，更新自己的总指令数
				tid2function_callinfo_map[trace_tid][func_name][0]+=insn_count-tid2function_callinfo_map[trace_tid][func_name][2]

				tid2function_callinfo_map[trace_tid][func_name][5][-1]+=insn_count-tid2function_callinfo_map[trace_tid][func_name][2]
				insn_this_time=tid2function_callinfo_map[trace_tid][func_name][5][-1]
				tid2function_callinfo_map[trace_tid][func_name][5].pop()
				tid2function_callinfo_map[trace_tid][func_name][3]=max(insn_this_time,tid2function_callinfo_map[trace_tid][func_name][3])
				tid2function_callinfo_map[trace_tid][func_name][4]=min(insn_this_time,tid2function_callinfo_map[trace_tid][func_name][4])

				tid2stack[trace_tid].pop()
				father_func_name=tid2stack[trace_tid][-1]

				tuple_cur=(father_func_name,func_name)
				tid2edge_callinfo_map[trace_tid][tuple_cur][0]+=insn_count-tid2function_callinfo_map[trace_tid][func_name][2]
				tid2edge_callinfo_map[trace_tid][tuple_cur][2]=max(insn_this_time,tid2edge_callinfo_map[trace_tid][tuple_cur][2])
				tid2edge_callinfo_map[trace_tid][tuple_cur][3]=min(insn_this_time,tid2edge_callinfo_map[trace_tid][tuple_cur][3])

				tid2function_callinfo_map[trace_tid][father_func_name][2]=insn_count ###更新父函数的  上一次没有子函数的时刻(指令数count)
		LineTemp = trace_file.readline()
	trace_file.close()

	FileDrcallgraph= r"call_and_inst_result.dot"
	Filedrcallgraph = open(FileDrcallgraph,'w')  #输出文件

	for i in tid_list:
		for j in sorted(tid2function_callinfo_map[i].items(),key=lambda x:x[1][0],reverse=True):
			if j[1][4]==100000000:
				Filedrcallgraph.write(f'{int(j[0],16):016x} time={j[1][1]} min=0 max={j[1][3]} self={j[1][0]} tid={i};\n')
			else:
				Filedrcallgraph.write(f'{int(j[0],16):016x} time={j[1][1]} min={j[1][4]} max={j[1][3]} self={j[1][0]} tid={i};\n')
	for i in tid_list:
		for j in tid2edge_callinfo_map[i].items():
			Filedrcallgraph.write(f'{int(j[0][0],16):016x} -> {int(j[0][1],16):016x} time={j[1][1]} min={j[1][3]} max={j[1][2]} self={j[1][0]} tid={i};\n')
	Filedrcallgraph.close()
##########################online和offline均以call_and_inst_result.dot作为向后传递的结果文件，因此offline预处理阶段就是将trace加工为call_and_inst_result.dot
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
###################################################################获取offset,静态链接程序设为0
if '-dis' in sys.argv:
	name_to_address1={}   #函数名到起始地址
	name_to_address2={}   #函数名到终止地址
	a=sys.argv.index('-dis')
	FileDis= rf"{sys.argv[a+1]}"  
	FileAddr= rf"callgraph.addr"
	Filedis = open(FileDis)
	Fileaddr = open(FileAddr,'w')

	LineTemp = Filedis.readline()
	flag=0
	while LineTemp: 
 		if '<' in LineTemp and '>' in LineTemp:
 			a=LineTemp.find('<')
 			b=LineTemp.find(':')
 			if a<b :
 				address = int(LineTemp[:a-1],16)   #值1  本段起始地址  
 				name = LineTemp[a+1:b-1] #键  本段函数名

 				name_to_address1[name]=address
 			
 				if flag == 1:
 					name_to_address2[namePre]=address
 				namePre=name
 				flag=1

 		LineTempPre=LineTemp
 		LineTemp=Filedis.readline()	

	c=LineTempPre.find(':')
	tmp1=int(LineTempPre[:c],16)+4
	name_to_address2[name]=tmp1

##############################################建字典
	count=0
	for key in name_to_address1:
		count+=1
		Fileaddr.write(f'  Node_{count} [label="{{{key}}}",addr="{{0x{name_to_address1[key]:016x},0x{name_to_address2[key]:016x}}}"];\n')
	Fileaddr.close()
	Filedis.close()

#############################################dis_to_addr
if '-addr' in sys.argv:
	a=sys.argv.index('-addr')
	FileAddr= rf"{sys.argv[a+1]}"  
else:
	FileAddr= rf"callgraph.addr"
FileDrcallgraph= r"call_and_inst_result.dot"
Filedrcallgraph = open(FileDrcallgraph)
tid_list=[]
Filedrcallgraph_files = []  #每个线程grep出一个dot
calldot_to_address={}  #文件映射到线程,用于后续文件命名

LineTemp = Filedrcallgraph.readline()
while LineTemp: 
 	a=LineTemp.find('tid=')
 	b=LineTemp.find(';\n')
 	KeyStr1 = LineTemp[a:b]   #键  起始地址
 	if KeyStr1 not in tid_list:
 		tid_list.append(KeyStr1)
 	LineTemp=Filedrcallgraph.readline()	
Filedrcallgraph.close()

# for i in tid_list:
# 	print(i)

if '-tid' in sys.argv:  #可用用-tid指定只分析哪个线程
	a=sys.argv.index('-tid')
	target_tid=f'tid={sys.argv[a+1]}'

for i in tid_list:
	if ('-tid' not in sys.argv) or ('-tid' in sys.argv and i == target_tid):
		os.system(f"cat call_and_inst_result.dot | grep '{i}' >call_and_inst_result-{i}.dot")
		Filedrcallgraph_files.append(f'call_and_inst_result-{i}.dot')
		calldot_to_address[f'call_and_inst_result-{i}.dot']=i
Filedrcallgraph.close()
############################################## 创建pid、tid列表 每个形成一个dot
address_to_address={}
address_to_name={}

FileRetdec= FileAddr
Fileretdec = open(FileRetdec)

LineTemp = Fileretdec.readline()
while LineTemp: 
 	if 'addr="{' in LineTemp:
 		a=LineTemp.find('{0x')
 		b=LineTemp.find('label=')
 		c=LineTemp.find('}",addr=')
 		d=LineTemp.find(',0x')
 		e=LineTemp.find('}"];')
 		KeyStr1 = int(LineTemp[a+3:d],16)+offset   #键  起始地址,在这里加上了从offset文件中获取的offset，后续不需要再处理了
 		KeyStr2 = int(LineTemp[d+3:e],16)+offset   #值1  终止地址
 		KeyStr3 = LineTemp[b+8:c] #值2  函数名
 		address_to_address[KeyStr1]=KeyStr2
 		address_to_name[KeyStr1]=KeyStr3
 	LineTemp=Fileretdec.readline()	
Fileretdec.close()
address_to_address=sorted(address_to_address.items(),reverse=True)
##############################################建字典
if '-merge' in sys.argv:
	merge_func_map={}
	Totalcount_merge=0
############################################# merge最后处理，先创建合并字典
for Filedrcallgraph_current in Filedrcallgraph_files:
	FileTmp=rf"{sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}-tmp.dot"
	print(f'processing {calldot_to_address[Filedrcallgraph_current]}')

	FileTotalInsn=rf"callgraph_total_insn_num.txt"
	Filetotalinsn = open(FileTotalInsn)
	LineTemp = Filetotalinsn.readline()
	while LineTemp: 
		if ' total=' in LineTemp:
			a=LineTemp.find(' total=')
			b=LineTemp.find('_tid=')
			if LineTemp[b+1:a] == calldot_to_address[Filedrcallgraph_current]:
				Totalcount_cur_tid=int(LineTemp[a+7:])
				if '-merge' in sys.argv:
					Totalcount_merge +=Totalcount_cur_tid
		LineTemp=Filetotalinsn.readline()
	Filetotalinsn.close()

	Filedrcallgraph = open(Filedrcallgraph_current)
	Filetmp = open(FileTmp,'w')

	LineTemp = Filedrcallgraph.readline()
	while LineTemp:
		if '->' not in LineTemp:
			KeyStr1 = int(LineTemp[0:16],16)  #地址
			a=LineTemp.find(' time=')
			b=LineTemp.find(' tid=')

			Filetmp.write('"')
			Filetmp.write(address_to_name.get(KeyStr1,f'function_{str(hex(KeyStr1))}'))
			Filetmp.write('" [label="')
			Filetmp.write(address_to_name.get(KeyStr1,f'function_{str(hex(KeyStr1))}'))
			Filetmp.write(f'{LineTemp[a:b]}"];\n')
		else:
			KeyStr1 = int(LineTemp[0:16],16)  #起
			KeyStr2 = int(LineTemp[20:36],16) #止
			a = LineTemp.find('tid=')
			KeyStr3 = LineTemp[37:a-1]
		
			Filetmp.write('"')
			Filetmp.write(address_to_name.get(KeyStr1,f'function_{str(hex(KeyStr1))}'))
			Filetmp.write('" -> "')
			Filetmp.write(address_to_name.get(KeyStr2,f'function_{str(hex(KeyStr2))}'))
			Filetmp.write(f'" [label="{KeyStr3}"];\n')
		LineTemp=Filedrcallgraph.readline()

	Filedrcallgraph.close()
	Filetmp.close()
################################################换地址为函数名
	Filetmp=open(FileTmp,'r')
	FileReformedCg=rf"{sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}-reformed.dot"
	Filereformedcg=open(FileReformedCg,'w')

	Filereformedcg.write(f'strict digraph {{\ngraph[ordering="out",overlap="false", label="Total_insn={Totalcount_cur_tid}",labelloc=t];\nnode[fontcolor="#990000"];\nedge[arrowsize=0.6,fontsize=12];\n')

	plt_flag=0
	LineTemp = Filetmp.readline()
	while LineTemp:
		if '->' in LineTemp:
			a=LineTemp.find('" -> "')
			b=LineTemp.find('" [label=')
			KeyStr_name1=LineTemp[1:a]
			KeyStr_name2=LineTemp[a+6:b]
			KeyStr_else=LineTemp[b+2:].replace(' ','\\n')

			if KeyStr_name1[:2] == '_Z':
				a=KeyStr_name1.find('@plt')
				if a!=0:
					plt_flag=1
					KeyStr_name1=KeyStr_name1[:a]
				ret=os.popen(f'c++filt {KeyStr_name1}').read()[:-1]
				if plt_flag==1:
					Filereformedcg.write(f'"{ret}@plt" -> "')
					plt_flag=0
				else:
					Filereformedcg.write(f'"{ret}" -> "')
			else:
				Filereformedcg.write('"')
				Filereformedcg.write(KeyStr_name1)
				Filereformedcg.write('" -> "')

			if KeyStr_name2[:2] == '_Z':
				a=KeyStr_name2.find('@plt')
				if a!=0:
					plt_flag=1
					KeyStr_name2=KeyStr_name2[:a]
				ret=os.popen(f'c++filt {KeyStr_name2}').read()[:-1]
				if plt_flag==1:
					Filereformedcg.write(f'{ret}@plt')
					plt_flag=0
				else:
					Filereformedcg.write(f'{ret}')
			else:
				Filereformedcg.write(KeyStr_name2)
			if '-detail' in sys.argv:  #只有有detail参数时图才显示min、max
				Filereformedcg.write(f'" {KeyStr_else}')
			else:
				a=KeyStr_else.find('min=')
				b=KeyStr_else.find('self=')
				Filereformedcg.write(f'" {KeyStr_else[:a]}{KeyStr_else[b:]}')
		else:
			a=LineTemp.find('" [label="')
			b=LineTemp.find(' time=')
			KeyStr_name1=LineTemp[1:a]
			KeyStr_else=LineTemp[b:].replace(' ','\\n')

			if KeyStr_name1[:2] == '_Z':
				a=KeyStr_name1.find('@plt')
				if a!=0:
					plt_flag=1
					KeyStr_name1=KeyStr_name1[:a]
				ret=os.popen(f'c++filt {KeyStr_name1}').read()[:-1]
				if plt_flag==1:
					Filereformedcg.write(f'"{ret}@plt" [label="{ret}@plt')
					plt_flag=0
				else:
					Filereformedcg.write(f'"{ret}" [label="{ret}')
			else:
				Filereformedcg.write('"')
				Filereformedcg.write(KeyStr_name1)
				Filereformedcg.write('" [label="')
				Filereformedcg.write(KeyStr_name1)
			if '-detail' in sys.argv:
				Filereformedcg.write(KeyStr_else)
			else:
				a=KeyStr_else.find('min=')
				b=KeyStr_else.find('self=')
				Filereformedcg.write(f'{KeyStr_else[:a]}{KeyStr_else[b:]}')
		LineTemp=Filetmp.readline()
	
	Filereformedcg.write('}\n')

	Filetmp.close()
	Filereformedcg.close()

	FileFinal=FileReformedCg   #将FileFinal向后传递
#################################################做c++函数名处理    第一阶段完全完成

#################################################开始第二阶段，各额外功能处理部分，依次为-selfrank、-show、-percent
	if '-selfrank' in sys.argv:
		if '-merge' not in sys.argv:
			FileSelfRank=rf"{sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}-selfrank.txt"
			Fileselfrank=open(FileSelfRank,'w')
			Fileselfrank.write(f'{calldot_to_address[Filedrcallgraph_current]}-total_insn_num:{Totalcount_cur_tid}\n')
			Fileselfrank.write(f'{"number":<8} {"function":<30} {"time":<10} {"percent":<10} {"insn":<8}\n')

			func_map={}#新map
			edge_num=0#统计边的总数

			a=sys.argv.index('-selfrank')
			rank_num=int(sys.argv[a+1])
			cur_num=1

			total_percent=0.0

			Filefinal=open(FileFinal,'r') #从之前已经转换为函数名的文件中读取节点的信息，存入字典，并进行排序输出
			for i in range(4):
				LineTemp = Filefinal.readline()
			
			LineTemp = Filefinal.readline()
			while LineTemp:
				if '" -> "' in LineTemp:
					edge_num+=1
				else:
					if LineTemp!="}\n":
						a=LineTemp.find('" [label="')
						b=LineTemp.find('time=')
						if '-detail' in sys.argv:
							c=LineTemp.find('min=')
						else:
							c=LineTemp.find('self=')
						d=LineTemp.find('self=')
						e=LineTemp.find('"];')

						cur_func=LineTemp[1:a]
						cur_time=int(LineTemp[b+5:c-2])
						cur_self=int(LineTemp[d+5:e])

						func_map[cur_func]=[cur_time,cur_self]

				LineTemp = Filefinal.readline()

			for i in sorted(func_map.items(),key=lambda x:x[1][1],reverse=True):
				if cur_num>rank_num:
					break
				Fileselfrank.write(f'{cur_num:<8} {i[0]:<30} {i[1][0]:<10} {i[1][1]/Totalcount_cur_tid:<10.2%} {i[1][1]:<8}\n')
				cur_num+=1
				total_percent+=i[1][1]/Totalcount_cur_tid


			Filefinal.close()
			Fileselfrank.close()
			print(f'total function num:{len(func_map)}')
			print(f'total edge num:{edge_num}')
			print(f'rank top{rank_num} total_percent:{total_percent:.2%}')
		else:
			Filefinal=open(FileFinal,'r') #从之前已经转换为函数名的文件中读取节点的信息，存入字典，并进行排序输出
			for i in range(4):
				LineTemp = Filefinal.readline()

			LineTemp = Filefinal.readline()
			while '->' not in LineTemp and LineTemp!='}\n':
				a=LineTemp.find('" [label="')
				b=LineTemp.find('time=')
				if '-detail' in sys.argv:
					c=LineTemp.find('min=')
				else:
					c=LineTemp.find('self=')
				d=LineTemp.find('self=')
				e=LineTemp.find('"];')

				cur_func=LineTemp[1:a]
				cur_time=int(LineTemp[b+5:c-2])
				cur_self=int(LineTemp[d+5:e])
				LineTemp = Filefinal.readline()

				if cur_func not in merge_func_map:
					merge_func_map[cur_func]=[cur_time,cur_self]
				else:
					merge_func_map[cur_func][0]+=cur_time
					merge_func_map[cur_func][1]+=cur_self
			Filefinal.close()
#################################################-selfrank文本输出阶段
	if '-show' in sys.argv or '-percent' in sys.argv:  #当有这两个参数在时，需要使用networkx库创建有向图帮助分析，-onlymain、-show需要筛选节点，-percent将递归函数标注为紫色
		import networkx
		G=networkx.DiGraph()

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
###############################################用每个线程的FileReformedCg建图
	if('-show' in sys.argv):
		FileShow=rf"{sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}-show.dot"
		Fileshow=open(FileShow,'w')
		Filefinal=open(FileFinal,'r')
		for i in range(4):
			LineTemp = Filefinal.readline()
			Fileshow.write(LineTemp)

		a=sys.argv.index('-show')
		fun_name=sys.argv[a+1]
		upnum=int(sys.argv[a+2])
		downnum=int(sys.argv[a+3])
		if upnum < 0 or downnum < 0:
			print('wrong upnum or downnum!')
		if not G.has_node(fun_name):
			print('wrong function_name!')
		up_visited_func_list=[fun_name]   #上下分别处理，向上找到过的函数不会继续向上找了，向上找到的函数只会继续想上找，而不记录它的子函数，向下时同理
		up_queue=[fun_name] #表示向上找的每一层的函数
		up_queue_num=1  #在只用一个队列时，要记录每一层有多少函数
		down_visited_func_list=[fun_name]
		down_queue=[fun_name]
		down_queue_num=1
		show_func_list=[fun_name]#找到的所有函数的列表

		while upnum:  #向上找的层数
			next_up_queue_num=0
			for i in range(up_queue_num):
				func=up_queue[i]
				for predecessor_func in G.predecessors(func):
					if predecessor_func not in up_visited_func_list:
						up_visited_func_list.append(predecessor_func)
						up_queue.append(predecessor_func)
						next_up_queue_num+=1
					if predecessor_func not in show_func_list:
						show_func_list.append(predecessor_func)
			for i in range(up_queue_num):#把上一层的删掉
				del(up_queue[0])
			upnum-=1
			up_queue_num=next_up_queue_num
			if up_queue_num==0:
				break

		while downnum:  #向下找的层数
			next_down_queue_num=0
			for i in range(down_queue_num):
				func=down_queue[i]
				for successor_func in G.successors(func):
					if successor_func not in down_visited_func_list:
						down_visited_func_list.append(successor_func)
						down_queue.append(successor_func)
						next_down_queue_num+=1
					if successor_func not in show_func_list:
						show_func_list.append(successor_func)
			for i in range(down_queue_num):
				del(down_queue[0])
			downnum-=1
			down_queue_num=next_down_queue_num
			if down_queue_num==0:
				break
		
		#需要显示的函数都找出来了，接下来读输入文件，相应的节点保留，对于边，只保留两个节点都需要显示的
		LineTemp = Filefinal.readline()
		while LineTemp:
			if '" -> "' not in LineTemp:
				a=LineTemp.find('" [label="')
				if LineTemp!="}\n":
					KeyStr1=LineTemp[1:a]
					if KeyStr1 in show_func_list:
						Fileshow.write(LineTemp)
			else:
				a=LineTemp.find('" -> "')
				b=LineTemp.find('" [label=')
				KeyStr1=LineTemp[1:a]
				KeyStr2=LineTemp[a+6:b]
				if KeyStr1 in show_func_list and KeyStr2 in show_func_list:
					Fileshow.write(LineTemp)
			LineTemp = Filefinal.readline()
		Fileshow.write('}\n')

		Fileshow.close()
		Filefinal.close()
		FileFinal=FileShow
###############################################-show处理阶段
	mincolor = (2.0/3.0, 0.80, 0.25) # dark blue
	maxcolor = (0.0, 1.0, 0.5) # satured red

	def color(weight):
	    weight = min(max(weight, 0.0), 1.0)
	    global mincolor
	    global maxcolor
	    hmin, smin, lmin = mincolor
	    hmax, smax, lmax = maxcolor
	        
	    h = hmin + weight*(hmax - hmin)
	    s = smin + weight*(smax - smin)
	    l = lmin + weight*(lmax - lmin)
	    
	    rgbcolor=hsl_to_rgb(h, s, l)
	    return rgb2hex(rgbcolor) 

	def hsl_to_rgb(h, s, l):
	    #Convert a color from HSL color-model to RGB.
	    #See also:
	    #- http://www.w3.org/TR/css3-color/#hsl-color
	    h = h % 1.0
	    s = min(max(s, 0.0), 1.0)
	    l = min(max(l, 0.0), 1.0)

	    if l <= 0.5:
	        m2 = l*(s + 1.0)
	    else:
	        m2 = l + s - l*s
	    m1 = l*2.0 - m2
	    r1 = _hue_to_rgb(m1, m2, h + 1.0/3.0)
	    g1 = _hue_to_rgb(m1, m2, h)
	    b1 = _hue_to_rgb(m1, m2, h - 1.0/3.0)

	    return (r1, g1, b1)

	def _hue_to_rgb(m1, m2, h):
	    if h < 0.0:
	        h += 1.0
	    elif h > 1.0:
	        h -= 1.0
	    if h*6 < 1.0:
	        return m1 + (m2 - m1)*h*6.0
	    elif h*2 < 1.0:
	        return m2
	    elif h*3 < 2.0:
	        return m1 + (m2 - m1)*(2.0/3.0 - h)*6.0
	    else:
	        return m1

	def rgb2hex(rgbcolor):#返回结果现在是十进制值
	    r, g, b = rgbcolor
	    result = (int(r*255+0.5)<<16) + (int(g*255+0.5)<< 8) + int(b*255+0.5)
	    #return hex(result)
	    return result
#############################################颜色算法相关函数
	if '-percent' in sys.argv:
		recursion_function_list=[]   #哪些函数是递归相关函数需要标为紫色
		for i in networkx.simple_cycles(G):   #以列表的形式返回有向图中的环，每个环是一个列表
			for j in i:
				if j not in recursion_function_list:
					recursion_function_list.append(j)
		FilePercentageCg=rf"{sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}-percentage.dot"
		FilePercentagecg=open(FilePercentageCg,'w')

		Filefinal=open(FileFinal,'r')
		for i in range(4):
			LineTemp = Filefinal.readline()
		FilePercentagecg.write('strict digraph {\n')
		FilePercentagecg.write(f'graph [fontname=Arial, nodesep=0.125, ranksep=0.25 , label="Total_insn={Totalcount_cur_tid}",labelloc=t];\n')
		FilePercentagecg.write('node [fontcolor=white, fontname=Arial, height=0, shape=box, style=filled, width=0];\n')
		FilePercentagecg.write('edge [fontname=Arial];\n')

		LineTemp = Filefinal.readline()
		while LineTemp:
			if '" -> "' not in LineTemp:
				a=LineTemp.find('self=')
				b=LineTemp.find('"];')
				c=LineTemp.find('" [label="')
				if LineTemp!="}\n":
					KeyStr1=int(LineTemp[a+5:b],10)
					FilePercentagecg.write(LineTemp[:a+5])
					curpercent=KeyStr1/Totalcount_cur_tid
					func_name=LineTemp[1:c]
					if func_name in recursion_function_list:
						FilePercentagecg.write(f'{curpercent:.2%}",color="#8a2be2"];\n')#是递归函数的标记为紫色
					else:
						FilePercentagecg.write(f'{curpercent:.2%}",color="#{color(curpercent):06x}"];\n')
			else:
				a=LineTemp.find('self=')
				b=LineTemp.find('"];')
				KeyStr1=int(LineTemp[a+5:b],10)
				curpercent=KeyStr1/Totalcount_cur_tid
				c=LineTemp.find('" -> "')
				d=LineTemp.find('" [label="')
				func_name1=LineTemp[1:c]
				func_name2=LineTemp[c+6:d]

				FilePercentagecg.write(LineTemp[:a+5])
				if func_name1 in recursion_function_list and func_name2 in recursion_function_list:
					FilePercentagecg.write(f'{curpercent:.2%}",fontcolor="#8a2be2",color="#8a2be2"];\n')
				else:
					FilePercentagecg.write(f'{curpercent:.2%}",fontcolor="#{color(curpercent):06x}",color="#{color(curpercent):06x}"];\n')
			LineTemp = Filefinal.readline()
		FilePercentagecg.write('}\n')

		FilePercentagecg.close()
		Filefinal.close()
		FileFinal=FilePercentageCg
###############################################-percent处理阶段
	if('-nograph' not in sys.argv):
		print(rf'Printing {sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}.svg ...')
		os.system(rf'dot -Tsvg {FileFinal} -o {sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}.svg')
		#print(rf'dot -Tsvg {FileFinal} -o {sys.argv[1]}-{calldot_to_address[Filedrcallgraph_current]}.svg')
	os.system(rf'rm {FileTmp}')
	#os.system(rf"rm {FileReformedCg}")    不再删除FileReformedCg，可用于递归环检测脚本进行静态分析
	os.system(rf"rm {Filedrcallgraph_current}")

	if('-percent'in sys.argv):
		os.system(rf'rm {FilePercentageCg}')
	if('-show'in sys.argv):
		os.system(rf'rm {FileShow}')
###############################################进入后处理阶段，作图，并且将所有中间文件删除
if '-merge' in sys.argv:
	if '-selfrank' not in sys.argv:
		print('-merge must use with -selfrank')
	FileMergeSelfRank=rf"{sys.argv[1]}-mergeselfrank.txt"
	Filemergeselfrank=open(FileMergeSelfRank,'w')
	Filemergeselfrank.write(f'total_insn_num:{Totalcount_merge}\n')
	Filemergeselfrank.write(f'{"number":<8} {"function":<30} {"time":<10} {"percent":<10} {"insn":<8}\n')

	a=sys.argv.index('-selfrank')
	rank_num=int(sys.argv[a+1])
	cur_num=1

	for i in sorted(merge_func_map.items(),key=lambda x:x[1][1],reverse=True):
		if cur_num>rank_num:
			break
		Filemergeselfrank.write(f'{cur_num:<8} {i[0]:<30} {i[1][0]:<10} {i[1][1]/Totalcount_merge:<10.2%} {i[1][1]:<8}\n')
		cur_num+=1
	Filemergeselfrank.close()
###############################################-merge处理阶段
