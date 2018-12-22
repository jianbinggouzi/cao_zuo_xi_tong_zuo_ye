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
		if (if_start == false) break;
	}
}

void cpu::do_ir()
{
	cpu_time = (cpu_time++) % 5;
	pcb_now = _os->get_running_pcb();
	pcb *next = (_os->run_pcb)->next;
	ir = pcb_now->ir;
	printf("处理pid=%d 指令:%s\n",pcb_now->pid, ir);
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
	else if (strcmp(ir, "gob;") == 0) {
		pcb_now->ir_reg = pcb_now->ir_reg - 8;
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
				_os->add_block_process(pcb_now, B, time);
			}
		}
		else {
			printf("cpu无法识别指令:%s\n", ir);
		}
	}
	dr = pcb_now->data_reg;
	
	//如果时间片用完或发生阻塞，指向下一个块 重新调度 
	if ((_os->run_pcb)->surplus == 0 || (_os->run_pcb)->status == BLOCK || (_os->run_pcb)->status == FINISH) {
		if((_os->run_pcb)->surplus == 0)
			(_os->run_pcb)->surplus = TIME; //如果时间片用完 恢复时间片，其他情况下表示时间片已经设置好 不能重新设置时间片
		(_os->run_pcb) = next;
	}

	//如果到达准备序列结尾 从头开始 如果有其他进程 调度其他进程 否则运行闲逛进程
	if ((_os->run_pcb) == NULL) {
		(_os->run_pcb) = _os->ready_pcb;
		
		(_os->run_pcb)->status = RUN;
	}
	_sleep(200);
}

pcb * cpu::get_now_pcb()
{
	return pcb_now;
}

int cpu::get_cpu_time()
{
	return cpu_time;
}

char * cpu::get_ir()
{
	return ir;
}

int cpu::get_dr()
{
	return dr;
}




