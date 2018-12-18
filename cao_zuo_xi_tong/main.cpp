#include <stdio.h>

#include "file.h"
#include "os.h"
struct test {
	int n;
	struct test* next;
};
void test() {
	struct test *head = new struct test();
	head->next = NULL;
	struct test *p = head;
	for (int i = 0; i < 5; i++) {
		p->n = i;
		p->next = new struct test();
		p = p->next;
	}
	p = NULL;
	p = head;
	while (p->next != NULL) {
		printf("%d ", p->n);
		p = p->next;
	}
	printf("\n");
	p = head;
	while (p->next != NULL) {
		if (p->n == 2)
			break;
		p = p->next;
	}
	printf("find p->n=%d\n", p->n);
	p->next = p->next->next;
	p = head;
	while (p->next != NULL) {
		printf("%d ", p->n);
		p = p->next;
	}
}
int main() {
	memory mem;
	
	os _os(&mem);
	_os.add_process(NULL, 2);
	_os.add_process(NULL, 7);
	_os.add_process(NULL, 16);
	_os.add_process(NULL, 20);
	_os.add_process(NULL, 13);
	_os.add_process(NULL, 24);
	
	pcb *p = _os.ready_pcb,*temp=NULL;
	if (p == NULL) printf("ready_pcb is null\n");
	while (p->next != NULL) {
		if (p->pid == 2 ) {
			temp = p;
			_os.add_block_process(temp, A, 3);
			break;
		}
		p = p->next;
	}

	p = _os.ready_pcb;
	while (p->next != NULL) {
		if (p->pid == 3) {
			temp = p;
			_os.add_block_process(temp, A, 3);
			break;
		}
		p = p->next;
	}

	p = _os.block_pcb;
	while (p != NULL) {
		if (p->pid == 3) {
			temp = p;
			_os.move_block_process(temp);
			break;
		}
		p = p->next;
	}

	_os.show_all_ready();
	_os.show_all_block();
	mem.busy_list();
	
	getchar();
}