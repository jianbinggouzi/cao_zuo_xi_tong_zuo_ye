#include <stdio.h>
//״̬
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
//����ԭ��
constexpr auto A = 4;
constexpr auto B = 5;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // ���ݼĴ�����Ҫ����
	char * ir_reg; //ָ��Ĵ�����Ҫ����
	int status; //״̬ 
	char reason; //����ԭ��
	struct _pcb *next;
}pcb;
class os {
private :
	pcb* free_pcb; // �հ׽��̿��ƿ���
	pcb* ready_pcb = NULL; //��������
	pcb* block_pcb; //��������
	pcb* now_pcb; //�������еĽ���
	int last_pid = 0; //���µ�pid���
	int pid_num = 0; //pid����
public:
	os(); //��ɳ�ʼ��
	int add_process(char *irs); //����½��� irsΪָ����ʼ��ַ
	
};