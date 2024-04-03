import sys
name_to_num={}

FileDis= rf"{sys.argv[1]}"
ratio = float(sys.argv[2])
print('Input ratio =',ratio)
Filedis = open(FileDis)
print('Opcode mix tool process results:')
LineTemp = Filedis.readline()
LineTemp = Filedis.readline()
a=LineTemp.find(':')
total_insn = int(LineTemp[:a-1].strip())
LineTemp = Filedis.readline()
a=LineTemp.find(':')
total_usr_insn = int(LineTemp[:a-1].strip())
LineTemp = Filedis.readline()
a=LineTemp.find(':')
total_sys_insn = int(LineTemp[:a-1].strip())
Filedis.close()

Filedis = open(FileDis)
LineTemp = Filedis.readline()
total_keys = 0
while LineTemp and 'usr results' not in LineTemp: 
	if ':' in LineTemp and 'total' not in LineTemp and 'results' not in LineTemp:
		b=LineTemp.find(':')
		name = LineTemp[b+1:-1].strip() 
		num = int(LineTemp[:b-1].strip())
		if name not in name_to_num:
			name_to_num[name] = num
			total_keys +=1
		else:
			name_to_num[name] += num
	LineTemp=Filedis.readline()	
name_to_num_usr={}
usr_insn_ls=set()
total_usr_keys = 0
while LineTemp and 'sys results' not in LineTemp:
	if ':' in LineTemp and 'total' not in LineTemp and 'results' not in LineTemp:
		c=LineTemp.find(':')
		name = LineTemp[b+1:-1].strip()
		num = int(LineTemp[:b-1].strip())
		usr_insn_ls.add(name)
		if name not in name_to_num_usr:
			name_to_num_usr[name] = num
			total_usr_keys += 1
		else:
			name_to_num_usr[name] += num
	LineTemp=Filedis.readline()
name_to_num_sys={}
sys_insn_ls = set()
total_sys_keys = 0
while LineTemp:
        if ':' in LineTemp and 'total' not in LineTemp and 'results' not in LineTemp:
                d=LineTemp.find(':')
                name = LineTemp[b+1:-1].strip()
                num = int(LineTemp[:b-1].strip())
                sys_insn_ls.add(name)
                if name not in name_to_num_sys:
                        name_to_num_sys[name] = num
                        total_sys_keys += 1
                else:
                        name_to_num_sys[name] += num
        LineTemp=Filedis.readline()
diff_insn_ls = usr_insn_ls ^ sys_insn_ls
print('Instruction count:')
print('%15s' % total_insn,': total')
print('%15s' % total_usr_insn,': total usr')
print('%15s' % total_sys_insn,': total sys')
print('Instruction proportion:')
print('%14s' % round(total_usr_insn/total_insn*100,2),'%',' : total usr',sep='')
print('%14s' % round(total_sys_insn/total_insn*100,2),'%',' : total sys',sep='')
print('Instruction category:')
print('%15s' % total_keys,': total ')
print('%15s' % total_usr_keys,': total usr ')
print('%15s' % total_sys_keys,': total sys ')
print('Core  total results:')

top_total_insn = 0
top_keys = 0
for keys,values in sorted(name_to_num.items() , key = lambda kv:(kv[1],kv[0]),reverse = True):
	top_total_insn += values
	top_keys += 1
	print('%14s' % round(values/total_insn*100 ,2),'%',' : %9s' % keys,sep='')
	if (top_total_insn/total_insn > ratio):
		break
print(f'Top {top_keys} keys cover {round(top_total_insn/total_insn*100,2)}%')
print()

i = 0
conditional_branch_ls=[]
unconditional_branch_ls=[]
call_and_ret_ls=[]
exception_generation_and_return_ls=[]
system_register_instructions_ls=[]
system_instructions_ls=[]
hint_instructions_ls=[]
barriers_and_CLREX_instructions_ls=[]

load_store_register_ls=[]
load_store_pair_ls=[]
load_store_unprivileged_ls=[]
load_store_exclusive_ls=[]
load_acquire_store_release_ls=[]

arithmetic_ls=[]
logical_ls=[]
move_ls=[]
pc_relative_address_calculation_ls=[]
bitfield_processing_ls=[]
extract_register_ls=[]
shift_ls=[]
conditional_select_ls=[]
conditional_comparison_ls=[]
multiply_and_divide_ls=[]

