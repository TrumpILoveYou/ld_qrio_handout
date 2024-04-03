/* **********************************************************
 * Copyright (c) 2015-2020 Google, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Google, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#define SHARE_MEM
//#define _QR_R_TB_COUNT_

#include <assert.h>
#include <map>
#include "ipc_reader.h"
#include "../common/memref.h"
#include "../common/utils.h"
#ifdef SHARE_MEM
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <assert.h>
#include <thread>
#include <mutex>
#include <ctime>
#include <iostream>
#include <string.h>
#include  "shm_slim.h"

#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>//cpu bind
#include "gcc_atomic.h"
#include "ring_buf.h"
#include "cpu_timer.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef FUN_SPECIFY
#include "analyzer.h"
extern std::unordered_map<int,tid_flags> tid2flags;
#endif

qrio_buff_t * qbuf = NULL;
shm_data_t *shm = NULL;
tb_trace_t *tt;
int real_insn_num;
bool ipc_reader_t::read_next_tb(){
    int ret;
    int ret2;
    volatile  unsigned long taddr=0;
    if ( pre_tb == true ) 
	    ret2 = ringbuf->ringbuf_set_next();
    while(1){
      	qbuf = (qrio_buff_t*)ringbuf->shm_getaddr_from_idx(); 
        ret = ringbuf->ringbuf_pop_unlock();
        if(ret == No_Data) 
        {
	    if(ringbuf->rb_shm->app_status == 1){
	        continue;
	    }
	    if( ringbuf->rb_shm->app_status == 2){
		ringbuf->rb_shm->app_status = 1;
	        return false;
	    }
	    continue;
        }
        taddr = qbuf->offset;
    	tt = (tb_trace_t *)SHM_OFFT_TO_ADDR(taddr);
	real_insn_num= (qbuf->real_insn_num < tt->insn_num)? qbuf->real_insn_num : tt->insn_num;
    	
	//ret2 = ringbuf->ringbuf_set_next();

	cpu_id = (int)qbuf->cpu_id;
 	dpid = (int)qbuf->tgid;
    	dtid = (int)qbuf->pid;
	//printf("dtid i got: %d\n",(int)dtid);

#ifdef _QR_R_TB_COUNT_
        core_map_[cpu_id] += real_insn_num;
        core_tb_map_[cpu_id] +=1;
	tb_num++;
#endif
#ifdef DUMP_FUNC
	ins_total += real_insn_num;
	if  ( ipc_ins_print && ( ins_total > ipc_ins_print ) ) {
		/* output info of ins */
		printf("Processed total insn num = %u\n",ipc_ins_print*dcount);
		dcount++;
		ins_total = 0;

	}

#endif
        break;
	
    }
#ifdef FUN_SPECIFY
    if (tid2flags[(int)dtid].ret_flag) {
        tid2flags[(int)dtid].specified_flag = false;
        //end_counts++;
        //printf("end_counts: %d\n", end_counts);
        tid2flags[(int)dtid].ret_flag = false;
    }
    if (qbuf->insn_type == 0) {
        if (tid2flags[(int)dtid].call_flag) {
            tid2stack[(int)dtid].push(tt->ti[0].pc);
            //printf("push: %x\n", tt->ti[0].pc);
            if (tt->ti[0].pc == target_function_pc) {
                tid2flags[(int)dtid].specified_flag = true;
                //start_counts++;
                //printf("start_counts: %d\n", start_counts);
            }
            tid2flags[(int)dtid].call_flag = false;
        }
        if (ppi_instr_is_call_arch(tt->ti[real_insn_num - 1].instr)) {
            //printf("call_instr:%x   pc:%lx\n", tt->ti[real_insn_num - 1].instr, tt->ti[real_insn_num - 1].pc);
            tid2flags[(int)dtid].call_flag = true;
            //call_counts++;
            //printf("call_counts: %d\n", call_counts);
        }
        else if (ppi_instr_is_return(tt->ti[real_insn_num - 1].instr)) {
            //printf("ret_instr:%x   pc:%lx\n", tt->ti[real_insn_num - 1].instr, tt->ti[real_insn_num - 1].pc);
            //ret1_counts++;
            //printf("ret1_counts: %d\n", ret1_counts);
            if (!tid2stack[(int)dtid].empty()) {

                //ret2_counts++;
                //printf("ret2_counts: %d\n", ret2_counts);
                //printf("ret pop stack top : %lx\n", tid2stack[(int)dtid].top());
                if (tid2stack[(int)dtid].top() == target_function_pc) {
                    tid2flags[(int)dtid].ret_flag= true;
                }
                tid2stack[(int)dtid].pop();
            }
        }
    }
