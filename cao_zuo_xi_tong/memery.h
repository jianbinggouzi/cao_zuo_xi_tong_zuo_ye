#include <stdio.h>

typedef struct _mem_area { //内存分区表
	struct busy { //已分区区表
		int no; //序号
		int size; //大小
		void * head; //起始地址
		int status; //状态
		struct busy* next;
	};
	struct free { //空闲分区表
		int no; //序号
		int size; //大小
		void * head; //起始地址
		int status; //状态
		struct free* next;
	};
}mem_area;

class memory {
public:
	char mem[128][4]; //内存
	mem_area list;

	memory();
	char *malloc(int size);
	void free(char *add, int size);
	mem_area *mem_status();
	void write(char *address,char *str);
	void read(char *address);


};
