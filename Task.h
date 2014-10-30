#ifndef TASK_H
#define TASK_H

#include "Project.h"
#include "Client.h"
#include "Date.h"
#include "Collaborator.h"
#include "Application.h"


#include <string>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

class Collaborator;
class Project;
class Task
{
private:
	int ID;
	static int lastID;
	string name;
	string description;
	int effort; //no. de horas restante para a tarefa ficar terminada
	vector< pair<Collaborator*, unsigned int> > collaborators;
	vector<Task*> dependencies; //tarefas das quais depende a tarefa
	vector<Task*> dependants; // tarefas que dependem da tarefa
	Project* project;
public:
	Task(string name, string description, unsigned int effort): name(name), description(description), effort(effort),ID(++lastID), project(NULL){};
	Task(string name, string description, unsigned int effort, int setID): name(name), description(description), effort(effort),ID(setID), project(NULL){if(setID > lastID) lastID = setID;};
	Task(int i)
	{
		stringstream s1,s2;
		s1 << "Task " << i;
		s2 << "Description " << i;
		*this = Task(s1.str(),s2.str(), 1 + rand() % 100);
	};
	friend ostream & operator<<(ostream& out, const Task& t);
	friend istream & operator>>(istream& in, Task& t);
	void connect();
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
	class TaskComparatorID : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getID() < t2.getID(); };
	};
	string getName() const { return this->name; };
	int getID() const { return this->ID; };
	Project* getProject()const{ return this->project; };
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
	double tick();//dia de trabalho
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
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask=true);
	bool removeCollaborator(Collaborator* c, bool removeTask = true);
	void setProject(Project* p, bool addTask = true);
};
#endif
