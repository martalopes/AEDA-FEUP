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
		size_t j = 0;
		for (; j < tasks.size(); j++)
		if (tasks.at(j).first->getProject() == t->getProject())
			break;
		if (j == tasks.size())//colaborador nao tem mais tarefas do mesmo projecto
			removeProject(t->getProject(), true);
		if(removeCollaborator)
			return t->removeCollaborator(this, false);
		return true;
	}
	return false;
}
bool Collaborator::removeProject(Project* p, bool removeCollaborator)
{
	if (p == NULL)
		throw CollaboratorExcept("Invalid Project");
	for (size_t i = 0; i < projects.size(); ++i)
	if (*projects.at(i) == *p)
	{
		projects.erase(projects.begin() + i);
		if (removeCollaborator)
			return p->removeCollaborator(this, false);
		return true;
	}
	return false;
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
		p->addCollaborator(this, false);
	return true;
}
void Collaborator::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
			projects.at(i) = ptr;
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		Task* ptr = Application::getTaskPtr((int)tasks.at(i).first);
			tasks.at(i).first = ptr;
	}
}

bool Collaborator::removeTrace()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		projects.at(i)->removeCollaborator(this, false);
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i).first->removeCollaborator(this, false);
	}
	return true;
}

ostream & operator<<(ostream& out, const Collaborator& c)
{
	out << c.getTitle() << endl;
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
	out << c.finishedtasks.size() << endl;
	for (size_t i = 0; i < c.finishedtasks.size(); i++)
		out << c.finishedtasks.at(i)->getID() << endl;
	return out;
}
istream & operator>>(istream& in, Collaborator& c)
{
	in >> c.ID;
	in.ignore();
	if (c.ID > Collaborator::lastID)
		Collaborator::lastID = c.ID;
	getline(in, c.name);
	in >> c.maxweeklyhours;
	in.ignore();
	in >> c.workinghours;
	in.ignore();
	unsigned int numprojects = 0;
	in >> numprojects;
	in.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		unsigned long int projectid;
		in >> projectid;
		in.ignore();
		c.projects.push_back((Project*)projectid);
	}
	unsigned int numtasks = 0;
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
	unsigned int numfinishedtasks = 0;
	in >> numfinishedtasks;
	in.ignore();
	for (size_t i = 0; i < numfinishedtasks; i++)
	{
		unsigned long int taskid = 0;
		in >> taskid;
		in.ignore();
		c.finishedtasks.push_back((Task*)taskid);
	}
	return in;
}

bool Collaborator::reassign(Task* t)
{
	if (!removeTask(t, false))
		return false;
	finishedtasks.push_back(t);
}

Collaborator* Collaborator::newRandomCollaborator(int i)
{
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		return new Programmer(i);
		break;
	case 1:
		return new Architect(i);
		break;
	case 2:
		return new Manager(i);
		break;
	case 3:
		return new Tester(i);
		break;
	default:
		return NULL;
		break;
	}
}

Collaborator* Collaborator::newCollaboratorTitle(string title)
{
	if ("Programmer" == title)
		return new Programmer();
	if ("Architect" == title)
		return new Architect();
	if ("Manager" == title)
		return new Manager();
	if ("Tester" == title)
		return new Tester();
	return NULL;
}