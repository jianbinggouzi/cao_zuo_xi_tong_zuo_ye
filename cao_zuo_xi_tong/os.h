#include <stdio.h>
typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // ���ݼĴ�����Ҫ����
	char * ir_reg; //ָ��Ĵ�����Ҫ����
	int status; //״̬
	char reason; //����ԭ��
	struct _pcb *next;
}pcb;
class os {
public :
	pcb* free_pcb; // �հ׽��̿��ƿ���
	pcb* ready_pcb; //��������
	pcb* block_pcb; //��������
	pcb* now_pcb; //�������еĽ���
};