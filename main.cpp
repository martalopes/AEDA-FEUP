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
	if (0){
		Application b;
		b.genApplication();
		b.writeFiles();
	}
	else{
		a.readFiles();
		int x= 0;
		//a.writeFiles();
	}
	system("pause");
}
