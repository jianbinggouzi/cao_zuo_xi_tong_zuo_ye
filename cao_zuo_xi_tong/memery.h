#include <stdio.h>

class memory {
public:
	char mem[128][4]; //�ڴ�
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
