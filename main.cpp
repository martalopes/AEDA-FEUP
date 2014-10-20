#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"

#include <iostream>

using namespace std;

int main()
{
	Date d = Date();
	cout << d.printDate();
	return 0;
}
