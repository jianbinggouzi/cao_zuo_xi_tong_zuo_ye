#include"cpu.h"
#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<tchar.h>

using namespace std;

cpu::cpu()
{
	if (JudgeState() == true)
	{

	}
}
int cpu::GetTime()
{
	return time;
}
int cpu::GetPsw()
{
	return psw;
}
char* cpu::GetIr()
{
	return ir;
}
void cpu::SetTime(int t)
{
	time = t;
}
void cpu::SetPsw(int p)
{
	psw = p;
}
void cpu::SetIr(char a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		*(ir + i) = a[i];
	}
}

void cpu::SetInterrupt(int p)//设置中断
{
	psw = p;
}
void cpu::ClearInterrupt()
{
	psw = 0;
	//标记：：需改进
}
bool cpu::JudgeState()//判断是否存在中断
{
	if (psw == 1 && psw == 2 && psw == 4)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void cpu::SaveState()//保存当前状态
{
	nir = new char[4];
	_tcscpy(nir, ir);
	ndr = dr;
	npsw = psw;
	np = pc;
	nti = time;
}
void cpu::BakcState()
{
	_tcscpy(ir, nir);
	dr = ndr;
	psw = npsw;
	pc = np;
	time = nti;

}
void cpu::DealInterrupt()//处理中断
{

}
void cpu::DealIointer()//处理Io中断
{
	SaveState();
	int ioPcbno;
	ioPcbno = np.pcb_no;
	pro_count iop;
	if (ioPcbno == -1)
	{
		//标记：进行程序IO中断处理
	}
	ClearInterrupt();
}
void cpu::DealSoftint()
{
	SaveState();
	//标记：进行程序软中断
	ClearInterrupt();

}
void cpu::DealTimeint()
{
	SaveState();
	//标记：处理时间中断
	ClearInterrupt();
}
void cpu::DisposeIR()//cpu处理指令
{
	string str;
	str = ir;
	if (str.compare("x++;") == 1)
	{
		dr++;
		pc.pcb_no++;
	}
	else if (str.compare("x--;") == 1)
	{
		dr--;
		pc.pcb_no++;
	}
	else if (str.compare("x=1;") == 1)
	{
		dr = 1;
		pc.pcb_no++;
	}
	else if (str.compare("end;") == 1)
	{
		//todo 
	}
	else if (str.compare("!=A9;") == 1)
	{


	}



}