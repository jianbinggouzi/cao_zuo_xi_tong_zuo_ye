#include "os.h"

os::os(memory *_mem)
{
	//初始化内存
	mem = _mem;
	//为闲逛进程申请内存
	int address = mem->malloc(8, last_pid);
	printf("闲逛进程address值:%d\n",address);
	char idle[] = "x=0;gob;";
	printf("---------%d\n", sizeof(idle));
	if (mem->write(address, idle) == 1) {
		printf("闲逛进程写入成功\n");
	}
	printf("闲逛进程内存块内容:%s\n", (mem->mem) + address);
	//添加闲逛进程
	ready_pcb = new pcb();
	ready_pcb->pid = last_pid++;
	ready_pcb->data_reg = 0;
	ready_pcb->ir_reg = mem->mem + address;
	printf("创建时ir_reg=%d\n", ready_pcb->ir_reg);
	ready_pcb->status = READY;
	ready_pcb->reason = NO_BLOCK;
	ready_pcb->next = NULL;
	pid_num++;
	run_pcb = ready_pcb;
	//初始化后 闲逛进程永远处于就绪队列第一位 删除进程时也不会删除闲逛进程
}

int os::add_process(int size)
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
	show_all_ready();
	show_all_block();
	//将阻塞队列内所有pcb时间片-1 如果阻塞时间片用完 唤醒该进程
	pcb* p = block_pcb;	
	while (p != NULL) {
		printf("检查阻塞：当前pid = %d .time = %d", p->pid, p->surplus);
		p->surplus--;
		printf("--------------\n");
		if (p->surplus <= 0) {
			printf("发现pid = %d时间片用完", p->pid);
			move_block_process(p);
		}

		p = p->next;
	}
	//检查当前的pcb中是否有被cpu设置为完成状态 如果有 从就绪队列中删除
	pcb *p1 = ready_pcb;
	while (p1 != NULL) {
		if (p1->status == FINISH) {
			printf("发现一个完成 pid= %d\n", p1->pid);
			move_finished_process(p1);
			
		}
		p1 = p1->next;
	}
	
	//时间片-1
	run_pcb->surplus--;
	//一次读取一条指令
	run_pcb->ir = read_id_reg();
	if (run_pcb->pid == 0) {
		run_pcb->ir = mem->mem + 0;
		run_pcb->ir_reg = mem->mem + 0;
	}
	printf("pid:%d读取到指令%s\n",run_pcb->pid, run_pcb->ir);		

	

}

int os::move_finished_process(pcb* _pcb)
{
	printf("pid:%d完成\n", _pcb->pid);
	if (_pcb == ready_pcb) {
		ready_pcb = ready_pcb->next;
	}
	else {
		pcb* p = ready_pcb;
		while (p->next != _pcb) {
			if (p->next == NULL) {
				printf("os::move_finished_process:未在ready中找到pid=%d\n", _pcb->pid);
				return -1;
			}
			p = p->next;
		}
		pcb* temp = p->next;
		p->next = p->next->next;

	}
	return 1;
}

pcb * os::get_running_pcb()
{
	return run_pcb;
}

int os::add_block_process(pcb* _pcb,int reason,int _time)
{
	printf("添加pid=%d 到阻塞中,time=%d\n", _pcb->pid, _time);
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
		printf("os::add_block_process:未找到对应pcb:%d\n",_pcb->pid);
		return -1;
	}
	
	_pcb->reason = reason;
	_pcb->surplus = _time;
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
	printf("从阻塞队列中移除pid=%d\n", _pcb->pid);
	int if_find = -1;
	pcb *p = block_pcb;
	if (p == NULL) {
		printf("os::move_block_process:阻塞队列为空\n");
		return -1;
	}
	
	//_pcb位于第一位
	if (_pcb == block_pcb) {
		block_pcb = block_pcb->next;
	}
	else {
		while (p->next != _pcb) {
			if (p->next == NULL || p == NULL) {
				printf("os::move_block_process:未在阻塞队列中找到pid=%d\n", _pcb->pid);
				return -1;
			}
			p = p->next;
		}
		p->next = p->next->next;
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
		printf("pid:%d,address:%p,time:%d, status%d\n", p->pid,p->ir_reg,p->surplus,p->status);
		p = p->next;
	}
}

void os::show_all_block()
{
	pcb *p = block_pcb;
	printf("block:\n");
	while (p != NULL) {
		printf("pid:%d,address:%p,status:%d,time:%d\n", p->pid, p->ir_reg,p->status,p->surplus);
		p = p->next;
	}
}

char * os::read_id_reg()
{
	int length = 1;
	if (run_pcb->pid == 0) {
		char t[] = "x=0;";
		return t;
	}
	show_all_ready();
	show_all_block();
	printf("pid = %d-----------------\n", run_pcb->pid);
	while (*(run_pcb->ir_reg + length -1) != ';') {
		length++;
	}
	char *res = new char[length];
	for (int i = 0; i < length; i++) {
		res[i] = *(run_pcb->ir_reg + i);
	}
	run_pcb->ir_reg = run_pcb->ir_reg + length;
	
	char *temp = new char[length+1];
	memset(temp, 0, length+1);
	for (int i = 0; i < length; i++) {
		temp[i] = res[i];
	}
	return temp;

}


