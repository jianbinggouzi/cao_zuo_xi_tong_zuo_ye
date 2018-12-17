#include "os.h"

os::os(memory *_mem)
{
	//初始化内存
	mem = _mem;
	//为闲逛进程申请内存
	int address = mem->malloc(8, last_pid);
	//添加闲逛进程
	ready_pcb = new pcb();
	ready_pcb->pid = last_pid++;
	ready_pcb->data_reg = 0;
	ready_pcb->ir_reg = mem->mem + address;
	ready_pcb->status = READY;
	ready_pcb->reason = NO_BLOCK;
	ready_pcb->next = NULL;
	pid_num++;
	run_pcb = ready_pcb;
	//初始化后 闲逛进程永远处于就绪队列第一位 删除进程时也不会删除闲逛进程
}

int os::add_process(char * irs,int size)
{
	pcb *p = ready_pcb;
	while (p != NULL) {
		p = p->next;
	}
	int address = mem->malloc(size, last_pid);

	p = new pcb();
	p->pid = last_pid++;
	p->data_reg = 0;
	p->ir_reg = mem->mem + address;
	p->status = READY;
	p->reason = NO_BLOCK;
	p->next = NULL;
	pid_num++;
}

void os::dispatch()
{
	if (run_pcb == NULL)
		run_pcb = ready_pcb;
	run_pcb->surplus--;
	//执行一条指令
	if (run_pcb->surplus == 0) {
		run_pcb->surplus = TIME;
		run_pcb = run_pcb->next;
	}
}
