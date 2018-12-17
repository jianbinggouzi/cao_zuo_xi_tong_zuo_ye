#include <stdio.h>
#include "memery.h"
//状态
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
//阻塞原因
constexpr auto A = 4;
constexpr auto B = 5;
constexpr auto NO_BLOCK = 6;
//默认每个进程的时间片
constexpr auto TIME = 5;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // 数据寄存器主要内容
	char * ir_reg; //指令寄存器主要内容
	int status; //状态 
	char reason; //阻塞原因
	struct _pcb *next;
	int surplus = TIME; //时间片 在就绪队列中表示剩余占用时间片 在阻塞队列中表示剩余阻塞时间
}pcb;
class os {
private :
	pcb* free_pcb = NULL; // 空白进程控制块链
	pcb* ready_pcb = NULL; //就绪队列
	pcb* block_pcb = NULL; //阻塞队列
	pcb* run_pcb = NULL; //正在运行的进程指针
	int last_pid = 0; //最新的pid序号
	int pid_num = 0; //pid个数
	memory *mem = NULL;
public:
	os(memory *_mem); //完成初始化
	int add_process(char *irs,int size); //添加新进程 irs为指令起始地址，size为所需内存大小
	void dispatch(); //调度
	
};