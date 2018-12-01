#include <stdio.h>

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // ���ݼĴ�����Ҫ����
	char * ir_reg; //ָ��Ĵ�����Ҫ����
	int status; //״̬
	char reason; //����ԭ��
	struct _pcb *next;
}pcb;

class com {
public:
	char mem[128][4]; //�ڴ�
	int reg_1, reg_2, reg_3, reg_4; //�ĸ��Ĵ���
	char *ir;//ָ��Ĵ���
	typedef struct _pro_count { //���������
		int pcb_no; //pcb���
		char *ir_index; //��һ��ָ��λ��
	}pro_count;
	int dr; //���ݼĴ��� ���x
	pcb* free_pcb; // �հ׽��̿��ƿ���
	pcb* ready_pcb; //��������
	pcb* block_pcb; //��������
	pcb* now_pcb; //�������еĽ���
	struct mem_area { //�ڴ������
		struct busy { //�ѷ�������
			int no; //���
			int size; //��С
			void * head; //��ʼ��ַ
			int status; //״̬
		};
		struct free { //���з�����
			int no; //���
			int size; //��С
			void * head; //��ʼ��ַ
			int status; //״̬
		};
	};
};
