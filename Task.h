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
	int getPriority() const;
	void setName(string nm){ name = nm; };
	void setEffort(unsigned int ef){ effort = ef; };
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
	int calculateEstimatedTime() const; //tempo estimado de realização da tarefa
	int calculateTimeToCompletion() const; //tempo que falta para a conclosão da tarefa
	bool isReady(); //uma tarefa é dada como concluida quando todas as tarefas de que depende já se encontram realizadas
	double tick();//dia de trabalho.. retorna o custo daquele dia de trabalho
	void connect(); 
	//indica se a tarefa esta ou nao concluida
	bool isCompleted() const
	{
		return effort == 0;
	} 
	
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
	
};
#endif
