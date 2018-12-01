#include <stdio.h>

typedef struct _mem_area { //�ڴ������
	struct busy { //�ѷ�������
		int no; //���
		int size; //��С
		void * head; //��ʼ��ַ
		int status; //״̬
		struct busy* next;
	};
	struct free { //���з�����
		int no; //���
		int size; //��С
		void * head; //��ʼ��ַ
		int status; //״̬
		struct free* next;
	};
}mem_area;

class memory {
public:
	char mem[128][4]; //�ڴ�
	mem_area list;

	memory();
	char *malloc(int size);
	void free(char *add, int size);
	mem_area *mem_status();
	void write(char *address,char *str);
	void read(char *address);


};
