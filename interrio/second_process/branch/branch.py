import sys
from collections import defaultdict
name_to_num_unconditional={}
name_to_num_conditional={}

FileDis= rf"{sys.argv[1]}"
Filedis = open(FileDis)
print('Jump judge tool process results: ')
print('Branch count :')
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
a=LineTemp.find('total')
total_branch = int(LineTemp[:a-1].strip())
print('\ttotal branches :',total_branch)
unconditional_branch = 0
conditional_branch = 0
for i in range (0,5):
	LineTemp = Filedis.readline()
	a=LineTemp.find('total')
	unconditional_branch += int(LineTemp[:a-1].strip())
	name = LineTemp[a+6:-1].strip()
	name_to_num_unconditional[name] = int(LineTemp[:a-1].strip())

for i in range (0,5):
	LineTemp = Filedis.readline()
	a=LineTemp.find('total')
	conditional_branch += int(LineTemp[:a-1].strip())
	name = LineTemp[a+6:-1].strip()
	name_to_num_conditional[name] = int(LineTemp[:a-1].strip())
total_call_ret = name_to_num_unconditional['ret']+name_to_num_unconditional['bl']+name_to_num_unconditional['blr']
print('Branch proportion :')
print('\tConditional branch ratio: ',round(conditional_branch/total_branch*100,2),'%',sep='')
print('\tUnconditional branch ratio: ',round((unconditional_branch-total_call_ret)/total_branch*100,2),'%',sep='')
print('\tCall and Return ratio: ',round(total_call_ret/total_branch*100,2),'%',sep='')
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
a=LineTemp.find('total')
forwardBranch_ratio = float(LineTemp[:a-2].strip())
print('Branch direction proportion:')
print('\tForwardBranch ratio: ',forwardBranch_ratio,'%',sep='')
print('\tBackwardBranch ratio: ',(100-forwardBranch_ratio),'%',sep='')
print('Branch taken count : ')

Filedis.close()

FileDis_pc= rf"{sys.argv[2]}"
FileDis_pc = open(FileDis_pc)
LineTemp = FileDis_pc.readline()
src_pc_ls=[]
des_pc_ls=[]
branch_opc_ls=[]
distance_ls=[]
total_taken = 0
total_not_taken = 0
while LineTemp and 'finish' not in LineTemp:
	a = LineTemp.find(':')
	b = LineTemp.find('-')
	c = LineTemp.find('T')
	src_pc_ls.append(int(LineTemp[:a].strip(),16))
	des_pc_ls.append(int(LineTemp[a+1:b].strip(),16))
	branch_opc_ls.append(int(LineTemp[b+1:c].strip()))
	LineTemp = FileDis_pc.readline()
ls_len = len(src_pc_ls)
dis_count = 0
#print('ls_len = ',ls_len)


b_src_dic = defaultdict(list)
b_des_set=set()
b_des_dic = {}
b_src_count = 0
b_des_count = 0
b_taken = 0
b_not_taken = 0
b_dis_count = 0
b_distance_ls=[]

br_src_dic = defaultdict(list)
br_des_set=set()
br_des_dic = {}
br_src_count = 0
br_des_count = 0
br_taken = 0
br_not_taken = 0
br_dis_count = 0
br_distance_ls=[]

bcond_src_dic = defaultdict(list)
bcond_des_set=set()
bcond_des_dic = {}
bcond_src_count = 0
bcond_des_count = 0
bcond_taken = 0
bcond_not_taken = 0
bcond_dis_count = 0
bcond_distance_ls=[]

cbnz_src_dic = defaultdict(list)
cbnz_des_set=set()
cbnz_des_dic = {}
cbnz_src_count = 0
cbnz_des_count = 0
cbnz_taken = 0
cbnz_not_taken = 0
cbnz_dis_count = 0
cbnz_distance_ls=[]

cbz_src_dic = defaultdict(list)
cbz_des_set=set()
cbz_des_dic = {}
cbz_src_count = 0
cbz_des_count = 0
cbz_taken = 0
cbz_not_taken = 0
cbz_dis_count = 0
cbz_distance_ls=[]

tbz_src_dic = defaultdict(list)
tbz_des_set=set()
tbz_des_dic = {}
tbz_src_count = 0
tbz_des_count = 0
tbz_taken = 0
tbz_not_taken = 0
tbz_dis_count = 0
tbz_distance_ls=[]

