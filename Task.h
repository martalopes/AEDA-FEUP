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
	Task(): ID(0),effort(0),project(NULL){};
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
	int getPriority() const;
	int calculateEstimatedTime() const;
	int calculateTimeToCompletion() const;
	bool isReady();
	double tick();//dia de trabalho
	bool isCompleted() const
	{
		return effort == 0;
	}
	Task& addDependency(Task* t, bool addDependant = true);
	Task& addDependant(Task* t, bool addDependency = true);
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask=true);
	bool removeCollaborator(Collaborator* c, bool removeTask = true);
	void setProject(Project* p, bool addTask = true);
};
#endif
