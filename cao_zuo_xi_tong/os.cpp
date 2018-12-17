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
	//ִ��һ��ָ��
	if (run_pcb->surplus == 0) {
		run_pcb->surplus = TIME;
		run_pcb = run_pcb->next;
	}
}
