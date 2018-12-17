#include "file.h"
#define BUFFER_SIZE 4096
char** file::load_files(char * names[_MAX_PATH], int n)
{
	char** res = new char* [n];
	for (int i = 0; i < n; i++)
		res[i] = new char[100];


	char buffer[512];
	for (int i = 0; i < n; i++) {
		ifstream in(names[i]);
		if (in) {
			while (in.getline(buffer,512)) {
				printf("%s", buffer);

			}
		}
		else {
			printf("file::load_files:打开%s出错\n", names[i]);
		}
		in.close();
	}
	return NULL;
}

char * file::load_file(char * name)
{
	ifstream in(name);
	char buffer[BUFFER_SIZE];
	int length = 0;
	memset(buffer, 0, BUFFER_SIZE);
	if (in) {
		while (in.getline(buffer + length, BUFFER_SIZE)) {
			length = strlen(buffer);		
		}
	}
	else {
		printf("file::load_files:打开%s出错\n", name);
	}
	printf("%s", buffer);
	in.close();
	return buffer;
}
