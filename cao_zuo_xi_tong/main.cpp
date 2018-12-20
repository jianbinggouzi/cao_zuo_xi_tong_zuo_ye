
#include "cpu.h"
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

	_os.add_process( 20);
	_os.add_process( 20);
	_os.add_process( 20);
	_os.add_process( 20);
	_os.add_process( 20);
	_os.add_process( 20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);

	
	cpu _cpu;
	_cpu.set_computer_status(true, &_os);
	if (_cpu.get_status()) {
		printf("开机完成");
		_cpu.run();
	}

	


	printf("all:\n");
	for (int i = 0; i < 512; i++) {
		printf("%c",mem.mem[i]);
	}
	getchar();
}