import os
import sys

##########################################这个脚本用于合并字典文件
if('-i' not in sys.argv):
	print('Please use parameter -i filename1 filename2 ... to specify addr files!')
else:
	a=sys.argv.index('-i')
	FileAddrfiles=[]
	for i in sys.argv[a+1:]:
		if i=='-o':
			break
		FileAddrfiles.append(i)
#print(FileAddrfiles)

if('-o' not in sys.argv):
	FileOut= "callgraph.addr"  
else:
	a=sys.argv.index('-o')
	FileOut= rf"{sys.argv[a+1]}"  

Fileout=open(FileOut,'w')
################################################################### 
count=0
for FileAddrfile in FileAddrfiles:
	Fileaddrfile=open(FileAddrfile,'r')
	LineTemp = Fileaddrfile.readline()
	while LineTemp: 
		a=LineTemp.find('Node_')
		b=LineTemp.find(' [label=')

		Fileout.write(LineTemp[:a+5])
		Fileout.write(f'{count}')
		Fileout.write(LineTemp[b:])
		LineTemp=Fileaddrfile.readline()
		count+=1	
	Fileaddrfile.close()
Fileout.close()