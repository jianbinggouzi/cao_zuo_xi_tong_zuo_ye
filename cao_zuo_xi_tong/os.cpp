#include "os.h"

os::os(memory *_mem)
{
	//��ʼ���ڴ�
	mem = _mem;
	//Ϊ�й���������ڴ�
	int address = mem->malloc(8, last_pid);
	//����й����
	ready_pcb = new pcb();
	ready_pcb->pid = last_pid++;
	ready_pcb->data_reg = 0;
	ready_pcb->ir_reg = mem->mem + address;
	ready_pcb->status = READY;
	ready_pcb->reason = NO_BLOCK;
	ready_pcb->next = NULL;
	pid_num++;
	run_pcb = ready_pcb;
	//��ʼ���� �й������Զ���ھ������е�һλ ɾ������ʱҲ����ɾ���й����
}

int os::add_process(char * irs,int size)
{
	pcb *p = ready_pcb;
	while (p->next != NULL) {
		p = p->next;
	}
	int address = mem->malloc(size, last_pid);

	p->next = new pcb();
	p = p->next;
	p->pid = last_pid++;
	p->data_reg = 0;
	p->ir_reg = mem->mem + address;
	p->status = READY;
	p->reason = NO_BLOCK;
	p->next = NULL;
	pid_num++;
	printf("������һ������,address:%d,size:%d,pid:%d\n", address, size, last_pid - 1);
	return last_pid - 1;
}

void os::dispatch()
{
	if (run_pcb == NULL)
		run_pcb = ready_pcb;
	run_pcb->surplus--;
	//ִ��һ��ָ��
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
			//��ready_pcb������ɾ��
			p->next = p->next->next;
			if_find = 1;
			break;
		}
		p = p->next;
	}
	if (if_find == -1) {
		printf("os::add_block_process:δ�ҵ���Ӧpcb\n");
		return -1;
	}
	
	_pcb->reason = reason;
	_pcb->surplus = time;
	_pcb->status = BLOCK;
	_pcb->next = NULL;
	//��ӵ�block_pcb��
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
		printf("os::move_block_process:��������Ϊ��\n");
		return -1;
	}
	//��������ֻ��һ����
	if (p->next == NULL) {
		if (p != _pcb) {
			printf("os::move_block_process:δ�ҵ���Ӧpcb\n");
			return -1;
		}
	}
	//����1��
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
	_pcb->next = NULL;
	p->next = _pcb;
	return 1;
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
