#include "cpu.h"
#include "resource.h"
#include <Windows.h>
#include <tchar.h>

//全局变量
memory mem;
os _os(&mem);
cpu _cpu;


//图形界面初始化
void initDialog(HWND hDlg) {
	HBITMAP bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
	HWND Button = GetDlgItem(hDlg, IDC_BUTTON1);
	SetWindowLong(Button, GWL_STYLE, GetWindowLong(Button, GWL_STYLE) + BS_BITMAP);
	SendMessage(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	
	//初始化内存块界面
	bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP3));
	for (int i = 1035; i <= 1162; i++) {
		Button = GetDlgItem(hDlg, i);
		SetWindowLong(Button, GWL_STYLE, GetWindowLong(Button, GWL_STYLE) + BS_BITMAP);
		SendMessage(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	}

}

//cpu运行线程
static void WINAPI run_cpu() {
	_cpu.set_computer_status(true, &_os);
	printf("开机完成");
	_cpu.run();
}

//载入进程函数
void add_all_processes() {
	
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
	_os.add_process(20);
}

//消息处理函数
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UINT wmId;
	switch (message)
	{
	case WM_INITDIALOG:
		initDialog(hDlg);
		return TRUE;
	case WM_CREATE:
		
		break;
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		switch (wmId) {
			case IDC_BUTTON1:
				if (_cpu.get_status() == false) {
					DWORD CPUId = 0;
					HANDLE CPUThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run_cpu, NULL, 0, &CPUId);
					HBITMAP bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP2));
					HWND switchButton = GetDlgItem(hDlg, IDC_BUTTON1);
					SendMessage(switchButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
				}
				else {
					_cpu.set_computer_status(false, &_os);
					HBITMAP bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
					HWND switchButton = GetDlgItem(hDlg, IDC_BUTTON1);
					SendMessage(switchButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
				}
				break;
			case 1004:
				add_all_processes();
				break;
		}
		
	}
	break;
	case WM_CLOSE:
	{
		PostQuitMessage(1);
		return TRUE;
	}
	}
	return FALSE;
}

//更新窗口
void updateInterface(HWND hDlg) {
	HWND status;
	pcb * now_pcb = _cpu.get_now_pcb();
	if (now_pcb == NULL) return;

	//更新cpu状态
	SetDlgItemInt(hDlg, IDC_NOW_PID, now_pcb->pid, FALSE);
	SetDlgItemInt(hDlg, IDC_CPU_TIME, _cpu.get_cpu_time(), FALSE);
	SetDlgItemTextA(hDlg, IDC_NOW_IR, (LPCSTR)(_cpu.get_ir()));
	SetDlgItemInt(hDlg, IDC_NOW_DR, _cpu.get_dr(),FALSE);

	//更新内存块状态
	//先全部恢复为起始状态
	HBITMAP bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP3));
	HWND Button = GetDlgItem(hDlg, 1035);
	SendMessage(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	for (int i = 1035; i <= 1162; i++) {
		Button = GetDlgItem(hDlg, i);
		SendMessage(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	}
	//重新上色
	bmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP4));
	struct busy * p = mem.list.busy;
	int p1, p2;
	while (p != NULL) {
		p1 = (p->head) / 4 + 1035;
		p2 = (p->size) / 4 + (p->head) / 4 + 1034;
		for (int i = p1; i <= p2; i++) {
			Button = GetDlgItem(hDlg, i);
			SendMessage(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		}
		p = p->next;
	}

	//更新三个列表 先清空 再添加数据
	HWND List = GetDlgItem(hDlg, 1029);
	SendMessage(List, LB_RESETCONTENT, 0, 0);
	pcb *p3 = _os.ready_pcb;
	char buffer[20];
	while (p3 != NULL) {
		memset(buffer, 0, 10);
		sprintf(buffer, "pid=%d\n", p3->pid);
		if (p3->pid != 0) {
			SendMessageA(List, LB_ADDSTRING, 0, (LPARAM)buffer);
		}
		p3 = p3->next;
	}

	List = GetDlgItem(hDlg, 1030);
	SendMessage(List, LB_RESETCONTENT, 0, 0);
	p3 = _os.block_pcb;
	while (p3 != NULL) {
		memset(buffer, 0, 10);
		sprintf(buffer, "pid=%d remian:%d\n", p3->pid,p3->surplus);
		if (p3->pid != 0) {
			SendMessageA(List, LB_ADDSTRING, 0, (LPARAM)buffer);
		}
		p3 = p3->next;
	}


	List = GetDlgItem(hDlg, 1031);
	SendMessage(List, LB_RESETCONTENT, 0, 0);
	p3 = _os.finish_pcb;
	while (p3 != NULL) {
		memset(buffer, 0, 10);
		sprintf(buffer, "pid=%d\n", p3->pid);
		if (p3->pid != 0) {
			SendMessageA(List, LB_ADDSTRING, 0, (LPARAM)buffer);
		}
		p3 = p3->next;
	}

	
	
}

//创建窗口
static void WINAPI CreateInterface(void *arg) {
	HINSTANCE hInstance = GetModuleHandle(0);
	HWND hSurface = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)About);
	ShowWindow(hSurface, SW_SHOW);
	UpdateWindow(hSurface);
	

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (GetMessage(&msg, NULL, 0, 0)) {
		updateInterface(hSurface);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		UpdateWindow(hSurface);
	}
	return ;
}



int main() {
	//创建主界面 放在线程里
	DWORD SurfaceId = 0;
	HANDLE hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateInterface, NULL, 0, &SurfaceId);
		

	printf("all:\n");
	for (int i = 0; i < 512; i++) {
		printf("%c",mem.mem[i]);
	}
	getchar();
	return 0;
};








	

	
