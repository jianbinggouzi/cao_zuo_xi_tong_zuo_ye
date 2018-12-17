#include <stdio.h>
#include "memery.h"
int main() {
	memory mem;
	mem.malloc(3, 123);
	mem.malloc(5, 123);
	mem.malloc(10, 123);
	mem.malloc(20, 123);
	mem.malloc(20, 123);
	mem.malloc(20, 123);
	
	mem.free_list();
	mem.busy_list();
	getchar();
}