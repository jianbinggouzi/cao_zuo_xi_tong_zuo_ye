#include <stdio.h>
#include "memery.h"
#include "file.h"
//״̬
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
//����ԭ��
constexpr auto A = 4;
constexpr auto B = 5;
constexpr auto NO_BLOCK = 6;
//Ĭ��ÿ������ִ�е�ʱ��Ƭ
constexpr auto TIME = 2;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // ���ݼĴ�����Ҫ����
	char * ir_reg; //ָ��Ĵ���ָ�� ָ���ڴ����ʼ��ַ ���Ž��̵������𲽺���
	int status; //״̬ 
	char reason; //����ԭ��
	struct _pcb *next;
	int surplus = TIME; //ʱ��Ƭ �ھ��������б�ʾʣ��ռ��ʱ��Ƭ �����������б�ʾʣ������ʱ��
}pcb;
class os {
public:
	pcb* free_pcb = NULL; // �հ׽��̿��ƿ���
	pcb* ready_pcb = NULL; //��������
	pcb* block_pcb = NULL; //��������
	pcb* run_pcb = NULL; //�������еĽ���ָ��
	int last_pid = 0; //���µ�pid���
	int pid_num = 0; //pid����
	memory *mem = NULL;

	os(memory *_mem); //��ɳ�ʼ��
	int add_process(char *irs,int size); //����½��� irsΪָ����ʼ��ַ��sizeΪ�����ڴ��С ����pid
	void dispatch(); //����
	int add_block_process(pcb* _pcb,int reason,int time); //����������� dispatch()�е��� pcb���ַ ԭ�� ����ʱ�� -1ʧ�� 1�ɹ�
	int move_block_process(pcb* _pcb); //����������ȡ�� -1ʧ�� 1�ɹ�
	void set_now_process_status(int _status, int _reason, int _time); //���õ�ǰ���еĽ���״̬ ʵ��ʹ����ֻ������cpu�������ó�����״̬
	void show_all_ready();
	void show_all_block();
	char *read_id_reg(); //��ȡָ�� ��ir_reg��ʼ���� ; ������ir_reg���� ����ֵΪָ������ ע���޽�����0 ������sizeof()�жϳ���
};