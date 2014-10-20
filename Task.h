#ifndef TASK_H
#define TASK_H

#include "Project.h"
#include "Client.h"
#include "Date.h"
#include "Collaborator.h"


#include <string>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

class Collaborator;

class Task
{
private:
	int ID;
	static int lastID;
	string name;
	string description;
	unsigned int effort; //no. de horas restante para a tarefa ficar terminada
	vector< pair<Collaborator*, unsigned int> > collaborators;
	vector<Task*> dependencies; //tarefas das quais depende a tarefa
	vector<Task*> dependants; // tarefas que dependem da tarefa
public:
	Task(string name, unsigned int effort){this->name = name; this->effort = effort;};
	void setName(string nm){ name = nm; };
	void setEffort(unsigned int ef){ effort = ef; };
	bool operator==(Task& t2);
	class TaskExcept
	{
		string description;
	public:
		TaskExcept(string description, int ID = -1) :description(description){if(ID != -1) {stringstream s; s << ID; description+= s.str();}};
		string operator()(){ return description; };
	};
	class TaskComparator
	{
	public:
		virtual bool operator()(const Task& t1, const Task& t2)=0;
	};
	class TaskComparatorAlphabetic : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.name < t2.name; };
	};
	class TaskComparatorPriority : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getPriority() < t2.getPriority(); };
	};
	string getName() const { return this->name; };
	int getID() const { return this->ID; };
	int getPriority() const 
	{ 
		double sum = calculateEstimatedTime();
		for (size_t i = 0; i < dependants.size(); i++)
			sum += double(dependants.at(i)->getPriority()) / dependencies.size();
		return sum;
	};
	int calculateEstimatedTime() const //tempo que demora a tarefa a ser completada, sem ter em conta dependencias
	{ 
		int sum = 0; 
		for (size_t i = 0; i < collaborators.size(); i++) 
			sum += collaborators.at(i).second; 
		if (sum == 0) 
			return INT_MAX; 
		else return int(double (effort) / sum + .5);
	};
	int calculateTimeToCompletion() const //tempo que a tarefa vai demorar a ser completada, tendo em conta que as tarefas das quais depende terao de ser completadas primeiro
	{ 
		int sum = this->calculateEstimatedTime(); 
		for (size_t i = 0; i < dependencies.size(); i++) 
			sum += dependencies.at(i)->calculateTimeToCompletion();
		return sum; 
	};
	bool isReady()
	{ 
		for (size_t i = 0; i < dependencies.size(); ++i)
		if (!dependencies.at(i)->isCompleted()) //uma tarefa pode ser realizada se todas as tarefas das quais depende estiverem completas
			return false;
		return true;
	}
	double tick()//dia de trabalho
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
		if(effort == 0)//tarefa terminada
			for (size_t i = 0; i < collaborators.size(); ++i)
				collaborators.at(i).first->removeTask(this); // remover tarefa aos colaboradores

		return sum;//retorna o custo total do dia
	}
	bool isCompleted() const
	{
		return effort == 0;
	}
	Task& addDependency(Task* t, bool addDependant=true)
	{
		if(t == NULL)
			throw TaskExcept("No Task being added to Task:", ID);
		for(size_t i = 0; i < dependencies.size(); ++i)
			if(*dependencies.at(i)== *t)
				throw TaskExcept("Dependency already exists in Task:", ID);
		dependencies.push_back(t);
		if(addDependant)
		t->addDependant(this, false);
		return *this;
	}
	Task& addDependant(Task* t, bool addDependency=true)
		{
			if(t == NULL)
				throw TaskExcept("No Task being added to Task:", ID);
			for(size_t i = 0; i < dependants.size(); ++i)
				if(*dependants.at(i)== *t)
					throw TaskExcept("Dependant already exists in Task:", ID);
			dependants.push_back(t);
			if(addDependency)
			t->addDependency(this, false);
			return *this;
		}

};
#endif
