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
		if ((this->getWorkingHours() + hours) > this->maxweeklyhours)
			return false;
		tasks.push_back(make_pair(t1, hours));
		/*size_t i = 0;
		for (; i < projects.size(); i++)
		if (*t1->getProject() == *projects.at(i))
			break;
		if (i == projects.size())
			projects.push_back(t1->getProject());*/
		addProject(t1->getProject());
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
	return out;
}

istream & operator>>(istream& in, Collaborator& c)
{
	in >> c.ID;
	in.ignore();
	if (c.ID > Collaborator::lastID)
		Collaborator::lastID = c.ID;
	getline(in,c.name);
	in >> c.maxweeklyhours;
	in.ignore();
	in >> c.workinghours;
	in.ignore();
	int numprojects = 0;
	in >> numprojects;
	in.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		unsigned long int projectid;
		in >> projectid;
		in.ignore();
		c.projects.push_back((Project*)projectid);
	}
	int numtasks = 0;
	in >> numtasks;
	in.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		unsigned long int taskid = 0;
		unsigned int hours = 0;
		in >> taskid >> hours;
		in.ignore();
		c.tasks.push_back(make_pair((Task*)taskid, hours));
	}
	return in;
}
void Collaborator::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
		if (ptr != NULL)
			projects.at(i) = ptr;
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		Task* ptr = Application::getTaskPtr((int)tasks.at(i).first);
		if (ptr != NULL)
			tasks.at(i).first = ptr;
	}
}

bool Collaborator::changeTaskHours(Task* t1, unsigned int hours)
{
	for (size_t i = 0; i < this->tasks.size(); ++i)
	{
		if (*tasks[i].first == *t1)
		{
			if (workinghours - tasks[i].second + hours > maxweeklyhours)
				return false;
			else tasks[i].second = hours;
			workinghours = workinghours - tasks[i].second + hours;
		}
	}
	return false;
}

bool Collaborator::addProject(Project* p, bool addCollaborator)
{
	for (size_t i = 0; i < this->projects.size(); ++i)
	{
		if (*projects.at(i) == *p)
		{
			return false;
		}
	}
	projects.push_back(p);
	if (addCollaborator)
		p->addCollaborator(this,false);
	return true;
}