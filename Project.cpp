#include "Project.h"
#include "Task.h"
#include "Collaborator.h"
int Project::lastID = 0;
Project::Project(int i)
{
		stringstream s1, s2;
		s1 << "Project " << i;
		s2 << "Type " << i;
		*this = Project(s1.str(), s2.str(), Date() + Date::toSeconds(0, 6 + rand() % 10, 0, 0, 0, 0));
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
		for(int i = 0; i< tasks.size(); ++i)
				if(!tasks.at(i)->isCompleted())
					return false;
			return true;
	};
void Project::setClient(Client* c, bool addProject)
{ 
	if (c == NULL) throw ProjectExcept("Invalid client"); 
	else client = c; 
	if (addProject)
	c->addProject(this, false); 
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
	out << endl;
	return out;
}
istream & operator>>(istream& in, Project& p)
{
	in >> p.ID;
	in.ignore();
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

	int numtasks;
	in >> numtasks;
	in.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		long unsigned int taskid;
		in >> taskid;
		in.ignore();
		p.tasks.push_back((Task*) taskid);
	}
	int numcollaborators;
	in >> numcollaborators;
	for (size_t i = 0; i < numcollaborators; i++)
	{
		long unsigned int collaboratorid;
		in >> collaboratorid;
		in.ignore();
		p.collaborators.push_back((Collaborator*) collaboratorid);
	}
	string s;
	in >> s;
	in.ignore();
	return in;
}
void Project::connect()
{
	client = Application::getClientPtr((int)client);

	for (size_t i = 0; i < tasks.size(); i++)
	{
		Task* ptr = Application::getTaskPtr((int)tasks.at(i));
		if (ptr != NULL)
			tasks.at(i) = ptr;
	}
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		Collaborator* ptr = Application::getCollaboratorPtr((int)collaborators.at(i));
		if (ptr != NULL)
			collaborators.at(i) = ptr;
	}

}