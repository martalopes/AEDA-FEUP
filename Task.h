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
uma descricao;
Cada tarefa tem um esforco expectavel que e contabilizado pelo numero de colaboradores que se dedicam a tarefa;
Sendo assim cada tarefa vai ter um vector de colaboradores associado.
Como cada tarefa nao e independente, isto e existem tarefas que dependem de outras e outras que dependem desta,
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
	///no. de horas restante para a tarefa ficar terminada
	int effort; 
	/// lista de pares formado pelo colaborador e as horas que dedica a essa tarefa
	vector< pair<Collaborator*, unsigned int> > collaborators; 
	///tarefas das quais depende a tarefa
	vector<Task*> dependencies; 
	/// tarefas que dependem da tarefa
	vector<Task*> dependants; 
	Project* project;
public:
	Task();
	Task(string name, string description, unsigned int effort);
	Task(string name, string description, unsigned int effort, int setID);
	Task(int i);
	///@return nome da tarefa
	string getName() const;
	///@return ID da tarefa
	int getID() const ;
	///@return projeto associado a tarefa
	Project* getProject()const;
	///@return tarefas que dependem da tarefa
	vector<Task*> getDependants() const;
	///@return tarefas das quais depende a tarefa
	vector<Task*> getDependencies() const;
	///@return lista de pares formado pelo colaborador e as horas que dedica a essa tarefa
	vector<pair<Collaborator*, unsigned int> > getCollaborators() const;
	///@return descricao da tarefa
	string getDescription()const;
	///modifica descricao da tarefa
	void setDescription(string s);
	///modifica nome da tarefa
	void setName(string nm);
	///modifica esforco da tarefa
	void setEffort(unsigned int ef);
	///@return esforco da tarefa
	int getEffort()const;

	bool setProject(Project* p, bool addTask = true);
	bool addDependency(Task* t, bool addDependant = true);
	bool addDependant(Task* t, bool addDependency = true);
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);
	bool removeCollaborator(Collaborator* c, bool removeTask = true);
	bool removeProject(bool removeTask=true);
	bool removeTrace();
	bool removeTraceOutsideProject();
	bool removeDependency(Task* t, bool removeDependant = true);
	bool removeDependant(Task* t, bool removeDependency = true);
	double calculateEstimatedTime() const; //tempo estimado de realizacao da tarefa, sem contar com dependencias, em semanas
	double calculateTimeToCompletion() const; //tempo que falta para a conclusao da tarefa, a contar com dependencias, em semanas
	bool isReady()const; //uma tarefa e dada como concluida quando todas as tarefas de que depende ja se encontram realizadas
	double tick();//semana de trabalho.. retorna o custo daquele dia de trabalho
	Date getDateOfCompletion(const Date& d)const;
	void connect(); 
	string toString() const;
	//indica se a tarefa esta ou nao concluida
	void complete();
	bool isCompleted() const;
	bool delay(int i);
	bool delay();
	bool speedup();
	bool isIsolated()const;
	bool operator==(Task& t2);
	friend ostream & operator<<(ostream& out, const Task& t);
	friend istream & operator>>(istream& in, Task& t);
	
	class TaskExcept
	{
		string description;
	public:
		TaskExcept(string description, int ID = -1);
		string operator()();
	};
	class TaskComparator
	{
	public:
		virtual bool operator()(const Task& t1, const Task& t2)=0;
		virtual bool operator()(const Task* t1, const Task* t2) = 0;
		virtual string getAbbreviation() const=0;
	};
	class TaskComparatorAlphabetic : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2);
		bool operator()(const Task* t1, const Task* t2);
		string getAbbreviation() const;
	};
	class TaskComparatorID : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2);
		bool operator()(const Task* t1, const Task* t2);
		string getAbbreviation() const;
	};
	class TaskComparatorEffort : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2);
		bool operator()(const Task* t1, const Task* t2) ;
		string getAbbreviation() const;
	};
	class TaskComparatorEstimatedTime : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) ;
		bool operator()(const Task* t1, const Task* t2) ;
		string getAbbreviation() const;
	};
	class TaskComparatorTimeToCompletion : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2);
		bool operator()(const Task* t1, const Task* t2);
		string getAbbreviation() const;
	};
	class TaskComparatorNumDependants: public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) ;
		bool operator()(const Task* t1, const Task* t2) ;
		string getAbbreviation() const;
	};
	class TaskComparatorNumDependencies : public TaskComparator
	{
	public:
		bool operator()(const Task& t1, const Task& t2) ;
		bool operator()(const Task* t1, const Task* t2);
		string getAbbreviation() const;
	};
};
#endif
