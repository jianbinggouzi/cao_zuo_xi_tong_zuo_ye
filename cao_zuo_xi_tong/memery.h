#include <stdio.h>

class memory {
public:
	char mem[128][4]; //内存
	struct mem_area { //内存分区表
		struct busy { //已分区区表
			int no; //序号
			int size; //大小
			void * head; //起始地址
			int status; //状态
		};
		struct free { //空闲分区表
			int no; //序号
			int size; //大小
			void * head; //起始地址
			int status; //状态
		};
	};
};
