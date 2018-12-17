#include<stdio.h>
#pragma warning(disable:4996)
typedef struct _pro_count { //程序计数器
	int pcb_no; //pcb编号
	char *ir_index; //下一条指令位置
}pro_count;




class cpu {
public:

	int reg_1, reg_2, reg_3, reg_4; //四个寄存器
	int psw;//程序状态寄存器
	int time;//时间片寄存器
	char *ir;//指令寄存器
	int ndr, npsw, nti;
	pro_count np;
	char *nir;

	//char *nir;
	pro_count pc;//程序计数器
	int dr; //数据寄存器 存放x
	cpu();
	int GetTime();//获得当前时间片
	int GetPsw();//获得psw
	char* GetIr();//获得Ir
	void SetTime(int t);//设置时间片寄存器
	void SetPsw(int p);//设置psw寄存器
	void SetIr(char a[], int n);//设置Ir寄存器



	void DisposeIR();
	bool JudgeState();

	void SetInterrupt(int p);//设置中断
	void ClearInterrupt();//清理中断
	void DealInterrupt();//处理中断
	void DealIointer();//处理Io中断
	void DealSoftint();//处理软中断
	void DealTimeint();//处理时间中断


	void SaveState();
	void BakcState();//中断后恢复状态


};