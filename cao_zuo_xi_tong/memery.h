#include <stdio.h>
constexpr auto init_mem_size = 512;//��ʼ�ڴ��С
constexpr auto init_size = 32; //��ʼ��ʱÿ�����з���
constexpr auto null_project =  0; //�ձ����־
constexpr auto use_project =  1; //�ѷ����־
constexpr auto min_size = 2; //�������С��Ƭ
struct busy { //�ѷ�������
	int no; //�������
	int size; //��С
	int head; //��ʼ��ַ
	int status; //״̬ 0Ϊ�ձ��� 1Ϊ�ѷ���
	struct busy* next;
};
struct free { //���з�����
	int size; //��С
	int head; //��ʼ��ַ
	int status; //״̬ 0Ϊ�ձ��� 1Ϊ�ѷ���
	struct free* next;
};
typedef struct _mem_area { //�ڴ������
	struct busy* busy = NULL;//ʹ������
	struct free* free = NULL;//��������
	
}mem_area;

class memory {
public:
	char mem[init_mem_size]; //�ڴ�
	mem_area list;
	memory();
	int malloc(int size,int pid); //�����ڴ�
	void free(int pid); //�ͷ��ڴ�
	int mem_status(int address); 
	int write(int address,char *str);//-1Ϊʧ�� 1Ϊ�ɹ�
	char* read(int address); //���ص�ַ��Ӧ��ָ�� nullΪʧ��
	int length(int address);
	int busy_list();
	int free_list();
	int Length(char *);

};
