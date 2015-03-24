#include "stdafx.h"
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "address.pb.h"


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

	tutorial::Person person;
	person.set_name("John Doe");
	person.set_id(1234);
	person.set_email("jdoe@example.com");
	std::fstream output("myfile.txt", std::ios::out | std::ios::binary);
	person.SerializeToOstream(&output);
	output.close();
	{
		std::fstream input("myfile.txt", std::ios::in | std::ios::binary);
		tutorial::Person person;
		person.ParseFromIstream(&input);
		std::cout << "Name: " << person.name() << std::endl;
		std::cout << "E-mail: " << person.email() << std::endl;
	}
	FreeConsole();
	return 0;
}
