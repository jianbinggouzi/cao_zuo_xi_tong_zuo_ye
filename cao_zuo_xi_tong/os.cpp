#include "os.h"

os::os(memory *_mem)
{
	//��ʼ���ڴ�
	mem = _mem;
	//Ϊ�й���������ڴ�
	int address = mem->malloc(8, last_pid);
	printf("�й����addressֵ:%d\n",address);
	char idle[] = "x=0;gob;";
	printf("---------%d\n", sizeof(idle));
	if (mem->write(address, idle) == 1) {
		printf("�й����д��ɹ�\n");
	}
	printf("�й�����ڴ������:%s\n", (mem->mem) + address);
	//����й����
	ready_pcb = new pcb();
	ready_pcb->pid = last_pid++;
	ready_pcb->data_reg = 0;
	ready_pcb->ir_reg = mem->mem + address;
	printf("����ʱir_reg=%d\n", ready_pcb->ir_reg);
	ready_pcb->status = READY;
	ready_pcb->reason = NO_BLOCK;
	ready_pcb->next = NULL;
	pid_num++;
	run_pcb = ready_pcb;
	//��ʼ���� �й������Զ���ھ������е�һλ ɾ������ʱҲ����ɾ���й����
}

int os::add_process(int size)
{
	pcb *p = ready_pcb;
	while (p->next != NULL) {
		p = p->next;
	}
	//����һ�����ڴ�
	int address = mem->malloc(size, last_pid);

	//���ڴ���д��ָ��
	char filename[10];
	memset(filename, 0, 10);
	sprintf_s(filename, "%d.c", last_pid);
	if (mem->write(address, (new file)->load_file(filename)) == -1) {
		printf("�����½����ļ�ʧ��\n");
		mem->free(last_pid);
		return -1;
	}
	else {
		printf("ָ��ɹ����� ");
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
	printf("������һ������,address:%d,size:%d,pid:%d\n", address, size, last_pid - 1);
	return last_pid - 1;
}

void os::dispatch()
{
	show_all_ready();
	show_all_block();
	//����������������pcbʱ��Ƭ-1 �������ʱ��Ƭ���� ���Ѹý���
	pcb* p = block_pcb;	
	while (p != NULL) {
		printf("�����������ǰpid = %d .time = %d", p->pid, p->surplus);
		p->surplus--;
		printf("--------------\n");
		if (p->surplus <= 0) {
			printf("����pid = %dʱ��Ƭ����", p->pid);
			move_block_process(p);
		}

		p = p->next;
	}
	//��鵱ǰ��pcb���Ƿ��б�cpu����Ϊ���״̬ ����� �Ӿ���������ɾ��
	pcb *p1 = ready_pcb;
	while (p1 != NULL) {
		if (p1->status == FINISH) {
			printf("����һ����� pid= %d\n", p1->pid);
			move_finished_process(p1);
			
		}
		p1 = p1->next;
	}
	
	//ʱ��Ƭ-1
	run_pcb->surplus--;
	//һ�ζ�ȡһ��ָ��
	run_pcb->ir = read_id_reg();
	if (run_pcb->pid == 0) {
		run_pcb->ir = mem->mem + 0;
		run_pcb->ir_reg = mem->mem + 0;
	}
	printf("pid:%d��ȡ��ָ��%s\n",run_pcb->pid, run_pcb->ir);		

	

}

int os::move_finished_process(pcb* _pcb)
{
	printf("pid:%d���\n", _pcb->pid);
	if (_pcb == ready_pcb) {
		ready_pcb = ready_pcb->next;
	}
	else {
		pcb* p = ready_pcb;
		while (p->next != _pcb) {
			if (p->next == NULL) {
				printf("os::move_finished_process:δ��ready���ҵ�pid=%d\n", _pcb->pid);
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
	printf("���pid=%d ��������,time=%d\n", _pcb->pid, _time);
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
		printf("os::add_block_process:δ�ҵ���Ӧpcb:%d\n",_pcb->pid);
		return -1;
	}
	
	_pcb->reason = reason;
	_pcb->surplus = _time;
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
	printf("�������������Ƴ�pid=%d\n", _pcb->pid);
	int if_find = -1;
	pcb *p = block_pcb;
	if (p == NULL) {
		printf("os::move_block_process:��������Ϊ��\n");
		return -1;
	}
	
	//_pcbλ�ڵ�һλ
	if (_pcb == block_pcb) {
		block_pcb = block_pcb->next;
	}
	else {
		while (p->next != _pcb) {
			if (p->next == NULL || p == NULL) {
				printf("os::move_block_process:δ�������������ҵ�pid=%d\n", _pcb->pid);
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


