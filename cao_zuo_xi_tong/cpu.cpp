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

void cpu::SetInterrupt(int p)//�����ж�
{
	psw = p;
}
void cpu::ClearInterrupt()
{
	psw = 0;
	//��ǣ�����Ľ�
}
bool cpu::JudgeState()//�ж��Ƿ�����ж�
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
void cpu::SaveState()//���浱ǰ״̬
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
void cpu::DealInterrupt()//�����ж�
{

}
void cpu::DealIointer()//����Io�ж�
{
	SaveState();
	int ioPcbno;
	ioPcbno = np.pcb_no;
	pro_count iop;
	if (ioPcbno == -1)
	{
		//��ǣ����г���IO�жϴ���
	}
	ClearInterrupt();
}
void cpu::DealSoftint()
{
	SaveState();
	//��ǣ����г������ж�
	ClearInterrupt();

}
void cpu::DealTimeint()
{
	SaveState();
	//��ǣ�����ʱ���ж�
	ClearInterrupt();
}
void cpu::DisposeIR()//cpu����ָ��
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