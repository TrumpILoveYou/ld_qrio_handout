import os
import sys

##########################################这个脚本用于华为等不能拿反汇编的场景，将反汇编转换为callgraph.addr，并将函数名隐藏为数字

if('-i' not in sys.argv):
	print('Please use parameter -file filename to specify dump file!')
else:
	a=sys.argv.index('-i')
	FileDis=sys.argv[a+1]

if('-offset' not in sys.argv):
	offset=0
	print('Please use parameter -offset n to specify offset of process  or it will be set to 0!')
else:
	a=sys.argv.index('-offset')
	offset=int(sys.argv[a+1],16)

################################################################### 
num_to_name={}        #将函数名隐藏为数字，下面两个字典中的函数名实为数字
name_to_address1={}   #函数名到起始地址
name_to_address2={}   #函数名到终止地址

FileDis= rf"{sys.argv[2]}"

if '-o' in sys.argv:
	a=sys.argv.index('-o')
	FileAddr= rf"{sys.argv[a+1]}"  
else:
	FileAddr= rf"callgraph.addr"

Filedis = open(FileDis)
Fileaddr = open(FileAddr,'w')

LineTemp = Filedis.readline()
flag=0
num=0
if '-num' in sys.argv:
	a=sys.argv.index('-num')
	num=int(sys.argv[a+1])

while LineTemp: 
	if '<' in LineTemp and '>' in LineTemp:
		a=LineTemp.find('<')
		b=LineTemp.find(':')
		if a<b :
			address = int(LineTemp[:a-1],16)   #值1  本段起始地址
			name = LineTemp[a+1:b-1] #键  本段函数名
			num_to_name[num]=name
			
			name_to_address1[num]=address+offset
			
			if flag == 1:
				name_to_address2[namePre]=address+offset
			namePre=num
			flag=1
			num+=1  

	LineTempPre=LineTemp
	LineTemp=Filedis.readline()	

c=LineTempPre.find(':')
tmp1=int(LineTempPre[:c],16)+4 
name_to_address2[namePre]=tmp1
##############################################建字典
count=0
if '-num' in sys.argv:
	a=sys.argv.index('-num')
	count=int(sys.argv[a+1])

for key in name_to_address1:
	if '-hide' in sys.argv:
		Fileaddr.write(f'  Node_{count} [label="{{{key}}}",addr="{{0x{name_to_address1[key]:016x},0x{name_to_address2[key]:016x}}}"];\n')
	else:
		Fileaddr.write(f'  Node_{count} [label="{{{num_to_name[key]}}}",addr="{{0x{name_to_address1[key]:016x},0x{name_to_address2[key]:016x}}}"];\n')
	count+=1
Fileaddr.close()
Filedis.close()

if '-hide' in sys.argv:
	FileMap= rf"num2name.txt"
	filemap = open(FileMap,'w')
	for i in num_to_name:
		ret=os.popen(f'c++filt {num_to_name[i]}').read()[:-1]
		filemap.write(f'{i:<7} {ret}\n')
	filemap.close()
