#include <stdio.h>
#include "memery.h"
//״̬
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
//����ԭ��
constexpr auto A = 4;
constexpr auto B = 5;
constexpr auto NO_BLOCK = 6;
//Ĭ��ÿ�����̵�ʱ��Ƭ
constexpr auto TIME = 5;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // ���ݼĴ�����Ҫ����
	char * ir_reg; //ָ��Ĵ�����Ҫ����
	int status; //״̬ 
	char reason; //����ԭ��
	struct _pcb *next;
	int surplus = TIME; //ʱ��Ƭ �ھ��������б�ʾʣ��ռ��ʱ��Ƭ �����������б�ʾʣ������ʱ��
}pcb;
class os {
private :
	pcb* free_pcb = NULL; // �հ׽��̿��ƿ���
	pcb* ready_pcb = NULL; //��������
	pcb* block_pcb = NULL; //��������
	pcb* run_pcb = NULL; //�������еĽ���ָ��
	int last_pid = 0; //���µ�pid���
	int pid_num = 0; //pid����
	memory *mem = NULL;
public:
	os(memory *_mem); //��ɳ�ʼ��
	int add_process(char *irs,int size); //����½��� irsΪָ����ʼ��ַ��sizeΪ�����ڴ��С
	void dispatch(); //����
	
};