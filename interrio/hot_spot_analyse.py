import json
import sys


# 解析反汇编文件 得到函数首地址到方法名和结束地址映射
def analyse_fun_address(file_path):
    address_to_end_address_and_func = {}
    with open(file_path, 'r') as asm_file:
        line = asm_file.readline()
        last_address = None
        while line:
            index_1 = line.find('<')
            index_2 = line.find('>:')
            if index_1 != -1 and index_2 != -1:
                fun_name = line[index_1 + 1: index_2]
                fun_address = line.split()[0]
                address_to_end_address_and_func[fun_address] = {
                    'func_name': fun_name
                }
                if last_address:
                    address_to_end_address_and_func[last_address]['end_address'] = fun_address
                last_address = fun_address
            line = asm_file.readline()
        address_to_end_address_and_func[fun_address]['end_address'] = hex(int(fun_address, 16) + 16)[2:].zfill(16)
    return address_to_end_address_and_func


# 解析反汇编文件 得到地址到指令的映射关系
def analyse_address_to_codes(file_path):
    address_to_code = {}
    with open(file_path, 'r') as asm_file:
        line = asm_file.readline()
        while line:
            if line.startswith('  '):
                address_to_code[int(line.split()[0][:-1], 16)] = line.strip().replace('\t', '  ')
            line = asm_file.readline()
    return address_to_code


# 解析bb call 执行次数  解析地址调用次数
# return results:
# pid_tid_set
# ["pid1_tid1", "pid2_tid2"]
# bb_to_call_times_per_pid_tid
# {
#     "pid_tid;": {
#         "start_address-end_address": {
#           times: time1
#           codes: []
#         },
#         "start_address1-end_address1": {
#           times: time1
#           codes: []
#         },
#          ...
#     },
#     "pid2_tid2;": {
#         "start_address1=2-end_address2": {
#           times: time1
#           codes: []
#         },
#          ...
#     },
#     ...
# }
# address_to_call_times_per_pid_tid
# {
#     "pid_tid;": {
#         "address1": times1,
#         "address2": times2,
#          ...
#     },
#     "pid2_tid2;": {
#         "address2": times2
#          ...
#     },
#     ...
# }
def analyse_bb_and_call(file_path, address_to_codes):
    pid_tid_set = []
    address_to_call_times_per_pid_tid = {}
    bb_to_call_times_per_pid_tid = {}

    cur_process_type = 0  # 0 for bb, 1 for call
    cur_pid_tid = ''
    with open(file_path, 'r') as call_file:
        line = call_file.readline()
        while line:
            if line.startswith('bb info:'):
                cur_process_type = 0
                index1 = line.find('pid=')
                index2 = line.find(', tid=')
                index3 = line.find(', block total=')
                cur_pid_tid = line[index1 + 4: index2] + '_' + line[index2 + 6: index3]
                bb_to_call_times_per_pid_tid[cur_pid_tid] = {}
            elif line.startswith("func call info:"):
                cur_process_type = 1
                index1 = line.find('pid=')
                index2 = line.find(', tid=')
                cur_pid_tid = line[index1 + 4: index2] + '_' + line[index2 + 6:-1]
                address_to_call_times_per_pid_tid[cur_pid_tid] = {}
                pid_tid_set.append(cur_pid_tid)
            else:
                if cur_process_type:
                    index1 = line.find('call=')
                    index2 = line.find(' time=')
                    func_address = line[index1 + 5: index2]
                    time = int(line[index2 + 6:])
                    address_to_call_times_per_pid_tid[cur_pid_tid][func_address] = time
                else:
                    index1 = line.find('block=')
                    index2 = line.find(' time=')
                    block = line[index1 + 6: index2]
                    time = int(line[index2 + 6:])
                    bb_to_call_times_per_pid_tid[cur_pid_tid][block] = {
                        'times': time,
                        'codes': get_codes(address_to_codes, int(block.split('-')[0], 16), int(block.split('-')[1], 16))
                    }
            line = call_file.readline()
    return pid_tid_set, bb_to_call_times_per_pid_tid, address_to_call_times_per_pid_tid


#  总处理函数，获取最后结果
def analyse_hot_spot(address_to_end_address_and_func, pid_tid_set, address_to_call_times_per_pid_tid,
                     bb_to_call_times_per_pid_tid):
    func_to_call_times_per_pid_tid = {}

    for pid_tid in pid_tid_set:
        func_to_call_times = {}
        address_to_call_times = address_to_call_times_per_pid_tid[pid_tid]
        bb_to_call_times = bb_to_call_times_per_pid_tid[pid_tid] if pid_tid in bb_to_call_times_per_pid_tid else {}
        for address in address_to_call_times:
            if address in address_to_end_address_and_func:
                # if address_to_func[address].startswith("_"):
                #     continue
                func_to_call_times[address_to_end_address_and_func[address]['func_name']] = {
                    'time': address_to_call_times[address],
                    'func_address': address,
                    'blocks': {}
                }
            # else:
            #     func_to_call_times[address] = address_to_call_times[address]
        for func_start_address_str in address_to_end_address_and_func:
            func_start_address = int(func_start_address_str, 16)
            func_end_address = int(address_to_end_address_and_func[func_start_address_str]['end_address'], 16)
            for bb in bb_to_call_times:  # bb like 000000000041604c-0000000000416050
                bb_start_address = int(bb.split('-')[0], 16)
                bb_end_address = int(bb.split('-')[1], 16)
                if bb_start_address >= func_start_address and bb_end_address < func_end_address and \
                        address_to_end_address_and_func[func_start_address_str]['func_name'] in func_to_call_times:
                    bb_short = bb.split('-')[0].lstrip('0') + '-' + bb[-8:].lstrip(
                        '0')  # bb: 000000000041604c-0000000000416050  bb_short: 41604c-416050
                    func_to_call_times[address_to_end_address_and_func[func_start_address_str]['func_name']]['blocks'][
                        bb_short] = bb_to_call_times[bb]

        func_to_call_times_per_pid_tid[pid_tid] = func_to_call_times
    return func_to_call_times_per_pid_tid


# 使用地址返回获取代码
def get_codes(address_to_code, start_address, end_address):
    codes = []
    for i in range(start_address, end_address + 4, 4):
        if i in address_to_code:
            codes.append(address_to_code[i])
    return codes


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(__file__ + " need 1 args: the object disassemble file path!")

    address_to_end_address_and_func = analyse_fun_address(sys.argv[1])
    address_to_code = analyse_address_to_codes(sys.argv[1])

    pid_tid_set, bb_to_call_times_per_pid_tid, address_to_call_times_per_pid_tid = analyse_bb_and_call(
        'bb_call_count.txt', address_to_code)

    hot_spot_result = analyse_hot_spot(address_to_end_address_and_func, pid_tid_set,
                                       address_to_call_times_per_pid_tid, bb_to_call_times_per_pid_tid)
    with open('hot-spot-result.json', 'w') as f:
        json.dump(hot_spot_result, f)
    print('Hot spot result is in file: hot-spot-result.json.')
