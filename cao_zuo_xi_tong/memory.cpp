#include "memery.h"

memory::memory() {
	struct free *now;//�������free����
	struct free *temp;
	for (int i = 0; i < init_mem_size; i++)
		mem[i] = 0;
	now = new struct free();
	temp = now;
	for (int i = 0; i < init_mem_size; i = i+init_size) {
		temp->head = i;
		temp->size = init_size;
		temp->status = use_project;
		if (i + init_size == init_mem_size) {
			temp->next = NULL;
			break;
		}
		temp->next = new struct free();
		temp = temp->next;
		
	}

	//temp = NULL;
	list.free = now;
	list.busy = NULL;
}

;
//�����ڴ� ��С ����id
int memory::malloc(int size, int pid)
{
	struct busy *temp = new struct busy();//��������ڴ��
	struct free *free_prev = NULL;//��¼��һָ��
	struct free *free_temp = NULL;//Ҫ������Ŀ����ڴ��
	temp->next = NULL;
	bool has_res = false;
	for (struct free *i = list.free; i != NULL; i = i->next) { //Ѱ��>=size�Ŀ����ڴ��
		if (i->size >= size) { 
			has_res = true;
			temp->head = i->head;
			temp->size = size;
			temp->status = 1;
			temp->no = pid;
			temp->next = NULL;
			if (i->size == size) { //size=��ǰ�����ڴ���С����������ɾ����ǰ�����ڴ��
				if (free_prev == NULL) { //��ǰ�ڴ���ڵ�0��
					list.free = i->next;
					
				}
				else { //���ڵ�0��
					free_prev->next = i->next;
				}
			}
			else { //size<��ǰ�ڴ�飬��С��ǰ�ڴ���С���׵�ַ
				i->head = i->head + size;
				i->size = i->size - size;


				//���°���С��������������
				free_temp = i;
				for (struct free *j = list.free; j != NULL; j = j->next) {
					if (free_temp == j) {
						continue;
					}
					if (free_temp->size < j->size && free_temp != list.free) {
						int temp = free_temp->head;
						free_temp->head = j->head;
						j->head = temp;
						temp = free_temp->size;
						free_temp->size = j->size;
						j->size = temp;
						free_temp = NULL;
						break;
							
					}
				}
					
			}
			break;
		}
		free_prev = i;
	}
	if (!has_res) {
		printf("memory::malloc:δ�ҵ��ʺϴ�С\n");
		return -1;
	}//�����ڴ���С��С��size������-1

	//����������ڴ��temp���뵽ʹ�ñ���
	struct busy *p = list.busy;
	if (list.busy == NULL) {//��Ϊ��0λ
		list.busy = temp;
	}
	else { //����������뵽ʹ�ñ���
		while (p->next != NULL) {
			if (p->next->size >= temp->size) {
				break;
			}
			p = p->next;
		}
		temp->next = p->next;
		p->next = temp;
	}
	
	//�����׵�ַ
	return temp->head;

	
}

void memory::free(int pid)
{
	struct busy *p = list.busy;
	struct free *p2 = list.free;
	struct busy *busy_temp = NULL;
	struct free *free_temp = new struct free();
	struct free *prev_free = NULL;
	while (p->next != NULL) {
		if (p->next->no == pid) {
			busy_temp = p->next;//�ݴ�
			p->next = (p->next)->next;//��������ɾ��
			break;
		}
		p = p->next;
	}
	if (busy_temp == NULL) {  
		printf("�ͷ��ڴ�ʧ�ܣ�δ�ҵ�ָ��pid���ڵ��ڴ��\n");
		return; 
	}//δ�ҵ�
	busy_temp->next = NULL;
	while (p2->next != NULL) {
		//�ϱ߽��غ�
		if (p2->next->head + p2->next->size == busy_temp->head) {
			busy_temp->head = p2->next->head;
			busy_temp->size = p2->next->size;
			//����
			p2->next = p2->next->next;
		}
		//�±߽��غ�
		if (busy_temp->head + busy_temp->size == p2->next->head) {
			busy_temp->size = busy_temp->size + p2->next->size;

			p2->next = p2->next->next;
		}
		if (p2->next == NULL) break;
		p2 = p2->next;
	}
	
	free_temp->head = busy_temp->head;
	free_temp->size = busy_temp->size;
	free_temp->status = 0;
	free_temp->next = NULL;

	p2 = list.free;
	if (p2 == NULL) {
		list.free = free_temp;
		return;
	}
	while (p2->next != NULL) {
		if (p2->next->size >= busy_temp->size) {
			break;
		}
		p2 = p2->next;
	}
	free_temp->next = p2->next;
	p2->next = free_temp;

}

int memory::mem_status(int address)
{
	struct busy *p1 = list.busy;
	struct free *p2 = list.free;
	while (p1 != NULL) {
		if (p1->head == address)
			return p1->status;
		p1 = p1->next;
	}
	while (p2 != NULL) {
		if (p2->head == address)
			return p2->status;
		p2 = p2->next;
	}
	printf("δ��ѯ������ڴ�״̬\n");
	return -1;

}

int memory::Length(char *address) {
	/*for (int i = 0; i < sizeof(address); i++)
		if (address[i] == 0)
			return i;*/
	return sizeof(address);
}

int memory::write(int address, char * str)
{
	struct busy *p1 = list.busy;
	while (p1 != NULL) {
		if (p1->head == address) {
			if (p1->size < Length(str)) {
				printf("ָ��������޷�д��%d�����ڴ�\n", address);
				return -1;
			}
			for (int i = 0; i < Length(str); i++) {
				mem[p1->head] = str[i];
			}
			return 1;

		}
		p1 = p1->next;
	}
	printf("memory::write:list.busyΪ��");
	return -1;
}

char* memory::read(int address)
{
	struct busy *temp = list.busy;
	for (struct busy *i = temp; i != NULL; i = i->next) {
		if (i->head <= address && i->head + i->size > address) {
			if (i->head != address)
				printf("memory::read��Ѱ�ҵ�ַ�ĵ�ַδ����\n");
			return mem + i->head;
		}
	}
	printf("memory::read��Ѱ�ҵ�ַδ�ҵ�\n");
	return NULL;
}

int memory::length(int address)
{
	struct busy *temp = list.busy;
	for (struct busy *i = temp; i != NULL; i = i->next) {
		if (i->head <= address && i->head + i->size > address) {
			if (i->head != address)
				printf("memory::length��Ѱ�ҵ�ַ�ĵ�ַδ����\n");
			return i->size;
		}
	}
	printf("memory::length��Ѱ�ҵ�ַδ�ҵ�\n");
	return -1;
}

int memory::busy_list()
{
	printf("no\thead\tsize\tstatus\t\n");
	struct busy *temp = list.busy;
	for (struct busy *i = temp; i != NULL; i = i->next) {
		printf("%d\t%d\t%d\t%d\t\n", i->no, i->head, i->size, i->status);
	}
	return 0;
}

int memory::free_list()
{
	printf("head\tsize\tstatus\t\n");
	struct free *temp = list.free;
	for (struct free *i = temp; i != NULL; i = i->next) {
		printf("%d\t%d\t%d\t\n", i->head, i->size, i->status);
	}
	return 0;
}
