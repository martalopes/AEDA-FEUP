#include "Collaborator.h"
#include "Task.h"
int Collaborator::lastID=0;
bool Collaborator::addTask(Task* t1, unsigned int hours, bool addCollaborator)
	{
		for (size_t i = 0; i < this->tasks.size(); ++i)
		{
			if (*(tasks[i].first) == *t1)
			{
				throw CollaboratorExcept("Task already exists");
			}
		}
		if (this->getWorkingHours() + hours > this->maxweeklyhours)
			return false;
		tasks.push_back(make_pair(t1, hours));
		size_t i = 0;
		for (; i < projects.size(); i++)
		if (*t1->getProject() == *projects.at(i))
			break;
		if (i == projects.size())
			projects.push_back(t1->getProject());
		if(addCollaborator)
		t1->addCollaborator(this, hours, false);
		workinghours += hours;
		return true;
	}

bool Collaborator::removeTask(Task* t, bool removeCollaborator)
{
	if (t == NULL)
		throw CollaboratorExcept("Invalid task");
	for (size_t i = 0; i < tasks.size(); ++i)
	if (tasks.at(i).first == t)
	{
		workinghours -= tasks.at(i).second;
		tasks.erase(tasks.begin() + i);
		if(removeCollaborator)
			return t->removeCollaborator(this, false);
		return true;
	}
	return false;
}
ostream & operator<<(ostream& out, const Collaborator& c)
{
	out << c.ID << endl;
	out << c.name << endl;
	out << c.maxweeklyhours << endl;
	out << c.workinghours << endl;
	out << c.projects.size() << endl;
	for (size_t i = 0; i < c.projects.size(); i++)
		out << c.projects.at(i)->getID() << endl;
	out << c.tasks.size() << endl;
	for (size_t i = 0; i < c.tasks.size(); i++)
		out << c.tasks.at(i).first->getID() << " " << c.tasks.at(i).second << endl;
	out << endl;
	return out;
}