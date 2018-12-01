#include <stdio.h>

typedef struct _mem_area { //�ڴ������
	struct busy { //�ѷ�������
		int no; //�������
		int size; //��С
		void * head; //��ʼ��ַ
		int status; //״̬ 0Ϊ�ձ��� 1Ϊ�ѷ���
		struct busy* next;
	};
	struct free { //���з�����
		int size; //��С
		void * head; //��ʼ��ַ
		int status; //״̬ 0Ϊ�ձ��� 1Ϊ�ѷ���
		struct free* next;
	};
}mem_area;

class memory {
public:
	char mem[512]; //�ڴ�
	mem_area list;

	memory();
	char *malloc(int size); //�����ڴ�
	void free(char *address); //�ͷ��ڴ�
	int mem_status(char *address); //
	void write(char *address,char *str);
	void read(char *address);
	int length(char *address);
	int busy_list();
	int free_list();


};
