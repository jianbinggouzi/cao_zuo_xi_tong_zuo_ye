#include<stdio.h>
#pragma warning(disable:4996)
typedef struct _pro_count { //���������
	int pcb_no; //pcb���
	char *ir_index; //��һ��ָ��λ��
}pro_count;




class cpu {
public:

	int reg_1, reg_2, reg_3, reg_4; //�ĸ��Ĵ���
	int psw;//����״̬�Ĵ���
	int time;//ʱ��Ƭ�Ĵ���
	char *ir;//ָ��Ĵ���
	int ndr, npsw, nti;
	pro_count np;
	char *nir;

	//char *nir;
	pro_count pc;//���������
	int dr; //���ݼĴ��� ���x
	cpu();
	int GetTime();//��õ�ǰʱ��Ƭ
	int GetPsw();//���psw
	char* GetIr();//���Ir
	void SetTime(int t);//����ʱ��Ƭ�Ĵ���
	void SetPsw(int p);//����psw�Ĵ���
	void SetIr(char a[], int n);//����Ir�Ĵ���



	void DisposeIR();
	bool JudgeState();

	void SetInterrupt(int p);//�����ж�
	void ClearInterrupt();//�����ж�
	void DealInterrupt();//�����ж�
	void DealIointer();//����Io�ж�
	void DealSoftint();//�������ж�
	void DealTimeint();//����ʱ���ж�


	void SaveState();
	void BakcState();//�жϺ�ָ�״̬


};