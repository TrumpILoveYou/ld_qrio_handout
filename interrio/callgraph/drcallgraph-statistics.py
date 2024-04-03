import os
import sys

##################这个脚本用来统计需要从trace中读取的统计信息，如运行时最大栈深度，某个地址的函数的平均、最大最小调用栈深度，平均深度有问题


if('-tid' not in sys.argv):
	print('Please use parameter -tid n to specify thread_id!')
else:
	a=sys.argv.index('-tid')
	target_tid=sys.argv[a+1]
if('-addr' in sys.argv):
	a=sys.argv.index('-addr')  #用来指定某个函数 统计它的相关信息
	target_func=sys.argv[a+1]
	target_func_call_time=0
	target_func_total_depth=0
	target_func_avg_depth=0
	target_func_min_depth=99999999999
	target_func_max_depth=0

from collections import deque
stack = deque()    #用于维护当前调用链位置的栈
stack.append(99999999)


Trace_file=f"call_graph_trace.txt"
trace_file=open(Trace_file)
depth=0
max_depth=0

LineTemp = trace_file.readline()
while LineTemp:
	w=LineTemp.find('|')
	trace_tid=LineTemp[:w]
	if trace_tid == target_tid:#
		if LineTemp[w+1]=='c':
			depth+=1
			if depth>max_depth:
				max_depth=depth
			if '-addr' in sys.argv:
				a=LineTemp.find(':')
				b=LineTemp.find(';')
				func_name=LineTemp[a+1:b]
				if func_name==target_func:
					target_func_call_time+=1
					target_func_total_depth+=depth
					target_func_min_depth=min(target_func_min_depth,depth)
					target_func_max_depth=max(target_func_max_depth,depth)
		else:
		 	if depth:
		 		depth-=1
	LineTemp=trace_file.readline()
trace_file.close()

print(f"tid:{target_tid}  max_depth={max_depth}")
print(f"target_func:{target_func} call_time={target_func_call_time} total_depth={target_func_total_depth} avg_depth={target_func_total_depth/target_func_call_time:.2} min_depth={target_func_min_depth} max={target_func_max_depth}")