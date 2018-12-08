#include "memery.h"

memory::memory() {
	struct free *now = list.free;
	struct free *temp;
	for (int i = 0; i < 512 / 8; i + init_size) {
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
int memory::malloc(int size, int pid)
{
	struct busy *busy_list = list.busy;
	struct free *free_list = list.free;
	struct busy *temp = new struct busy();
	struct free *free_prev = NULL;
	struct free *free_temp = NULL;
	struct free *mini_free_prev = NULL;
	temp->next = NULL;
	bool has_res = false;
	for (struct free *i = list.free; i != NULL; i = i->next) {
		if (i->size >= size) {
			has_res = true;
			temp->head = i->head;
			temp->size = size;
			temp->status = 1;
			temp->no = pid;
			temp->next = NULL;
			if (i->size == size) {
				if (free_prev == NULL) {
					list.free = i->next;
				}
				else {
					free_prev->next = i->next;
				}
			}
			else {
				i->head = i->head + size;
				i->size = i->size - size;
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
	if (!has_res) return -1;

	struct busy *p = list.busy;
	if (list.busy == NULL) {
		list.busy = temp;
	}
	else {
		while (p->next != NULL) {
			if (p->next->size >= temp->size) {
				break;
			}
			p = p->next;
		}
		temp->next = p->next;
		p->next = temp;
	}
	

	return temp->head;

	
}

void memory::free(int address)
{
	for (struct free* i = list.free; i != NULL; i = i->next) {
		
	}
}

int memory::mem_status(char * address)
{
	
}

void memory::write(char * address, char * str)
{
}

void memory::read(char * address)
{
}

int memory::length(char * address)
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
