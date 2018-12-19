#include"cpu.h"


using namespace std;

cpu::cpu()
{
}

void cpu::set_computer_status(bool if_run, os * os)
{
	if_start = if_run;
	_os = os;
}

bool cpu::get_status()
{
	return if_start;
}

void cpu::run()
{
	while (true) { //先处理指令后调度
		
		do_ir();
		_os->dispatch();
	}
}

void cpu::do_ir()
{
	pcb_now = _os->get_running_pcb();
	if (pcb_now->pid == 0) {
		return;
	}
	ir = pcb_now->ir;
	printf("处理指令:%s\n", ir);
	if (ir == NULL) return; //刚开机
	ir_reg = pcb_now->ir_reg;
	if (strcmp(ir, "x++;") == 0) {
		pcb_now->data_reg++;
	}
	else if (strcmp(ir, "x--;") == 0) {
		pcb_now->data_reg--;
	}
	else if (strcmp(ir, "end;") == 0) {
		_os->set_now_process_status(FINISH, END, 1);
	}
	else {
		if (ir[1] == '=') {
			pcb_now->data_reg = ir[2] - 48;
		}
		else if (ir[0] == '!') {
			int time = ir[2] - 48;
			if (ir[1] == 'A') {
				_os->add_block_process(pcb_now, A, time);

			}
			else if (ir[1] == 'B') {
				_os->add_block_process(pcb_now, A, time);
			}
		}
		else {
			printf("cpu无法识别指令:%s\n", ir);
		}
	}
}


