#include "memery.h"

memory::memory() {
	struct free *now = list.free;
	struct free *temp;
	for (int i = 0; i < init_mem_size; i++)
		mem[i] = 0;
	for (int i = 0; i < init_mem_size / init_size; i + init_size) {
		now = new struct free();
		now->head = i;
		now->size = init_size;
		now->status = use_project;
		temp = now->next;
		now = temp;
	}
	now = NULL;
	list.busy = NULL;

}

;
//申请内存 大小 进程id
int memory::malloc(int size, int pid)
{
	struct busy *busy_list = list.busy;//使用表项
	struct free *free_list = list.free;//空闲表项
	struct busy *temp = new struct busy();//新申请的内存块
	struct free *free_prev = NULL;//记录上一指针
	struct free *free_temp = NULL;//要做处理的空闲内存块
	struct free *mini_free_prev = NULL; //临时添加
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

				//取出并重新按大小升序放入空闲链表
				free_prev->next = i->next; 
				free_temp = i;
				for (struct free *j = list.free; j != NULL; j = j->next) {
					if (free_temp->size < j->size) {
						if (mini_free_prev == NULL) {
							free_temp->next = list.free;
							list.free = free_temp;
						}
						else {
							free_temp->next = j;
							mini_free_prev->next = free_temp;
						}
						free_temp = NULL;
						break;
							
					}
					mini_free_prev = j;
				}
				if (free_temp != NULL) {
					free_temp->next = NULL;
					mini_free_prev = free_temp;
				}
					
			}
			break;
		}
		free_prev = i;
	}
	if (!has_res) return -1;//所有内存块大小都小于size，返回-1

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

			}

		}
	}
}

void memory::read(int address)
{
}

int memory::length(int address)
{
	return 0;
}

int memory::busy_list()
{
	return 0;
}

int memory::free_list()
{
	return 0;
}