#endif
    pre_tb = true;   
    return true;
}




#endif


#ifdef VERBOSE
#    include <iostream>
#endif

ipc_reader_t::ipc_reader_t()
    : creation_success_(false)
{
    /* Empty. */
}

ipc_reader_t::ipc_reader_t(const char *ipc_name, int verbosity,int ins_print , int channel_d,bool only_usr)
    : reader_t(verbosity, "IPC")
    , pipe_(ipc_name)
{
    // We create the pipe here so the user can set up a pipe writer
    // *before* calling the blocking analyzer_t::run().
    ipc_ins_print = ins_print*10000;
    ipc_channel_d = channel_d;
    ipc_only_usr = only_usr;
#ifdef SHARE_MEM    
    creation_success_ = true;
    key_t key_insoff;
    char pathname[128];
    sprintf(pathname,"%s/qr/fok_insoff.key",getenv("HOME"));
    printf("key path = %s\n",pathname);
    key_insoff = ftok(pathname,0x03);
    if(key_insoff == -1){
        perror("ftok error");
        exit(1);
    }
    printf("keyinoff + channel_d = %lx\n",key_insoff+ipc_channel_d);
    ringbuf = new ringbuf_t;
    int r1 = ringbuf->ringbuf_init(sizeof(qrio_buff_t),RB_SIZE,key_insoff+ipc_channel_d);
    
    char shm_file_name[128];
    sprintf(shm_file_name,"%s/qr/%d/shm_temp_file_%d",getenv("HOME"),ipc_channel_d,ipc_channel_d);

    bool retval = shm_init(NULL,shm_file_name);
    if (retval == false) {
	 fprintf(stderr, "shm_init() failed!");
	 exit(EXIT_FAILURE);
    }
    get_shm_user_base();
    printf("alloc shmem success\n");
#else
    creation_success_ = pipe_.create();
#endif
#ifdef FUN_SPECIFY
    char temp[100];
    if (fgets(temp, 1000, target_file) != NULL) {
        target_function_pc=strtol(strtok(temp, "\n"),NULL,16);
        printf("target_function_pc= %lx\n", target_function_pc);
    }
    else {
        printf("can't read target_function_pc!!!\n");
    }
#endif
}

// Work around clang-format bug: no newline after return type for single-char operator.
// clang-format off
bool
ipc_reader_t::operator!()
// clang-format on
{
    return !creation_success_;
}

std::string
ipc_reader_t::get_pipe_name() const
{
    return pipe_.get_name();
}

bool
ipc_reader_t::init()
{
#ifdef SHARE_MEM
    printf(" in ipc reader init\n");
    return read_next_tb();
#else

    printf(" in ipc reader init  %d\n", creation_success_);
    at_eof_ = false;
    if (!creation_success_ || !pipe_.open_for_read())
        return false;
    pipe_.maximize_buffer();
    cur_buf_ = buf_;
    end_buf_ = buf_;
    ++*this;
    return true;
#endif
}

ipc_reader_t::~ipc_reader_t()
{
    pipe_.close();
    pipe_.destroy();
}

