#include <stdio.h>

class cpu {
public:
	
	int reg_1, reg_2, reg_3, reg_4; //四个寄存器
	char *ir;//指令寄存器
	typedef struct _pro_count { //程序计数器
		int pcb_no; //pcb编号
		char *ir_index; //下一条指令位置
	}pro_count;
	int dr; //数据寄存器 存放x
	
	
};
