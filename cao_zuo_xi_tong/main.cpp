#include <stdio.h>
#include "memery.h"
#include "file.h"
int main() {
	memory mem;
	
	char *a = "1.txt";
	file b;
	b.load_file(a);


	getchar();
}