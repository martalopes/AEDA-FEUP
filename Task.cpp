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