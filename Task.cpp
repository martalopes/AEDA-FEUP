#include "Task.h"

int Task::lastID = 0;



bool Task::operator==(Task& t2)
{
	return this->getID() == t2.getID();
}