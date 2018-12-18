#include "os.h"

os::os(memory *_mem)
{
	//初始化内存
	mem = _mem;
	//为闲逛进程申请内存
	int address = mem->malloc(8, last_pid);
	char idle[] = "x=0;gob;";
	if (mem->write(address, idle) == 1) {
		printf("闲逛进程写入成功\n");
	}
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
	while (p->next != NULL) {
		p = p->next;
	}
	//申请一块新内存
	int address = mem->malloc(size, last_pid);

	//向内存中写入指令
	char filename[10];
	memset(filename, 0, 10);
	sprintf_s(filename, "%d.c", last_pid);
	if (mem->write(address, (new file)->load_file(filename)) == -1) {
		printf("载入新进程文件失败\n");
		mem->free(last_pid);
		return -1;
	}
	else {
		printf("指令成功载入 ");
	}
	
	p->next = new pcb();
	p = p->next;
	p->pid = last_pid++;
	p->data_reg = 0;
	p->ir_reg = mem->mem + address;
	p->status = READY;
	p->reason = NO_BLOCK;
	p->next = NULL;
	pid_num++;
	printf("新载入一条进程,address:%d,size:%d,pid:%d\n", address, size, last_pid - 1);
	return last_pid - 1;
}

void os::dispatch()
{
	//将阻塞队列内所有pcb时间片-1 如果阻塞时间片用完 加入到ready队列中
	pcb* p = block_pcb;
	while (p != NULL) {
		p->surplus--;
		if (p->surplus <= 0) {
			move_block_process(p);
		}
		p = p->next;
	}

	//如果到达准备序列结尾 从头开始
	if (run_pcb == NULL) {
		run_pcb = ready_pcb;
		run_pcb->status = RUN;
	}
	
	run_pcb->surplus--;
	//检查当前的pcb是否被cpu设置为阻塞状态 如果有 加入到阻塞队列并立即调度
	if (run_pcb->status == BLOCK) {
		add_block_process(run_pcb, run_pcb->reason, run_pcb->surplus);
		run_pcb = run_pcb->next;
		return;
	}
	//如果没有堵塞 继续检查时间片是否用完 如果用完 run_pcb指向下一个pcb 
	if (run_pcb->surplus == 0) {
		run_pcb->surplus = TIME;
		run_pcb = run_pcb->next;
	}

}

int os::add_block_process(pcb* _pcb,int reason,int time)
{
	pcb *p = ready_pcb;
	int if_find = -1;
	while (p->next != NULL) {
		if (p->next == _pcb) {
			//从ready_pcb链表中删除
			p->next = p->next->next;
			if_find = 1;
			break;
		}
		p = p->next;
	}
	if (if_find == -1) {
		printf("os::add_block_process:未找到对应pcb\n");
		return -1;
	}
	
	_pcb->reason = reason;
	_pcb->surplus = time;
	_pcb->status = BLOCK;
	_pcb->next = NULL;
	//添加到block_pcb中
	if (block_pcb == NULL) {
		block_pcb = _pcb;
	}
	else {
		p = block_pcb;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = _pcb;
	}
	
	return 1;
}

int os::move_block_process(pcb * _pcb)
{
	int if_find = -1;
	pcb *p = block_pcb;
	if (p == NULL) {
		printf("os::move_block_process:阻塞队列为空\n");
		return -1;
	}
	//阻塞队列只有一个块
	if (p->next == NULL) {
		if (p != _pcb) {
			printf("os::move_block_process:未找到对应pcb\n");
			return -1;
		}
	}
	//大于1个
	else {
		while (p->next != NULL) {
			if (p->next == _pcb) {
				p->next = p->next->next;
				if_find = 1;
				break;
			}
			p = p->next;
		}
	}
	
	p = ready_pcb;
	while (p->next != NULL) {
		p = p->next;
	}
	_pcb->status = READY;
	_pcb->reason = NO_BLOCK;
	_pcb->surplus = TIME;
	_pcb->next = NULL;
	p->next = _pcb;
	return 1;
}

void os::set_now_process_status(int _status, int _reason, int _time)
{
	run_pcb->status = _status;
	run_pcb->reason = _reason;
	run_pcb->surplus = _time;
}

void os::show_all_ready()
{
	pcb *p = ready_pcb;
	printf("ready:\n");
	while (p != NULL) {
		printf("pid:%d,address:%p,time:%d\n", p->pid,p->ir_reg,p->surplus);
		p = p->next;
	}
}

void os::show_all_block()
{
	pcb *p = block_pcb;
	printf("block:\n");
	while (p != NULL) {
		printf("pid:%d,address:%p,time:%d\n", p->pid, p->ir_reg,p->surplus);
		p = p->next;
	}
}


