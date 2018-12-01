#include <stdio.h>

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // 数据寄存器主要内容
	char * ir_reg; //指令寄存器主要内容
	int status; //状态
	char reason; //阻塞原因
	struct _pcb *next;
}pcb;

class com {
public:
	char mem[128][4]; //内存
	int reg_1, reg_2, reg_3, reg_4; //四个寄存器
	char *ir;//指令寄存器
	typedef struct _pro_count { //程序计数器
		int pcb_no; //pcb编号
		char *ir_index; //下一条指令位置
	}pro_count;
	int dr; //数据寄存器 存放x
	pcb* free_pcb; // 空白进程控制块链
	pcb* ready_pcb; //就绪队列
	pcb* block_pcb; //阻塞队列
	pcb* now_pcb; //正在运行的进程
	struct mem_area { //内存分区表
		struct busy { //已分区区表
			int no; //序号
			int size; //大小
			void * head; //起始地址
			int status; //状态
		};
		struct free { //空闲分区表
			int no; //序号
			int size; //大小
			void * head; //起始地址
			int status; //状态
		};
	};
};
