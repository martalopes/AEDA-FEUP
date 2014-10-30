#include "Task.h"


int Task::lastID = 0;



bool Task::operator==(Task& t2)
{
	return this->getID() == t2.getID();
}

double Task::tick()			//semana de trabalho
	{
		if (!isReady())
			return -1;
		double sum = 0;
		for (size_t i = 0; i < collaborators.size() && effort > 0; ++i)
		{
			sum += collaborators.at(i).second * collaborators.at(i).first->getCost();
			if(effort > 0) effort -= collaborators.at(i).second;
			if (effort <= 0)
				effort = 0;

		}
		if(effort == 0)		//tarefa terminada
			for (size_t i = 0; i < collaborators.size(); ++i)
				collaborators.at(i).first->removeTask(this); 	// remover tarefa aos colaboradores

		return sum;		//retorna o custo total do dia
	}
bool Task::addCollaborator(Collaborator* c1, unsigned int hours, bool addTask)
{
		for (size_t i = 0; i < this->collaborators.size(); ++i)
		{
			if (*collaborators[i].first == *c1)
			{
				throw TaskExcept("Collaborator already exists");
			}
		}
		if(addTask)
			if(c1->addTask(this, hours, false))
				return true;
			else return false;
		collaborators.push_back(make_pair(c1, hours));
		return true;
	}
bool Task::removeCollaborator(Collaborator* c, bool removeTask)
{
	if (c == NULL)
		throw TaskExcept("Invalid Collaborator");
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (collaborators.at(i).first == c)
	{
		collaborators.erase(collaborators.begin() + i);
		if(removeTask)
			return c->removeTask(this, false);
		return true;
	}
	return false;
}
void Task::setProject(Project* p, bool addTask)
{
	if (p == NULL)
		throw TaskExcept("Invalid Project");
	project = p;
	if (addTask)
		p->addTask(this, false);
}

ostream & operator<<(ostream& out, const Task& t)
{
	out << t.ID << endl;
	out << t.name << endl;
	out << t.description << endl;
	out << t.effort << endl;
	out << t.collaborators.size() << endl;
	for (size_t i = 0; i < t.collaborators.size(); i++)
		out << t.collaborators.at(i).first->getID() << " " << t.collaborators.at(i).second << endl;

	out << t.dependencies.size() << endl;
	for (size_t i = 0; i < t.dependencies.size(); i++)
		out << t.dependencies.at(i)->getID() << endl;
	
	out << t.dependants.size() << endl;
	for (size_t i = 0; i < t.dependants.size(); i++)
		out << t.dependants.at(i)->getID() << endl;
	out << t.project->getID();
	out << endl;
	return out;
}

istream & operator>>(istream& in, Task& t)
{
	in >> t.ID;
	in.ignore();
	getline(in,t.name);
	getline(in,t.description);
	in >> t.effort;
	in.ignore();
	int numcollaborators = 0;
	in >> numcollaborators;
	in.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		unsigned long int collaboratorid=0;
		unsigned int numhours;
		in >> collaboratorid >> numhours;
		in.ignore(2);
		t.collaborators.push_back(make_pair((Collaborator*) collaboratorid, numhours));
	}
	int numdependencies = 0;
	in >> numdependencies;
	in.ignore();
	for (size_t i = 0; i < numdependencies; i++)
	{
		unsigned long int dependencyid = 0;
		in >> dependencyid;
		in.ignore();
		t.dependencies.push_back((Task*) dependencyid);
	}
	int numdependants = 0;
	in >> numdependants;
	in.ignore();
	for (size_t i = 0; i < numdependants; i++)
	{
		unsigned long int dependantid = 0;
		in >> dependantid;
		in.ignore();
		t.dependants.push_back((Task*)dependantid);
	}
	unsigned long int projectid;
	in >> projectid;
	in.ignore();
	t.project = (Project*)projectid;
	string s;
	in >> s;
	return in;
}
void Task::connect()
{
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		Collaborator * ptr = Application::getCollaboratorPtr((int)collaborators.at(i).first);
		if (ptr != NULL)
			collaborators.at(i).first = ptr;
	}
	for (size_t i = 0; i < dependencies.size(); i++)
	{
		Task * ptr = Application::getTaskPtr((int)dependencies.at(i));
		if (ptr != NULL)
			dependencies.at(i) = ptr;
	}
	for (size_t i = 0; i < dependants.size(); i++)
	{
		Task * ptr = Application::getTaskPtr((int)dependants.at(i));
		if (ptr != NULL)
			dependants.at(i) = ptr;
	}
}