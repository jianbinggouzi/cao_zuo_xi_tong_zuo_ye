#include <stdio.h>
#include <fstream>
using namespace std;
//����ļ�����
class file {
public:
	static char ** load_files(char *names[_MAX_PATH], int num); //��n���ļ��ж�ȡ���� namesΪ�ļ��� numΪ�ļ�����
	static char * load_file(char *name); // ��ȡ�����ļ�
};
