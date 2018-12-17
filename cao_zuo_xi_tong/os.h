#include <stdio.h>
//状态
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
//阻塞原因
constexpr auto A = 4;
constexpr auto B = 5;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // 数据寄存器主要内容
	char * ir_reg; //指令寄存器主要内容
	int status; //状态 
	char reason; //阻塞原因
	struct _pcb *next;
}pcb;
class os {
private :
	pcb* free_pcb; // 空白进程控制块链
	pcb* ready_pcb = NULL; //就绪队列
	pcb* block_pcb; //阻塞队列
	pcb* now_pcb; //正在运行的进程
	int last_pid = 0; //最新的pid序号
	int pid_num = 0; //pid个数
public:
	os(); //完成初始化
	int add_process(char *irs); //添加新进程 irs为指令起始地址
	
};