name_to_ratio={}
name_to_ratio['conditional_branch_ls'] = 0
name_to_ratio['unconditional_branch_ls'] = 0
name_to_ratio['call_and_ret_ls'] = 0
name_to_ratio['exception_generation_and_return_ls'] = 0
name_to_ratio['system_register_instructions_ls'] = 0
name_to_ratio['system_instructions_ls'] = 0
name_to_ratio['hint_instructions_ls'] = 0
name_to_ratio['barriers_and_CLREX_instructions_ls'] = 0

name_to_ratio['load_store_register_ls'] = 0
name_to_ratio['load_store_pair_ls'] = 0
name_to_ratio['load_store_unprivileged_ls'] = 0
name_to_ratio['load_store_exclusive_ls'] = 0
name_to_ratio['load_acquire_store_release_ls'] = 0

name_to_ratio['arithmetic_ls'] = 0
name_to_ratio['logical_ls'] = 0
name_to_ratio['move_ls'] = 0
name_to_ratio['pc_relative_address_calculation_ls'] = 0
name_to_ratio['bitfield_processing_ls'] = 0
name_to_ratio['extract_register_ls'] = 0
name_to_ratio['shift_ls'] = 0
name_to_ratio['conditional_select_ls'] = 0
name_to_ratio['conditional_comparison_ls'] = 0
name_to_ratio['multiply_and_divide_ls'] = 0

