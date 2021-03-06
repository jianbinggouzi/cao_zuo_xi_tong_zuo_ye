#include <stdio.h>
#include "memery.h"
#include "file.h"
//状态
constexpr auto READY = 0;
constexpr auto BLOCK = 1;
constexpr auto RUN = 3;
constexpr auto FINISH = 7;
//阻塞原因
constexpr auto A = 4;
constexpr auto B = 5;
constexpr auto NO_BLOCK = 6;
constexpr auto END = 8;
//默认每个进程执行的时间片
constexpr auto TIME = 2;

typedef struct _pcb { //pcb
	int pid; //ID
	int data_reg; // 数据寄存器主要内容
	char *ir = NULL; //当前执行指令寄存器 
	char * ir_reg; //下一条指令寄存器  
	
	int status; //状态 
	char reason; //阻塞原因
	struct _pcb *next;
	int surplus = TIME; //时间片 在就绪队列中表示剩余占用时间片 在阻塞队列中表示剩余阻塞时间
}pcb;
class os {
public:
	pcb* free_pcb = NULL; // 空白进程控制块链
	pcb* ready_pcb = NULL; //就绪队列
	pcb* block_pcb = NULL; //阻塞队列
	pcb* run_pcb = NULL; //正在运行的进程指针
	pcb* finish_pcb = NULL; //已完成队列  调度用不到  只给图形界面用
	int last_pid = 0; //最新的pid序号
	int pid_num = 0; //pid个数
	memory *mem = NULL;
	int not_read = 0; //给前台使用

	os(memory *_mem); //完成初始化
	int add_process(int size); //添加新进程 size为所需内存大小 返回pid
	void dispatch(); //调度
	int add_block_process(pcb* _pcb,int reason,int _time); //添加阻塞进程 dispatch()中调用 pcb快地址 原因 阻塞时间 -1失败 1成功
	int move_block_process(pcb* _pcb); //从阻塞队列取出 -1失败 1成功
	void set_now_process_status(int _status, int _reason, int _time); //设置当前运行的进程状态 实际使用中只用来供cpu调用设置成阻塞状态
	void show_all_ready();
	void show_all_block();
	void show_all_finish();
	char *read_id_reg(); //读取指令 从ir_reg开始读到 ; 并设置ir_reg后移 返回值为指令内容 注意无结束符0 所以用sizeof()判断长度
	int move_finished_process(pcb* _pcb); //从ready中删除已完成进程
	pcb* get_running_pcb(); //返回当前pcb指针
};