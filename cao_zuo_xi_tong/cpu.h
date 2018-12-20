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
	char *ir_reg;//下一条指令寄存器
	pcb* pcb_now; //程序计数器的一部分 临时存放当前执行的pcb 为了方便 改用指针
	int dr; //数据寄存器 存放x
	bool if_start = false; //true为开机 false为关机
	os *_os;
	int cpu_time = 0;
public:
	cpu();
	void set_computer_status(bool if_run , os* os);//设置开关机
	void run(); //开始工作，当if_start为false时停止运行
	bool get_status(); 
	void do_ir();//识别指令并执行
	pcb* get_now_pcb();
	int get_cpu_time();
	char* get_ir();
	int get_dr();

};