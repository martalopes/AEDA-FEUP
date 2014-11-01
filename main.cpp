#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	Application a;
	if (0)
	{
		a.genApplication();
		a.writeFiles();
		return 0;
	}
	//string cmd;
	//getline(cin,cmd);
	//if (cmd == "gen")
	//a.genApplication();
	//else if (cmd == "read")
	a.readFiles();
	a.createMenus();
	a.play();
	a.writeFiles();
	int x = 0;
	system("pause");
}
