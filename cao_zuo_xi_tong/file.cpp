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
	char _name[_MAX_PATH];
	memset(_name, 0, _MAX_PATH);
	strcat_s(_name, "ir_files\\");
	strcat_s(_name, name);
	ifstream in(_name);
	char buffer[BUFFER_SIZE];
	int length = 0;
	memset(buffer, 0, BUFFER_SIZE);
	if (in) {
		while (in.getline(buffer + length, BUFFER_SIZE)) {
			length = strlen(buffer);		
		}
	}
	else {
		printf("file::load_file:打开%s出错\n", name);
	}
	in.close();
	char *res = new char[length];
	for (int i = 0; i < length; i++)
		res[i] = buffer[i];
	//printf("%s\n", res);
	return res;
}
