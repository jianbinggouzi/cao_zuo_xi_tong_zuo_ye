#include <stdio.h>
constexpr auto init_size = 8; //��ʼ��ʱÿ�����з���
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
	struct busy* busy;
	struct free* free;
	
}mem_area;

class memory {
public:
	char mem[512]; //�ڴ�
	mem_area list;

	memory();
	int malloc(int size,int pid); //�����ڴ�
	void free(int address); //�ͷ��ڴ�
	int mem_status(char *address); //
	void write(char *address,char *str);
	void read(char *address);
	int length(char *address);
	int busy_list();
	int free_list();


};
