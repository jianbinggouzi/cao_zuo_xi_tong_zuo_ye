#include "memery.h"
memory::memory() {
	struct busy *now = list.busy;
	struct busy *temp;
	for (int i = 0; i < 512 / 8; i+init_size) {
		now = new struct busy();
		now->head = i;
		now->size = init_size;
		now->status = use_project;
		temp = now->next;
		now = temp;
	}
	now = NULL;
}

;
char * memory::malloc(int size)
{
	
}

void memory::free(char * address)
{
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
