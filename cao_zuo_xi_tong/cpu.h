#include <stdio.h>

class cpu {
public:
	
	int reg_1, reg_2, reg_3, reg_4; //�ĸ��Ĵ���
	char *ir;//ָ��Ĵ���
	typedef struct _pro_count { //���������
		int pcb_no; //pcb���
		char *ir_index; //��һ��ָ��λ��
	}pro_count;
	int dr; //���ݼĴ��� ���x
	
	
};
