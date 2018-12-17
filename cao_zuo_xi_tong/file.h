#include <stdio.h>
#include <fstream>
using namespace std;
//相关文件操作
class file {
public:
	static char ** load_files(char *names[_MAX_PATH], int num); //从n个文件中读取内容 names为文件名 num为文件个数
	static char * load_file(char *name); // 读取单个文件
};