tbnz_src_dic = defaultdict(list)
tbnz_des_set=set()
tbnz_des_dic = {}
tbnz_src_count = 0
tbnz_des_count = 0
tbnz_taken = 0
tbnz_not_taken = 0
tbnz_dis_count = 0
tbnz_distance_ls=[]

for i in range (0,ls_len):
	#print('%#x' % src_pc_ls[i],':','%#x' % des_pc_ls[i] ,'-',branch_opc_ls[i])
	if ( branch_opc_ls[i] == 16 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		b_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		b_des_set.add(des_pc_ls[i])
		b_des_count += 1
		if des_pc_ls[i] not in b_des_dic:
			b_des_dic[des_pc_ls[i]] = 1
		else:
			b_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 17 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		if (dis == 1):
			total_not_taken += 1
		else:
			total_taken += 1
		bcond_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		bcond_des_set.add(des_pc_ls[i])
		bcond_des_count += 1
		if des_pc_ls[i] not in bcond_des_dic:
			bcond_des_dic[des_pc_ls[i]] = 1
		else:
			bcond_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 25 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		br_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		br_des_set.add(des_pc_ls[i])
		br_des_count += 1
		if des_pc_ls[i] not in br_des_dic:
			br_des_dic[des_pc_ls[i]] = 1
		else:
			br_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 44 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		if (dis == 1):
			total_not_taken += 1
		else:
			total_taken += 1
		cbnz_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		cbnz_des_set.add(des_pc_ls[i])
		cbnz_des_count += 1
		if des_pc_ls[i] not in cbnz_des_dic:
			cbnz_des_dic[des_pc_ls[i]] = 1
		else:
			cbnz_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 45 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		if (dis == 1):
			total_not_taken += 1
		else:
			total_taken += 1
		cbz_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		cbz_des_set.add(des_pc_ls[i])
		cbz_des_count += 1
		if des_pc_ls[i] not in cbz_des_dic:
			cbz_des_dic[des_pc_ls[i]] = 1
		else:
			cbz_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 383 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		if (dis == 1):
			total_not_taken += 1
		else:
			total_taken += 1
		tbnz_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		tbnz_des_set.add(des_pc_ls[i])
		tbnz_des_count += 1
		if des_pc_ls[i] not in tbnz_des_dic:
			tbnz_des_dic[des_pc_ls[i]] = 1
		else:
			tbnz_des_dic[des_pc_ls[i]] += 1
	if ( branch_opc_ls[i] == 384 ):
		dis = int(abs(des_pc_ls[i] - src_pc_ls[i])/4)
		dis_count += dis
		distance_ls.append(dis)
		if (dis == 1):
			total_not_taken += 1
		else:
			total_taken += 1
		tbz_src_dic[src_pc_ls[i]].append(des_pc_ls[i])
		tbz_des_set.add(des_pc_ls[i])
		tbz_des_count += 1
		if des_pc_ls[i] not in tbz_des_dic:
			tbz_des_dic[des_pc_ls[i]] = 1
		else:
			tbz_des_dic[des_pc_ls[i]] += 1
	
	
		
print('\tBranch taken : ',total_taken)
print('\tBranch not taken : ',total_not_taken)
print('\tBranch taken ratio: ',round(total_taken/(total_taken+total_not_taken)*100,2),'%',sep='')
print('\tBranch not taken ratio: ',round(total_not_taken/(total_taken+total_not_taken)*100,2),'%',sep='')

print('Branch distance : ')
print('\tMax jump distrance: ',max(distance_ls))
print('\tMin jump distrance: ',min(distance_ls))
print('\tAvg jump distrance: ',round(dis_count/ls_len,2))

print('Branch detail : ')
print('Bcond : ')
bcond_index = 0 
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in bcond_src_dic.items():
	bcond_src_count += 1
print('\tTotal bcond :',bcond_src_count)
print('\tTotal Target pc :',len(bcond_des_set))
#for keys,values in sorted(bcond_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#	print('\tBcond des_pc<%#x' % keys,'>(',round(bcond_des_dic[keys]/bcond_des_count*100,2),'%) :',bcond_des_dic[keys],sep='')
for keys,values in sorted(bcond_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(bcond_src_dic[keys])):
                if bcond_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[bcond_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                	tmp_dic[bcond_src_dic[keys][i]] += 1
                dis = int(abs(bcond_src_dic[keys][i]-keys)/4)
                bcond_dis_count += dis
                bcond_distance_ls.append(dis)
                if ( keys+4 == bcond_src_dic[keys][i] ):
                        bcond_not_taken += 1
                else:
                        bcond_taken += 1
        print('\tBcond[',bcond_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        bcond_index += 1
        bcond_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',bcond_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                bcond_target_index += 1
        if ( bcond_target_index == 1 ):
                target_num1 += 1
        elif ( bcond_target_index == 2 ):
                target_num2 += 1
        elif ( bcond_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Bcond target sum :')
print('\tBcond 1 target: ',target_num1)
print('\tBcond 2 target: ',target_num2)
print('\tBcond 3 target: ',target_num3)
print('\tBcond > 3 target: ',target_numn)
print('Bcond taken :')
print('\tBcond taken :',bcond_taken)
print('\tBcond not taken :',bcond_not_taken)
print('Bcond distance :')
if bcond_distance_ls:
	print('\tBcond Max jump distrance: ',max(bcond_distance_ls))
	print('\tBcond Min jump distrance: ',min(bcond_distance_ls))
	print('\tBcond Avg jump distance :',round(bcond_dis_count/len(bcond_distance_ls),2))

print('Cbnz : ')
cbnz_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in cbnz_src_dic.items():
        cbnz_src_count += 1
print('\tTotal Cbnz :',cbnz_src_count)
print('\tTotal Target pc :',len(cbnz_des_set))
#for keys,values in sorted(cbnz_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tCbnz des_pc<%#x' % keys,'>(',round(cbnz_des_dic[keys]/cbnz_des_count*100,2),'%) :',cbnz_des_dic[keys],sep='')
for keys,values in sorted(cbnz_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(cbnz_src_dic[keys])):
                if cbnz_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[cbnz_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[cbnz_src_dic[keys][i]] += 1
                dis = int(abs(cbnz_src_dic[keys][i]-keys)/4)
                cbnz_dis_count += dis
                cbnz_distance_ls.append(dis)
                if ( keys+4 == cbnz_src_dic[keys][i] ):
                        cbnz_not_taken += 1
                else:
                        cbnz_taken += 1
        print('\tCbnz[',cbnz_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        cbnz_index += 1
        cbnz_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',cbnz_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                cbnz_target_index += 1
        if ( cbnz_target_index == 1 ):
                target_num1 += 1
        elif ( cbnz_target_index == 2 ):
                target_num2 += 1
        elif ( cbnz_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Cbnz target sum :')
print('\tCbnz 1 target: ',target_num1)
print('\tCbnz 2 target: ',target_num2)
print('\tCbnz 3 target: ',target_num3)
print('\tCbnz > 3 target: ',target_numn)
print('Cbnz taken :')
print('\tCbnz taken :',cbnz_taken)
print('\tCbnz not taken :',cbnz_not_taken)
print('Cbnz distance :')
if cbnz_distance_ls:
	print('\tCbnz Max jump distrance: ',max(cbnz_distance_ls))
	print('\tCbnz Min jump distrance: ',min(cbnz_distance_ls))
	print('\tCbnz Avg jump distance :',round(cbnz_dis_count/len(cbnz_distance_ls),2))

print('Cbz : ')
cbz_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in cbz_src_dic.items():
        cbz_src_count += 1
print('\tTotal Cbz :',cbz_src_count)
print('\tTotal Target pc :',len(cbz_des_set))
#for keys,values in sorted(cbz_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tCbz des_pc<%#x' % keys,'>(',round(cbz_des_dic[keys]/cbz_des_count*100,2),'%) :',cbz_des_dic[keys],sep='')
for keys,values in sorted(cbz_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(cbz_src_dic[keys])):
                if cbz_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[cbz_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[cbz_src_dic[keys][i]] += 1
                dis = int(abs(cbz_src_dic[keys][i]-keys)/4)
                cbz_dis_count += dis
                cbz_distance_ls.append(dis)
                if ( keys+4 == cbz_src_dic[keys][i] ):
                        cbz_not_taken += 1
                else:
                        cbz_taken += 1
        print('\tCbz[',cbz_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        cbz_index += 1
        cbz_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',cbz_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                cbz_target_index += 1
        if ( cbz_target_index == 1 ):
                target_num1 += 1
        elif ( cbz_target_index == 2 ):
                target_num2 += 1
        elif ( cbz_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Cbz target sum :')
print('\tCbz 1 target: ',target_num1)
print('\tCbz 2 target: ',target_num2)
print('\tCbz 3 target: ',target_num3)
print('\tCbz > 3 target: ',target_numn)
print('Cbz taken:')
print('\tCbz taken :',cbz_taken)
print('\tCbz not taken :',cbz_not_taken)
print('Cbz distance :')
if cbz_distance_ls:
	print('\tCbz Max jump distrance: ',max(cbz_distance_ls))
	print('\tCbz Min jump distrance: ',min(cbz_distance_ls))
	print('\tCbz Avg jump distance :',round(cbz_dis_count/len(cbz_distance_ls),2))

print('Tbnz : ')
tbnz_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in tbnz_src_dic.items():
        tbnz_src_count += 1
print('\tTotal Tbnz :',tbnz_src_count)
print('\tTotal Target pc :',len(tbnz_des_set))
#for keys,values in sorted(tbnz_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tTbnz des_pc<%#x' % keys,'>(',round(tbnz_des_dic[keys]/tbnz_des_count*100,2),'%) :',tbnz_des_dic[keys],sep='')
for keys,values in sorted(tbnz_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(tbnz_src_dic[keys])):
                if tbnz_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[tbnz_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[tbnz_src_dic[keys][i]] += 1
                dis = int(abs(tbnz_src_dic[keys][i]-keys)/4)
                tbnz_dis_count += dis
                tbnz_distance_ls.append(dis)
                if ( keys+4 == tbnz_src_dic[keys][i] ):
                        tbnz_not_taken += 1
                else:
                        tbnz_taken += 1
        print('\tTbnz[',tbnz_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        tbnz_index += 1
        tbnz_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',tbnz_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                tbnz_target_index += 1
        if ( tbnz_target_index == 1 ):
                target_num1 += 1
        elif ( tbnz_target_index == 2 ):
                target_num2 += 1
        elif ( tbnz_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Tbnz target sum :')
print('\tTbnz 1 target: ',target_num1)
print('\tTbnz 2 target: ',target_num2)
print('\tTbnz 3 target: ',target_num3)
print('\tTbnz > 3 target: ',target_numn)
print('Tbnz taken :')
print('\tTbnz taken :',tbnz_taken)
print('\tTbnz not taken :',tbnz_not_taken)
print('Tbnz distance :')
if tbnz_distance_ls:
	print('\tTbnz Max jump distrance: ',max(tbnz_distance_ls))
	print('\tTbnz Min jump distrance: ',min(tbnz_distance_ls))
	print('\tTbnz Avg jump distance :',round(tbnz_dis_count/len(tbnz_distance_ls),2))


print('Tbz : ')
tbz_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in tbz_src_dic.items():
        tbz_src_count += 1
print('\tTotal Tbz :',tbz_src_count)
print('\tTotal Target pc :',len(tbz_des_set))
#for keys,values in sorted(tbz_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tTbz des_pc<%#x' % keys,'>(',round(tbz_des_dic[keys]/tbz_des_count*100,2),'%) :',tbz_des_dic[keys],sep='')
for keys,values in sorted(tbz_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(tbz_src_dic[keys])):
                if tbz_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[tbz_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[tbz_src_dic[keys][i]] += 1
                dis = int(abs(tbz_src_dic[keys][i]-keys)/4)
                tbz_dis_count += dis
                tbz_distance_ls.append(dis)
                if ( keys+4 == tbz_src_dic[keys][i] ):
                        tbz_not_taken += 1
                else:
                        tbz_taken += 1
        print('\tTbz[',tbz_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        tbz_index += 1
        tbz_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',tbz_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                tbz_target_index += 1
        if ( tbz_target_index == 1 ):
                target_num1 += 1
        elif ( tbz_target_index == 2 ):
                target_num2 += 1
        elif ( tbz_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Tbz target sum :')
print('\tTbz 1 target: ',target_num1)
print('\tTbz 2 target: ',target_num2)
print('\tTbz 3 target: ',target_num3)
print('\tTbz > 3 target: ',target_numn)
print('Tbz taken : ')
print('\tTbz taken :',tbz_taken)
print('\tTbz not taken :',tbz_not_taken)
print('Tbz distance :')
if tbz_distance_ls:
	print('\tTbz Max jump distrance: ',max(tbz_distance_ls))
	print('\tTbz Min jump distrance: ',min(tbz_distance_ls))
	print('\tTbz Avg jump distance :',round(tbz_dis_count/len(tbz_distance_ls),2))

print('B : ')
b_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in b_src_dic.items():
        b_src_count += 1
print('\tTotal b :',b_src_count)
print('\tTotal Target pc :',len(b_des_set))
#for keys,values in sorted(b_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tB des_pc<%#x' % keys,'>(',round(b_des_dic[keys]/b_des_count*100,2),'%) :',b_des_dic[keys],sep='')
for keys,values in sorted(b_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(b_src_dic[keys])):
                if b_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[b_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[b_src_dic[keys][i]] += 1
                dis = int(abs(b_src_dic[keys][i]-keys)/4)
                b_dis_count += dis
                b_distance_ls.append(dis)
        print('\tB[',b_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        b_index += 1
        b_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',b_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                b_target_index += 1
        if ( b_target_index == 1 ):
                target_num1 += 1
        elif ( b_target_index == 2 ):
                target_num2 += 1
        elif ( b_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('B target sum :')
print('\tB 1 target: ',target_num1)
print('\tB 2 target: ',target_num2)
print('\tB 3 target: ',target_num3)
print('\tB > 3 target: ',target_numn)
print('B distance :')
if b_distance_ls:
	print('\tB Max jump distrance: ',max(b_distance_ls))
	print('\tB Min jump distrance: ',min(b_distance_ls))
	print('\tB Avg jump distance :',round(b_dis_count/len(b_distance_ls),2))

print('Br : ')
br_index = 0
target_num1 = 0
target_num2 = 0
target_num3 = 0
target_numn = 0
for keys,values in br_src_dic.items():
        br_src_count += 1
print('\tTotal br :',br_src_count)
print('\tTotal Target pc :',len(br_des_set))
#for keys,values in sorted(br_des_dic.items(), key = lambda kv:(kv[1],kv[0]),reverse=True):
#        print('\tBr des_pc<%#x' % keys,'>(',round(br_des_dic[keys]/br_des_count*100,2),'%) :',br_des_dic[keys],sep='')
for keys,values in sorted(br_src_dic.items(), key = lambda d:len(d[1]) ,reverse=True):
        tmp_dic = {}
        tmp_dic_key_num = 0
        for i in range(0,len(br_src_dic[keys])):
                if br_src_dic[keys][i] not in tmp_dic:
                        tmp_dic[br_src_dic[keys][i]] = 1
                        tmp_dic_key_num += 1
                else:
                        tmp_dic[br_src_dic[keys][i]] += 1
                dis = int(abs(br_src_dic[keys][i]-keys)/4)
                br_dis_count += dis
                br_distance_ls.append(dis)
        print('\tBr[',br_index,'] src_pc<%#x' % keys,'>',':',tmp_dic_key_num,sep='' )
        br_index += 1
        br_target_index = 0
        for keys,values in tmp_dic.items():
                print('\t\t\t\tT[',br_target_index,'] des_pc<%#x' % keys,'>:',values,sep='')
                br_target_index += 1
        if ( br_target_index == 1 ):
                target_num1 += 1
        elif ( br_target_index == 2 ):
                target_num2 += 1
        elif ( br_target_index == 3 ):
                target_num3 += 1
        else:
                target_numn += 1
print('Br target sum :')
print('\tBr 1 target: ',target_num1)
print('\tBr 2 target: ',target_num2)
print('\tBr 3 target: ',target_num3)
print('\tBr > 3 target: ',target_numn)
print('Br distance :')
if br_distance_ls:
	print('\tBr Max jump distrance: ',max(br_distance_ls))
	print('\tBr Min jump distrance: ',min(br_distance_ls))
	print('\tBr Avg jump distance :',round(br_dis_count/len(br_distance_ls),2))
FileDis_pc.close()

