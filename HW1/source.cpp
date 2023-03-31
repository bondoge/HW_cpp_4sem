#include <math.h>
#include "timer.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


int main()
{
	{
		timer<std::chrono::microseconds> t;
		Sleep(500);
		t.pause();
		Sleep(500);
		t.resume();
		Sleep(500);
		std::cout << "test 1: ";
	}
	{
		timer<std::chrono::microseconds> t;
		Sleep(500);
		t.pause();
		Sleep(500);
		std::cout << "test 2: ";
	}
	{
		timer<std::chrono::microseconds> t;
		Sleep(500);
		t.resume();
		Sleep(500);
		std::cout << "test 3: ";
	}
	{
		timer<std::chrono::seconds> t;
		Sleep(1000);
		t.pause();
		Sleep(1000);
		t.resume();
		Sleep(1000);
		std::cout << "test 4: ";
	}
}
