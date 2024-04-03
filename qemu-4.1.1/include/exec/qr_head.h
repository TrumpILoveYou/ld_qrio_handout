#ifndef _QR_HEAD_H_
#define _QR_HEAD_H_
#define PPI_QR_FUNC
#define PPI_QR_MEM
#define PPI_QR_REG_TRACE
#define _QR_QR_RIO_
#define _QR_INSERT_BL_
#define DUMP_FUNC
//#define GET_PID_IMMEDIATE
//#define _QR_VM_TIMER
//#define _QR_Q_TB_COUNT_
//#define _QR_Q_TB_COUNTALL_
//#define _QR_Q_PIDMAP_
//#define _QR_Q_TB_RECORD_
//#define COUNT_SWITCH_TB
//#define _QR_Q_BIND_CPU_
/* if on, qrtag will reset off */
//#define GET_PID_OFF

struct namefunc{
	char 		*nf_name;
	uint64_t	nf_addr;
};

#define LOW_SYSPID (10)


#ifdef UBUNTU4
#define HAVE_TASK_PID
#define TASK_OFF   (0x10)
#define HAVE_SWITCH      0xffff800000085be0UL
#define HAVE_PID_NR_NS      0xffff8000000e29d8UL
#define HAVE_TASK_PID_NR_NS 0xffff8000000e2b28UL
#endif

#ifdef LINUX5
#define HAVE_TASK_PID
#define HAVE_SWITCH        0xffffff8008202bc0UL
#define HAVE_PID_NR_NS     0xffffff800826dca0UL
//#define DEBUG_COMM  //tmp debug swap
#endif

#ifdef TEST5
#define HAVE_TASK_PID
#define HAVE_SWITCH      0xffff800010005438UL
#endif

#ifdef LINUX5
/* type for get_task_pid */
enum pid_type
{
	PIDTYPE_PID  = 0,
	PIDTYPE_TGID = 4,
};
#else
/* type for get_task_pid */
enum pid_type
{
	PIDTYPE_PID,
	PIDTYPE_TGID,
	PIDTYPE_PGID,
	PIDTYPE_SID,
	PIDTYPE_MAX,
};
#endif

//#define PP_QR_FORCE
#define MEM_LOAD	(0x1)
#define	MEM_STORE	(0x2)

#define REG_NONE   (0x0)
#define REG_READ   (0x1)
#define REG_WRITE  (0x2)

#define REG_NEW    (0x0)
#define REG_OLD    (0x1)

struct mem_info{
     unsigned long addr;
     unsigned int type;
};
typedef struct mem_info mem_info_t;

/* Author: Chaoyi Liang
 * **Register access information type**
 * To reduce the size of register access information, 
 *     we can use some 32ints to present the register access of an instruction.
 * 
 *  31    28 2726 25      21 2019 18      14 1312 11       7 6  5 4        0
 * +--------+----+----------+----+----------+----+----------+----+----------+
 * |  old?  |r/w?|   Reg4   |r/w?|   Reg3   |r/w?|   Reg2   |r/w?|   Reg1   |
 * +--------+----+----------+----+----------+----+----------+----+----------+
 * 
 * old?: old(0x1) if this reg info is from the former instruction, or
 *     new(0x0) if a new instruction begins.This flag is reserved for 
 *     unexpected need, if an instruction contains more than 4 register access.
 * Regx(Reg1, Reg2, Reg3, Reg4): register index.
 * r/w?: none(0x0) read(0x1) or write(0x2).
 * E.g., for ARM instruction: ADD R3, R1, R2,
 *   register info is: 0B 0000 00 00000 01 00011 00 00010 00 00001
 *                         new no       wt    R3 rd    R2 rd    R1
 *   It means: A new instruction begins, read R1, read R2, write R3.
 */
typedef unsigned int reg_info_t;


#define MAX_MEMINFOS 1100

#define MAX_REGINFOS 1100

struct qrio_buff{
    int real_insn_num;
    int cpu_id;
    int insn_type;		/* tb_insn's mode,system = 1,user = 0 */
    unsigned int pid;			
    unsigned int tgid;
    unsigned long current;    
    unsigned long offset;
    int mem_num;
    struct mem_info mi[MAX_MEMINFOS];
    int reg_num;
    reg_info_t ri[MAX_REGINFOS];
};
typedef struct qrio_buff qrio_buff_t;

struct trace_info{
    unsigned long pc;
    unsigned int instr;
    unsigned long hva;
};
typedef struct trace_info trace_info_t;

struct tb_trace{
    int insn_num;
    unsigned long pc_start;     /* tb first pc */
    struct trace_info ti[512];
};
typedef struct tb_trace tb_trace_t;

#define BLOCKS 300
#define RB_SIZE 300

extern int global_qrtag_flag;
#ifdef _QR_VM_TIMER
extern void ppi_set_timer(void);
#endif

#endif
