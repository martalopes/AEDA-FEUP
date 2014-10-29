#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <iostream>
#include <ctime>

using namespace std;

int main( )
{
	Application a;
	a.genApplication();
	a.writeFiles();
	system("pause");
}
