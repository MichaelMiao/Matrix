#include "stdafx.h"
#include <fcntl.h>
#include <io.h>
#include <iomanip>


int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	AllocConsole();//Ϊ���̴���һ���µĿ���̨
	{
		HANDLE hin = ::GetStdHandle(STD_INPUT_HANDLE);
		HANDLE hout = ::GetStdHandle(STD_OUTPUT_HANDLE);
		int hcin = _open_osfhandle((intptr_t)hin, _O_TEXT);                 // ��ʱhcin �ͳ���һ��file descriptor ��   
		FILE * fpin = _fdopen(hcin, "r");
		*stdin = *fpin;                                                  //stdin ��ָ�����ļ�ָ��   
		int hcout = _open_osfhandle((intptr_t)hout, _O_TEXT);
		FILE * fpout = _fdopen(hcout, "wt");
		*stdout = *fpout;
		std::ios_base::sync_with_stdio();           // ��iostream ��ͬc runtime lib ��stdio ͬ������׼��ͬ����   
	}
	FreeConsole();
	return 0;
}
