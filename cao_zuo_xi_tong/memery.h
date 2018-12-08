#include <stdio.h>
constexpr auto init_size = 8; //初始化时每个空闲分区
constexpr auto null_project =  0; //空表项标志
constexpr auto use_project =  1; //已分配标志
constexpr auto min_size = 2; //允许的最小碎片
struct busy { //已分区区表
	int no; //进程序号
	int size; //大小
	int head; //起始地址
	int status; //状态 0为空表项 1为已分配
	struct busy* next;
};
struct free { //空闲分区表
	int size; //大小
	int head; //起始地址
	int status; //状态 0为空表项 1为已分配
	struct free* next;
};
typedef struct _mem_area { //内存分区表
	struct busy* busy;
	struct free* free;
	
}mem_area;

class memory {
public:
	char mem[512]; //内存
	mem_area list;

	memory();
	int malloc(int size,int pid); //申请内存
	void free(int address); //释放内存
	int mem_status(char *address); //
	void write(char *address,char *str);
	void read(char *address);
	int length(char *address);
	int busy_list();
	int free_list();


};
