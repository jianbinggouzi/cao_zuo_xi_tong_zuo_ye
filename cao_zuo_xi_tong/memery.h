#include <stdio.h>

typedef struct _mem_area { //内存分区表
	struct busy { //已分区区表
		int no; //进程序号
		int size; //大小
		void * head; //起始地址
		int status; //状态 0为空表项 1为已分配
		struct busy* next;
	};
	struct free { //空闲分区表
		int size; //大小
		void * head; //起始地址
		int status; //状态 0为空表项 1为已分配
		struct free* next;
	};
}mem_area;

class memory {
public:
	char mem[512]; //内存
	mem_area list;

	memory();
	char *malloc(int size); //申请内存
	void free(char *address); //释放内存
	int mem_status(char *address); //
	void write(char *address,char *str);
	void read(char *address);
	int length(char *address);
	int busy_list();
	int free_list();


};
