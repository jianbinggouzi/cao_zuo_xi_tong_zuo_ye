#include "os.h"

os::os()
{
	//����й����
	ready_pcb = new pcb();
	ready_pcb->pid = last_pid++;

	pid_num++;
}

int os::add_process(char * irs)
{
	

	
	pid_num++;
	last_pid++;
}