for key,values in sorted(name_to_num.items() , key = lambda kv:(kv[1],kv[0]),reverse = True):
	if ( i < top_keys):
		if ( key == 'bcond' or key == 'cbnz' or key == 'cbz' or key == 'tbnz' or key == 'tbz'):
			if key in diff_insn_ls:
				key = key + '*'
			conditional_branch_ls.append(key)
			name_to_ratio['conditional_branch_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['conditional_branch_ls'] = round(name_to_ratio['conditional_branch_ls'] , 2)
		if ( key == 'b' or key == 'br' ):
			if key in diff_insn_ls:
				key = key + '*'
			unconditional_branch_ls.append(key)
			name_to_ratio['unconditional_branch_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['unconditional_branch_ls'] = round(name_to_ratio['unconditional_branch_ls'],2)
		if ( key == 'bl' or key == 'blr' or key == 'ret'):
			if key in diff_insn_ls:
				key = key + '*'
			call_and_ret_ls.append(key)
			name_to_ratio['call_and_ret_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['call_and_ret_ls'] = round(name_to_ratio['call_and_ret_ls'],2)
		if ( key == 'brk' or key == 'hlt' or key == 'hvc' or key == 'smc' or key == 'svc' or key == 'eret' ):
			if key in diff_insn_ls:
				key = key + '*'
			exception_generation_and_return_ls.append(key)
			name_to_ratio['exception_generation_and_return_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['exception_generation_and_return_ls'] = round(name_to_ratio['exception_generation_and_return_ls'],2)
		if ( key == 'mrs' or key == 'msr' ):
			if key in diff_insn_ls:
				key = key + '*'
			system_register_instructions_ls.append(key)
			name_to_ratio['system_register_instructions_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['system_register_instructions_ls'] = round(name_to_ratio['system_register_instructions_ls'],2)
		if ( key == 'sys' or key == 'sysl' or key == 'ic' or key == 'dc' or key == 'at' or key == 'tlbi'):
			if key in diff_insn_ls:
				key = key + '*'
			system_instructions_ls.append(key)
			name_to_ratio['system_instructions_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['system_instructions_ls'] = round(name_to_ratio['system_instructions_ls'] ,2)
		if ( key == 'nop' or key == 'yield' or key == 'wfe' or key == 'wfi' or key == 'sev' or key == 'sevl' or key == 'hint' or key == 'dgh'):
			if key in diff_insn_ls:
				key = key + '*'
			hint_instructions_ls.append(key)
			name_to_ratio['hint_instructions_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['hint_instructions_ls'] = round(name_to_ratio['hint_instructions_ls'] ,2)
		if ( key == 'clrex' or key == 'dmb' or key == 'dsb' or key == 'isb' or key == 'csdb' or key == 'esb' or key == 'psb csync' or key == 'pssbb' or key == 'sb' or key == 'ssbb' or key == 'tsb csync'):
			if key in diff_insn_ls:
				key = key + '*'
			barriers_and_CLREX_instructions_ls.append(key)
			name_to_ratio['barriers_and_CLREX_instructions_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['barriers_and_CLREX_instructions_ls'] = round(name_to_ratio['barriers_and_CLREX_instructions_ls'] ,2)

		if ( key == 'ldr' or key == 'ldrb' or key == 'ldrsb' or key == 'ldrh' or key == 'ldrsh' or key == 'ldrsw' or key == 'str' or key == 'strb' or key == 'strh' or key == 'ldur' or key == 'ldurb' or key == 'ldursb' or key == 'ldurh' or key == 'ldursw' or key == 'stur' or key == 'sturb' or key == 'sturh'):
			if key in diff_insn_ls:
				key = key + '*'
			load_store_register_ls.append(key)
			name_to_ratio['load_store_register_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['load_store_register_ls'] = round(name_to_ratio['load_store_register_ls'] ,2)
		if ( key == 'ldp' or key == 'ldpsw' or key == 'stp' or key == 'ldnp' or key == 'stnp'):
			if key in diff_insn_ls:
				key = key + '*'
			load_store_pair_ls.append(key)
			name_to_ratio['load_store_pair_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['load_store_pair_ls'] = round(name_to_ratio['load_store_pair_ls'],2)
		if ( key == 'ldtr' or key == 'ldtrb' or key == 'ldtrsb' or key == 'ldtrh' or key == 'ldtrsh' or key == 'ldtrsw' or key == 'sttr' or key == 'sttrb' or key == 'sttrh'):
			if key in diff_insn_ls:
				key = key + '*'
			load_store_unprivileged_ls.append(key)
			name_to_ratio['load_store_unprivileged_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['load_store_unprivileged_ls'] = round(name_to_ratio['load_store_unprivileged_ls'] ,2)
		if ( key == 'ldxr' or key == 'ldxrb' or key == 'ldxrh' or key == 'ldxp' or key == 'stxr' or key == 'stxrb' or key == 'stxrh' or key == 'stxp'):
			if key in diff_insn_ls:
				key = key + '*'
			load_store_exclusive_ls.append(key)
			name_to_ratio['load_store_exclusive_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['load_store_exclusive_ls'] = round(name_to_ratio['load_store_exclusive_ls'] ,2)
		if ( key == 'ldaxr' or key == 'ldaxrb' or key == 'ldaxrh' or key == 'ldaxp' or key == 'stlxr' or key == 'stlxrh' or key == 'stlxrh' or key == 'stlxp' or key == 'ldapr' or key == 'ldaprb' or key == 'ldaprh' or key == 'ldapur' or key == 'ldapurb' or key == 'ldapursb' or key == 'ldapursh' or key == 'ldapursw' or key == 'ldar' or key == 'ldarb' or key == 'ldarh' or key == 'stlr' or key == 'stlrb' or key == 'stlrh' or key == 'stlur' or key == 'stlurb' or key == 'stlurh'):
			if key in diff_insn_ls:
				key = key + '*'
			load_acquire_store_release_ls.append(key)
			name_to_ratio['load_acquire_store_release_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['load_acquire_store_release_ls'] = round(name_to_ratio['load_acquire_store_release_ls'] ,2)
		
		if ( key == 'add' or key == 'adds' or key == 'sub' or key == 'subs' or key == 'cmp' or key == 'cmn' or key == 'neg' or key == 'negs' or key == 'adc' or key == 'adcs' or key == 'sbc' or key == 'sbcs' or key == 'ngc' or key == 'ngcs'):
			if key in diff_insn_ls:
				key = key + '*'
			arithmetic_ls.append(key)
			name_to_ratio['arithmetic_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['arithmetic_ls'] = round(name_to_ratio['arithmetic_ls'] ,2)
		if ( key == 'and' or key == 'ands' or key == 'eor' or key == 'orr' or key == 'tst' or key == 'bic' or key == 'bics' or key == 'eon' or key == 'mvn' or key == 'orn'):
			if key in diff_insn_ls:
				key = key + '*'
			logical_ls.append(key)
			name_to_ratio['logical_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['logical_ls'] = round(name_to_ratio['logical_ls'] ,2)
		if ( key == 'movz' or key == 'movn' or key == 'movk' or key == 'mov' ):
			if key in diff_insn_ls:
				key = key + '*'
			move_ls.append(key)
			name_to_ratio['move_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['move_ls'] = round(name_to_ratio['move_ls'] ,2)
		if ( key == 'adrp' or key == 'adr'):
			if key in diff_insn_ls:
				key = key + '*'
			pc_relative_address_calculation_ls.append(key)
			name_to_ratio['pc_relative_address_calculation_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['pc_relative_address_calculation_ls'] = round(name_to_ratio['pc_relative_address_calculation_ls'] ,2)
		if ( key == 'bfm' or key == 'sbfm' or key == 'ubfm' or key == 'bfc' or key == 'bfi' or key == 'bfxil' or key == 'sbfiz' or key == 'sbfx' or key == 'ubfiz' or key == 'ubfx'):
			if key in diff_insn_ls:
				key = key + '*'
			bitfield_processing_ls.append(key)
			name_to_ratio['bitfield_processing_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['bitfield_processing_ls'] = round(name_to_ratio['bitfield_processing_ls'] ,2)
		if ( key == 'extr'):
			if key in diff_insn_ls:
				key = key + '*'
			extract_register_ls.append(key)
			name_to_ratio['extract_register_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['extract_register_ls'] = round(name_to_ratio['extract_register_ls'] ,2)
		if ( key == 'asrv' or key == 'lslv' or key == 'lsrv' or key == 'rorv' or key == 'asr' or key == 'lsl' or key == 'lsr' or key == 'ror'):
			if key in diff_insn_ls:
				key = key + '*'
			shift_ls.append(key)
			name_to_ratio['shift_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['shift_ls'] = round(name_to_ratio['shift_ls'] ,2)
		if ( key == 'csel' or key == 'csinc' or key == 'csinv' or key == 'cset' or key == 'csetm' or key == 'cinc' or key == 'cinv' or key == 'cneg'):
			if key in diff_insn_ls:
				key = key + '*'
			conditional_select_ls.append(key)
			name_to_ratio['conditional_select_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['conditional_select_ls'] = round(name_to_ratio['conditional_select_ls'] ,2)
		if ( key == 'udiv' or key == 'sdiv' or key == 'umaddl' or key == 'umsubl' or key == 'umnegl' or key == 'umull' or key == 'umulh' or key == 'madd' or key == 'msub' or key == 'mneg' or key == 'mul' or key == 'smaddl' or key == 'smsubl' or key == 'smnegl' or key == 'smull' or key == 'smulh'):
			if key in diff_insn_ls:
				key = key + '*'
			multiply_and_divide_ls.append(key)
			name_to_ratio['multiply_and_divide_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['multiply_and_divide_ls'] = round(name_to_ratio['multiply_and_divide_ls'] ,2)
		if ( key == 'ccmn' or key == 'ccmp'):
			if key in diff_insn_ls:
				key = key + '*'
			conditional_comparison_ls.append(key)
			name_to_ratio['conditional_comparison_ls'] += round(values/total_insn*100 ,2)
			name_to_ratio['conditional_comparison_ls'] = round(name_to_ratio['conditional_comparison_ls'] ,2)
		i += 1
print('Branch(',name_to_ratio['conditional_branch_ls']+name_to_ratio['unconditional_branch_ls']+name_to_ratio['call_and_ret_ls'],'%):',sep='')
if conditional_branch_ls:
	print('Conditional branch(',name_to_ratio['conditional_branch_ls'],'%):',sep='')
	print(*conditional_branch_ls, sep=' , ' )
if unconditional_branch_ls:
	print('Unconditional branch(',name_to_ratio['unconditional_branch_ls'],'%):',sep='')
	print(*unconditional_branch_ls, sep=' , ')
if call_and_ret_ls:
	print('Call and Ret(',name_to_ratio['call_and_ret_ls'],'%):',sep='')
	print(*call_and_ret_ls,sep=' , ')

print()
print('Other(',name_to_ratio['exception_generation_and_return_ls']+name_to_ratio['system_register_instructions_ls']+name_to_ratio['system_instructions_ls']+name_to_ratio['hint_instructions_ls']+name_to_ratio['barriers_and_CLREX_instructions_ls']+name_to_ratio['move_ls']+name_to_ratio['extract_register_ls'],'%):',sep='')
if exception_generation_and_return_ls:
	print('Exception Generation and Retur(',name_to_ratio['exception_generation_and_return_ls'],'%):',sep='')
	print(*exception_generation_and_return_ls , sep = ' , ')
if system_register_instructions_ls:
	print('System register instructions(',name_to_ratio['system_register_instructions_ls'],'%):',sep='')
	print(*system_register_instructions_ls , sep = ' , ')
if system_instructions_ls:
	print('System instructions(',name_to_ratio['system_instructions_ls'],'%):',sep='')
	print(*system_instructions_ls , sep=' , ')
if hint_instructions_ls:
	print('Hint instructions(',name_to_ratio['hint_instructions_ls'],'%):',sep='')
	print(*hint_instructions_ls , sep=' , ')
if barriers_and_CLREX_instructions_ls:
	print('Barriers and CLREX instructions(',name_to_ratio['barriers_and_CLREX_instructions_ls'],'%):',sep='')
	print(*barriers_and_CLREX_instructions_ls , sep=' , ')
if move_ls:
	print('Move(',name_to_ratio['move_ls'],'%):',sep='')
	print(*move_ls, sep=' , ')
if extract_register_ls:
	print('Extract register(',name_to_ratio['extract_register_ls'],'%):',sep='')
	print(*extract_register_ls, sep=' , ')
print()
print('Load and Store(',name_to_ratio['load_store_register_ls']+name_to_ratio['load_store_pair_ls']+name_to_ratio['load_store_unprivileged_ls']+name_to_ratio['load_store_exclusive_ls']+name_to_ratio['load_acquire_store_release_ls'],'%):',sep='')
if load_store_register_ls:
	print('Load and Store register(',name_to_ratio['load_store_register_ls'],'%):',sep='')
	print(*load_store_register_ls , sep=' , ')
if load_store_pair_ls:
	print('Load and Store pair(',name_to_ratio['load_store_pair_ls'],'%):',sep='')
	print(*load_store_pair_ls , sep=' , ')
if load_store_unprivileged_ls:
	print('Load and Store unprivileged(',name_to_ratio['load_store_unprivileged_ls'],'%):',sep='')
	print(*load_store_unprivileged_ls , sep=' , ')
if load_store_exclusive_ls:
	print('Load and Store exclusive(',name_to_ratio['load_store_exclusive_ls'],'%):',sep='')
	print(*load_store_exclusive_ls , sep=' , ')
	print()
if load_acquire_store_release_ls:
	print('Load acquire and Store release(',name_to_ratio['load_acquire_store_release_ls'],'%):',sep='')
	print(*load_acquire_store_release_ls , sep=' , ')
print()
print('Arithmetic calculation(',round(name_to_ratio['arithmetic_ls']+name_to_ratio['logical_ls']+name_to_ratio['multiply_and_divide_ls']+name_to_ratio['shift_ls']+name_to_ratio['pc_relative_address_calculation_ls']+name_to_ratio['bitfield_processing_ls'],2),'%):',sep='')
if arithmetic_ls:
	print('Arithmetic(',name_to_ratio['arithmetic_ls'],'%):',sep='')
	print(*arithmetic_ls , sep=' , ')
if logical_ls:
	print('Logical(',name_to_ratio['logical_ls'],'%):',sep='')
	print(*logical_ls , sep=' , ')
if multiply_and_divide_ls:
	print('Multiply and Divide(',name_to_ratio['multiply_and_divide_ls'],'%):',sep='')
	print(*multiply_and_divide_ls , sep=' , ')
if shift_ls:
	print('Shift(',name_to_ratio['shift_ls'],'%):',sep='')
	print(*shift_ls, sep=' , ')
if pc_relative_address_calculation_ls:
	print('PC-relative address calculation(',name_to_ratio['pc_relative_address_calculation_ls'],'%):',sep='')
	print(*pc_relative_address_calculation_ls, sep=' , ')
if bitfield_processing_ls:
	print('Bitfield processing(',name_to_ratio['bitfield_processing_ls'],'%):',sep='')
	print(*bitfield_processing_ls, sep=' , ')
print()
print('Conditional select and comparison(',round(name_to_ratio['conditional_select_ls']+name_to_ratio['conditional_comparison_ls'],2),'%):',sep='')
if conditional_select_ls:
	print('Conditional select(',name_to_ratio['conditional_select_ls'],'%):',sep='')
	print(*conditional_select_ls, sep=' , ')
if conditional_comparison_ls:
	print('Conditional comparison(',name_to_ratio['conditional_comparison_ls'],'%):',sep='')
	print(*conditional_comparison_ls ,sep=' , ')
print()
print('Diff',len(diff_insn_ls),'insn in usr & sys :')
print(*diff_insn_ls,sep=' , ')
Filedis.close()

