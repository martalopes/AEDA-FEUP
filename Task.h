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

/*
Task Class:
Cada tarefa vai ser identificada por:
um ID, para facilitar a sua identificacao;
um nome;
uma descrição;
Cada tarefa tem um esforço expectável que é contabilizado pelo numero de colaboradores que se dedicam a tarefa;
Sendo assim cada tarefa vai ter um vector de colaboradores associado.
Como cada tarefa nao é independente, isto é existem tarefas que dependem de outras e outras que dependem desta,
optamos por criar um vector de tarefas dependentes (dependants) e de tarefas de que depende (dependencies).
*/

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
	vector< pair<Collaborator*, unsigned int> > collaborators; //par formado pelo colaborador e as horas que dedica a essa tarefa
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
	string getName() const { return this->name; };
	int getID() const { return this->ID; };
	Project* getProject()const{ return this->project; };
	vector<Task*> getDependants() const{ return dependants; };
	vector<Task*> getDependencies() const{ return dependencies; };
	vector<pair<Collaborator*, unsigned int> > getCollaborators() const{ return collaborators; };
	int getPriority() const;
	void setName(string nm){ name = nm; };
	void setEffort(unsigned int ef){ effort = ef; };
	int getEffort()const { return this->effort; };
	void setProject(Project* p, bool addTask = true);
	bool addDependency(Task* t, bool addDependant = true);
	bool addDependant(Task* t, bool addDependency = true);
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);
	bool removeCollaborator(Collaborator* c, bool removeTask = true);
	bool removeProject(bool removeTask=true);
	bool removeTrace();
	bool removeTraceOutsideProject();
	bool removeDependency(Task* t, bool removeDependant = true);
	bool removeDependant(Task* t, bool removeDependency = true);
	double calculateEstimatedTime() const; //tempo estimado de realização da tarefa, sem contar com dependencias, em semanas
	double calculateTimeToCompletion() const; //tempo que falta para a conclusão da tarefa, a contar com dependencias, em semanas
	bool isReady()const; //uma tarefa é dada como concluida quando todas as tarefas de que depende já se encontram realizadas
	double tick();//dia de trabalho.. retorna o custo daquele dia de trabalho
	void connect(); 
	//indica se a tarefa esta ou nao concluida
	void complete();
	bool isCompleted() const
	{
		return (effort <= 0);
	};
	bool delay(int i){ if (isCompleted()) return false; effort += i; return true; };
	bool delay()
	{ 
		if (isCompleted()) 
			return false; 
		effort += rand() % 19 + 1;
	};
	bool operator==(Task& t2);
	friend ostream & operator<<(ostream& out, const Task& t);
	friend istream & operator>>(istream& in, Task& t);
	
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
		bool operator()(const Task* t1, const Task* t2) { return t1->name < t2->name; };
	};
	class TaskComparatorPriority : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getPriority() < t2.getPriority(); };
		bool operator()(const Task* t1, const Task* t2) { return t1->getPriority() < t2->getPriority(); };
	};
	class TaskComparatorID : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getID() < t2.getID(); };
		bool operator()(const Task* t1, const Task* t2) { return t1->getID() < t2->getID(); };
	};
	class TaskComparatorEffort : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.getEffort() < t2.getEffort(); };
		bool operator()(const Task* t1, const Task* t2) { return t1->getEffort() < t2->getEffort(); };
	};
	class TaskComparatorEstimatedTime : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.calculateEstimatedTime() < t2.calculateEstimatedTime(); };
		bool operator()(const Task* t1, const Task* t2) { return t1->calculateEstimatedTime() < t2->calculateEstimatedTime(); };
	};
	class TaskComparatorTimeToCompletion : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) { return t1.calculateTimeToCompletion() < t2.calculateTimeToCompletion(); };
		bool operator()(const Task* t1, const Task* t2) { return t1->calculateTimeToCompletion() < t2->calculateTimeToCompletion(); };
	};
};
#endif
