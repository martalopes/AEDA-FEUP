#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <iostream>
#include <ctime>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <algorithm>

using namespace std;

#define ASSERT_EQUAL_DELTA(arg1, arg2, delta) assert(abs(arg1-arg2) < delta)
#define ASSERT_EQUAL(arg1,arg2) assert(arg1==arg2)


int main()
{
	srand((unsigned int)time(NULL));
	Application* app = Application::Instance();
	try{
		Application::readFiles();
		/*
		Application::genApplication();
		Application::writeFiles();
		return 0;*/
	}
	catch (Application::ApplicationExcept& e)
	{
		cerr << e()<< endl;
		cin.get();
		delete app;
		return 1;
	}
	int state = 1;
	menus(state, *app);
	try{
		Application::writeFiles();
	}
	catch (Application::ApplicationExcept& e)
	{
		cerr << e()<<endl;
		cin.get();
		delete app;
		return 1;
	}
	delete app;
	return 0;
}
