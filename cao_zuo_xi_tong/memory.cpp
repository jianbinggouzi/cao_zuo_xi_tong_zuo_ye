#include "memery.h"

memory::memory() {
	struct free *now;//新申请的free链表
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
//申请内存 大小 进程id
int memory::malloc(int size, int pid)
{
	struct busy *temp = new struct busy();//新申请的内存块
	struct free *free_prev = NULL;//记录上一指针
	struct free *free_temp = NULL;//要做处理的空闲内存块
	temp->next = NULL;
	bool has_res = false;
	for (struct free *i = list.free; i != NULL; i = i->next) { //寻找>=size的空闲内存块
		if (i->size >= size) { 
			has_res = true;
			temp->head = i->head;
			temp->size = size;
			temp->status = 1;
			temp->no = pid;
			temp->next = NULL;
			if (i->size == size) { //size=当前空闲内存块大小，在链表中删除当前空闲内存块
				if (free_prev == NULL) { //当前内存块在第0块
					list.free = i->next;
					
				}
				else { //不在第0快
					free_prev->next = i->next;
				}
			}
			else { //size<当前内存块，缩小当前内存块大小和首地址
				i->head = i->head + size;
				i->size = i->size - size;


				//重新按大小升序放入空闲链表
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
		printf("memory::malloc:未找到适合大小\n");
		return -1;
	}//所有内存块大小都小于size，返回-1

	//将新申请的内存块temp放入到使用表项
	struct busy *p = list.busy;
	if (list.busy == NULL) {//作为第0位
		list.busy = temp;
	}
	else { //按照升序插入到使用表项
		while (p->next != NULL) {
			if (p->next->size >= temp->size) {
				break;
			}
			p = p->next;
		}
		temp->next = p->next;
		p->next = temp;
	}
	
	//返回首地址
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
			busy_temp = p->next;//暂存
			p->next = (p->next)->next;//从链表中删除
			break;
		}
		p = p->next;
	}
	if (busy_temp == NULL) {  
		printf("释放内存失败，未找到指定pid所在的内存块\n");
		return; 
	}//未找到
	busy_temp->next = NULL;
	while (p2->next != NULL) {
		//上边界重合
		if (p2->next->head + p2->next->size == busy_temp->head) {
			busy_temp->head = p2->next->head;
			busy_temp->size = p2->next->size;
			//断链
			p2->next = p2->next->next;
		}
		//下边界重合
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
	printf("未查询到相关内存状态\n");
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
				printf("指令过长，无法写入%d所在内存\n", address);
				return -1;
			}
			for (int i = 0; i < Length(str); i++) {
				mem[p1->head] = str[i];
			}
			return 1;

		}
		p1 = p1->next;
	}
	printf("memory::write:list.busy为空");
	return -1;
}

char* memory::read(int address)
{
	struct busy *temp = list.busy;
	for (struct busy *i = temp; i != NULL; i = i->next) {
		if (i->head <= address && i->head + i->size > address) {
			if (i->head != address)
				printf("memory::read：寻找地址的地址未对齐\n");
			return mem + i->head;
		}
	}
	printf("memory::read：寻找地址未找到\n");
	return NULL;
}

int memory::length(int address)
{
	struct busy *temp = list.busy;
	for (struct busy *i = temp; i != NULL; i = i->next) {
		if (i->head <= address && i->head + i->size > address) {
			if (i->head != address)
				printf("memory::length：寻找地址的地址未对齐\n");
			return i->size;
		}
	}
	printf("memory::length：寻找地址未找到\n");
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
