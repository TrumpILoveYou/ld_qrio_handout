#ifndef _QR_HEAD_H_
#define _QR_HEAD_H_
//#define _QR_Q_TB_COUNT_

//#define THREAD_FLAG_FUN  0xffff800000086370UL
//#define THREAD_FLAG_FUN  0xffffff80082057ecUL
//#define THREAD_FLAG_FUN  0xffffff800826413cUL //getpid
//#define HAVE_SWITCH      0xffffff800820612cUL //fz

//#define THREAD_FLAG_FUN  0xffff0000100854bcUL
#define DUMP_FUNC


#ifdef UBUNTU4
#define TASK_OFF   (0x10)
//#define TASK_COMM        0xffff800000260808UL //get_task_comm
//#define HAVE_SWITCH      0xffff800000086bc0UL
#define HAVE_SWITCH      0xffff800000085be0UL
#endif

#ifdef LINUX4
#endif

#ifdef LINUX5
//#define TASK_COMM        	0xffffff80083985f0UL 
#define HAVE_SWITCH      	0xffffff8008202bc0UL
#define have_sys_getpid       	0xffffff800826413cUL
#define have_sys_gettid       	0xffffff8008264168UL
#define have_task_active_pid_ns 0xffffff800826da14UL
#define have_task_pid_nr_ns    	0xffffff800826dd38UL
#define have_pid_nr_ns       	0xffffff800826dca0UL

#endif

#ifdef TEST5
#define TASK_COMM        0xffff0000102454e8UL 
#define HAVE_SWITCH      0xffff0000100854bcUL
#endif

/* type for get_task_pid */
enum pid_type
{
	PIDTYPE_PID,
	PIDTYPE_TGID,
	PIDTYPE_PGID,
	PIDTYPE_SID,
	PIDTYPE_MAX,
};

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

typedef unsigned int reg_info_t;


struct qrio_buff{
    int real_insn_num;
    int cpu_id;
    int insn_type;		/* tb_insn's mode,system = 1,user = 0 */
    unsigned int pid;			
    unsigned int tgid;
    unsigned long current;    
    unsigned long offset;
    int mem_num;
    struct mem_info mi[1100];
    int reg_num;
    reg_info_t ri[1100];
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

#endif
