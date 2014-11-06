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

	///associa projeto a tarefa
	///@param projeto a ser associado
	///@param indica se a tarefa deve ser adicionada ao projeto
	///@throw projeto nao existe
	///@return sucesso da operacao
	bool setProject(Project* p, bool addTask = true);

	///adiciona dependencia a tarefa
	///@param tarefa a ser associada
	///@param indica se a tarefa deve ser adicionada como dependente a dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependency(Task* t, bool addDependant = true);

	///adiciona dependente a tarefa
	///@param tarefa a ser associada
	///@param indica se a tarefa deve ser adicionada como  dependencia ao dependente
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependant(Task* t, bool addDependency = true);

	///adiciona colaborador a tarefa
	///@param colaborador a ser associado
	///@param numero de horas que o colaborador vai trabalhar na tarefa
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);

	///remove colaborador da tarefa
	///@param colaborador a ser desassociado
	///@param indica se a tarefa deve ser removida do colaborador
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool removeCollaborator(Collaborator* c, bool removeTask = true);

	///desassocia projeto da tarefa
	///@param indica se a tarefa deve ser removida do projeto
	///@return sucesso da operacao
	bool removeProject(bool removeTask=true);
	///remove todas as referencias a tarefa noutros objetos
	///@return sucesso da operacao
	bool removeTrace();
	///remove todas as referencias a tarefa noutros objetos, fora do projeto ao qual esta associado
	///@return sucesso da operacao
	bool removeTraceOutsideProject();
	///remove dependencia da tarefa
	///@param tarefa a ser removida
	///@param indica se a tarefa deve ser removida da sua dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependency(Task* t, bool removeDependant = true);
	///remove dependente da tarefa
	///@param tarefa a ser removida
	///@param indica se a tarefa deve ser removida da seu dependente
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependant(Task* t, bool removeDependency = true);
	///@return tempo estimado de realizacao da tarefa, sem contar com dependencias, em semanas, -1 se a tarefa nao estiver a ser trabalhada
	double calculateEstimatedTime() const; 
	///@return tempo que falta para a conclusao da tarefa, a contar com dependencias, em semanas, -1 se a tarefa ou 1 das suas dependencias nao estivera ser trabalhada
	double calculateTimeToCompletion() const; 
	///@return uma tarefa pode ser trabalhada quando todas as tarefas de que depende ja se encontram realizadas
	bool isReady()const; 
	///semana de trabalho
	///@return custo daquela semana de trabalho
	double tick();
	///@param data atual
	///@return data estimada de conclusao da tarefa
	Date getDateOfCompletion(const Date& d)const;
	///substitui IDs contidos na tarefa pelos apontadores para os objetos correspondentes
	void connect();
	///@return string com o nome e o ID da tarefa
	string toString() const;
	///poe o esforco da tarefa a 0, e remove todos os colaboradores da tarefa, adicionando a tarefa a lista de tarefas completadas dos colaboradores
	void complete();
	///@param indica se a tarefa esta concluida
	bool isCompleted() const;
	///atraso na tarefa
	///@param atraso pretendido
	///@return sucesso da operacao
	bool delay(int i);
	///atraso aleatorio na tarefa
	///@return sucesso da operacao
	bool delay();
	///adiantamento aleatorio na tarefa
	///@return sucesso da operacao
	bool speedup();
	///@return verdadeiro se tarefa nao esta associada a outras por dependencias
	bool isIsolated()const;
	///@return tarefas sao iguais se tiverem o mesmo ID
	bool operator==(Task& t2);

	/// escrita de todos os dados da tarefa, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param  stream de saida
	/// @param  tarefa a ser escrita
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Task& t);

	/// leitura de todos os dados da tarefa, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param  stream de entrada
	/// @param  tarefa a ser lido
	/// @return stream de entrada
	friend istream & operator>>(istream& in, Task& t);
	///classe de excecao associada a tarefas
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
