#include <stdio.h>
#include "os.h"
#pragma warning(disable:4996)
typedef struct _pro_count { //程序计数器
	int pcb_no; //pcb编号
	char *ir_index; //下一条指令位置
}pro_count;




class cpu {
private:
	int reg_1, reg_2, reg_3, reg_4; //四个寄存器
	int psw;//程序状态寄存器 临时存放当前pcb的status
	char *ir;//指令寄存器 临时保存当前执行的指令
	pcb* pcb_now; //程序计数器的一部分 临时存放当前执行的pcb 为了方便 改用指针
	int ir_index; //程序计数器的一部分 临时存放当前指令在内存块的位置
	int dr; //数据寄存器 存放x
	bool if_start = true; //true为开机 false为关机
public:
	cpu(); //构造函数 cpu实例化后执行其中的循环，直到开机状态失效后跳出循环
	void set_computer_status(bool if_run);


};