trace_entry_t *
ipc_reader_t::read_next_entry()
{   
#ifdef SHARE_MEM
    bool suc = true;
    if(r_idx >= real_insn_num && mem_r_idx >= qbuf->mem_num && reg_r_idx >= qbuf->reg_num){
	    suc = read_next_tb();
	    header = 1;
	    core_header = 1;
        el_type_header = 1;
        tid_cg_header = 1;
	    r_idx = 0;
	    mem_r_idx =0;
        reg_r_idx = 0;
    } 
    if (!suc){
	    cur_buf_ = buf_temp;   
	    cur_buf_->type = TRACE_TYPE_FOOTER;
	    cur_buf_->size = 0;
	    cur_buf_->addr = 0;
	    at_eof_ = true;
	    return cur_buf_;
    }
    if(core_header == 1){
	    buf_temp->type = TRACE_TYPE_CORE_ID;
	    buf_temp->size = sizeof(addr_t);
	    buf_temp->addr = (addr_t)cpu_id;
	    core_header = 0;
        
    }else if(header ==1){
	    buf_temp->type = TRACE_TYPE_PID;
	    buf_temp->size = sizeof(addr_t);
	    buf_temp->addr = (addr_t)dpid;
	    header = 0;

    }else if (el_type_header == 1) {
        buf_temp->type = TRACE_TYPE_EL_TYPE;
	if(ipc_only_usr)
          buf_temp->size = 0;
        else
	  buf_temp->size = 1;
        buf_temp->addr = (addr_t)qbuf->insn_type;
        el_type_header = 0;

    }
    else if (tid_cg_header == 1) {
        buf_temp->type = TRACE_TYPE_TID_CG;
        buf_temp->size = sizeof(addr_t);
        buf_temp->addr = (addr_t)dtid;
        tid_cg_header = 0;

    }else if (r_idx < real_insn_num){
       if (r_idx == real_insn_num - 1){
           buf_temp->is_bb_end = 1;  //bb ����
       }
       else if(r_idx == 0){
           buf_temp->is_bb_end = 2;  //bb ��ʼ
       }
       else {
           buf_temp->is_bb_end = 0;
       }
       if (r_idx == real_insn_num - 1 && r_idx == 0){
           buf_temp->is_bb_end = 3;
       }
	   ct +=1;
	   trace_info1_t *buf = (trace_info1_t *)&tt->ti[r_idx];
	   r_idx += 1;    
	   buf_temp->type = TRACE_TYPE_INSTR; 
	   buf_temp->size = sizeof(addr_t);
	   buf_temp->addr = (addr_t)buf->instr;
       buf_temp->pc = buf->pc;
	   buf_temp->hva = buf->hva;

    }else if(mem_r_idx < qbuf->mem_num){
	   mem_info_t *mem_buf = &qbuf->mi[mem_r_idx];
	   mem_r_idx +=1;
	   if ( mem_buf->type == MEM_LOAD ) {
		buf_temp->type = TRACE_TYPE_READ;
	   } else if ( mem_buf->type == MEM_STORE ) {
		buf_temp->type = TRACE_TYPE_WRITE;
	   }
	   //buf_temp->type =(mem_buf->type == 0)? TRACE_TYPE_READ: TRACE_TYPE_WRITE ;
	   buf_temp->size = sizeof(addr_t);
	   buf_temp->addr = (addr_t)mem_buf->addr;      
    }
    else if (reg_r_idx < qbuf->reg_num) {
        reg_info_t reg_info = qbuf->ri[reg_r_idx];
        reg_r_idx += 1;
        buf_temp->type = TRACE_TYPE_REG;
        buf_temp->size = sizeof(reg_info_t);
        buf_temp->addr = reg_info;
    }
    
    
    cur_buf_ = buf_temp;
    return cur_buf_; 
#else
    ++cur_buf_;
    if (cur_buf_ >= end_buf_) {
        ssize_t sz = pipe_.read(buf_, sizeof(buf_)); // blocking read
        if (sz < 0 || sz % sizeof(*end_buf_) != 0) {
            // We aren't able to easily distinguish truncation from a clean
            // end (we could at least ensure the prior entry was a thread exit
            // I suppose).
            cur_buf_ = buf_;
            cur_buf_->type = TRACE_TYPE_FOOTER;
            cur_buf_->size = 0;
            cur_buf_->addr = 0;
            at_eof_ = true;
            return cur_buf_;
        }
        cur_buf_ = buf_;
        end_buf_ = buf_ + (sz / sizeof(*end_buf_));
    }
    if (cur_buf_->type == TRACE_TYPE_FOOTER)
        at_eof_ = true;
    return cur_buf_;
#endif
}

#ifdef _QR_R_TB_COUNT_
static void
print_pid_map()
{
    printf("======usr=map=========\n");
    for (auto it1 = pid_usr_map_.begin(); it1 != pid_usr_map_.end(); ++it1) {
        printf("pid = %d , num = %d \n", it1->first, it1->second);
    }
    printf("======sys=map=========\n");
    for (auto it2 = pid_sys_map_.begin(); it2 != pid_sys_map_.end(); ++it2) {
        printf("pid = %d , num = %d \n", it2->first, it2->second);
    }
}
#endif
