#include "Project.h"
#include "Task.h"
#include "Collaborator.h"

int Project::lastID = 0;


Project::Project(int i)
{
		stringstream s1, s2;
		s1 << "Project " << i;
		s2 << "Type " << i;
		*this = Project(s1.str(), s2.str(), Date() + Date::toSeconds(0, 6 + rand() % 10, 0, 0, 0, 0), 10000 + (rand() % 5000-2500));
}
void Project::setClient(Client* c, bool addProject)
{
	if (c == NULL) throw ProjectExcept("Invalid client");
	else client = c;
	if (addProject)
		c->addProject(this, false);
}
bool Project::addCollaborator(Collaborator* c, bool addProject)
{
	for (size_t i = 0; i < this->collaborators.size(); ++i)
	{
		if (*collaborators.at(i) == *c)
		{
			return false;
		}
	}
	collaborators.push_back(c);
	if (addProject)
		c->addProject(this, false);
	return true;
}
void Project::addTask(Task * t, bool setProject)
{
	if (t == NULL)
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		if (*tasks.at(i) == *t)
		{
			throw ProjectExcept("Task already exists");
		}
	}
	tasks.push_back(t);
	if (setProject)
		t->setProject(this, false);
}
bool Project::tick() 
	{
		if(isCompleted())
			return false;
		for (size_t i = 0; i < tasks.size(); ++i)
			{
				double value = tasks.at(i)->tick();
				if(value >= 0)
					cost += value;
			}
		return true;
	}
bool Project::isCompleted()
	{
		for(size_t i = 0; i< tasks.size(); ++i)
				if(!tasks.at(i)->isCompleted())
					return false;
			return true;
	};
void Project::connect()
{
	client = Application::getClientPtr((int)client);

	for (size_t i = 0; i < tasks.size(); i++)
	{
		Task* ptr = Application::getTaskPtr((int)tasks.at(i));
			tasks.at(i) = ptr;
	}
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		Collaborator* ptr = Application::getCollaboratorPtr((int)collaborators.at(i));
			collaborators.at(i) = ptr;
	}

}

ostream & operator<<(ostream& out, const Project& p)
{
	out << p.ID << endl;
	out << p.name << endl;
	out << p.type << endl;
	out << p.client->getID() << endl;
	out << p.cost << endl;
	out << p.deadline.getTotalSeconds() << endl;
	out << p.tasks.size() << endl;
	for (size_t i = 0; i < p.tasks.size(); i++)
		out << p.tasks.at(i)->getID() << endl;
	out << p.collaborators.size() << endl;
	for (size_t i = 0; i < p.collaborators.size(); i++)
		out << p.collaborators.at(i)->getID() << endl;
	return out;
}
istream & operator>>(istream& in, Project& p)
{
	in >> p.ID;
	in.ignore();
	if (p.ID > Project::lastID)
		Project::lastID = p.ID;
	getline(in, p.name);
	getline(in, p.type);
	long unsigned int clientid;
	in >> clientid;
	in.ignore();
	p.client = (Client*) clientid;
	in >> p.cost;
	in.ignore();

	time_t totalseconds;
	in >> totalseconds;
	in.ignore();
	p.deadline= Date(totalseconds);

	unsigned int numtasks;
	in >> numtasks;
	in.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		long unsigned int taskid;
		in >> taskid;
		in.ignore();
		p.tasks.push_back((Task*) taskid);
	}
	unsigned int numcollaborators;
	in >> numcollaborators;
	in.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		long unsigned int collaboratorid;
		in >> collaboratorid;
		in.ignore();
		p.collaborators.push_back((Collaborator*) collaboratorid);
	}
	return in;
}

bool Project::removeTask(Task* t, bool removeProject)
{
	for (size_t i = 0; i < tasks.size(); i++)
	if (*tasks.at(i) == *t)
	{
		tasks.erase(tasks.begin() + i);
		if (removeProject)
			return t->removeProject(false);
		return true;
	}
	throw(ProjectExcept("Task does not exist"));
}
bool Project::removeClient(bool removeProject)
{
	if (client == NULL)
		throw ProjectExcept("Client being removed does not exist");
	if (removeProject)
		client->removeProject(this, false);
	client = NULL;
	return true;
}

bool Project::removeCollaborator(Collaborator* c, bool removeProject)
{
	if (c == NULL)
		throw ProjectExcept("Invalid Collaborator");
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		if (*c == *collaborators.at(i))
		{
			collaborators.erase(collaborators.begin() + i);
			if (removeProject)
				return c->removeProject(this, false);
			return true;
		}
	}
	return false;
}

bool Project::removeTrace()
{
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i)->removeTraceOutsideProject();
	}
	client->removeProject(this, false);
	return true;
}