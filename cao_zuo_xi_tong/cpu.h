#include <stdio.h>
#include "os.h"
#pragma warning(disable:4996)
typedef struct _pro_count { //���������
	int pcb_no; //pcb���
	char *ir_index; //��һ��ָ��λ��
}pro_count;




class cpu {
private:
	int reg_1, reg_2, reg_3, reg_4; //�ĸ��Ĵ���
	int psw;//����״̬�Ĵ��� ��ʱ��ŵ�ǰpcb��status
	char *ir;//ָ��Ĵ��� ��ʱ���浱ǰִ�е�ָ��
	char *ir_reg;//��һ��ָ��Ĵ���
	pcb* pcb_now; //�����������һ���� ��ʱ��ŵ�ǰִ�е�pcb Ϊ�˷��� ����ָ��
	int dr; //���ݼĴ��� ���x
	bool if_start = false; //trueΪ���� falseΪ�ػ�
	os *_os;
	int cpu_time = 0;
public:
	cpu();
	void set_computer_status(bool if_run , os* os);//���ÿ��ػ�
	void run(); //��ʼ��������if_startΪfalseʱֹͣ����
	bool get_status(); 
	void do_ir();//ʶ��ָ�ִ��
	pcb* get_now_pcb();
	int get_cpu_time();
	char* get_ir();
	int get_dr();

};