#include <stdio.h>
typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // 数据寄存器主要内容
	char * ir_reg; //指令寄存器主要内容
	int status; //状态
	char reason; //阻塞原因
	struct _pcb *next;
}pcb;
class os {
public :
	pcb* free_pcb; // 空白进程控制块链
	pcb* ready_pcb; //就绪队列
	pcb* block_pcb; //阻塞队列
	pcb* now_pcb; //正在运行的进程
};