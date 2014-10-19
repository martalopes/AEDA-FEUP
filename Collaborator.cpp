#include "Collaborator.h"

int Collaborator::lastID = 0;


/*int Collaborator::numCollaborators(){ return Collaborator::lastID; }
int Collaborator::getID() const { return this->ID; }
string Collaborator::getName() const { return this->name; }
void Collaborator::setName(string newname){ this->name = newname; }
int Collaborator::getWorkingHours() const { return  this->workinghours; }
int Collaborator::getWeeklyHours() const { return this->weeklyhours; }
void Collaborator::setWeeklyHours(int newhours) { this->weeklyhours = newhours; }

float Programmer::getCost() const { return PROGRAMMER_COST; }
float Architect::getCost() const { return ARCHITECT_COST; }
float Manager::getCost() const { return MANAGER_COST; }
float Testers::getCost() const { return TESTER_COST; }*/

bool Collaborator::addTask(Task* t1, unsigned int hours)
	{
		for (size_t i = 0; i < this->tasks.size(); ++i)
		{
			if (*tasks[i].first == *t1)
			{
				throw CollaboratorExcept("Task already exists");
			}
		}
		if (this->getWorkingHours() + hours > this->maxdailyhours)
			return false;
		tasks.push_back(make_pair(t1, hours));
		workinghours += hours;
		return true;
	}


bool Collaborator::changeTaskHours(Task* t1, unsigned int hours)
{


	Task* t = new Task ("1", 0);
	Task* t2 = new Task ("2", 0);


	if (*t == *t2)
		cout << "ok";
	for (size_t i = 0; i < this->tasks.size(); ++i)
	{
		if (*tasks[i].first == *t1)
		{
			if (workinghours - tasks[i].second + hours >maxdailyhours)
				return false;
			else tasks[i].second = hours;
			workinghours = workinghours - tasks[i].second + hours;
		}
	}
	return false;
}
