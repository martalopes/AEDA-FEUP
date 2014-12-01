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
	///construtor por defeito
	Task();
	///construtor sem ID especificado
	///@param name nome da tarefa
	///@param description descricao da tarefa
	///@param effort esforco restante para terminar a tarefa
	Task(string name, string description, unsigned int effort);
	///construtor sem ID especificado
	///@param name nome da tarefa
	///@param description descricao da tarefa
	///@param effort esforco restante para terminar a tarefa
	///@param setID o ID da tarefa
	Task(string name, string description, unsigned int effort, int setID);
	///@param i indice da tarefa
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
	///@param s string da nova descricao
	void setDescription(string s);

	///modifica nome da tarefa
	///@param nm string com o novo nome
	void setName(string nm);

	///modifica esforco da tarefa
	///@param ef novo esforco da tarefa
	void setEffort(unsigned int ef);

	///@return esforco da tarefa
	int getEffort()const;

	///associa projeto a tarefa
	///@param p projeto a ser associado
	///@param addTask indica se a tarefa deve ser adicionada ao projeto
	///@throw projeto nao existe
	///@return sucesso da operacao
	bool setProject(Project* p, bool addTask = true);

	///adiciona dependencia a tarefa
	///@param t tarefa a ser associada
	///@param addDependant indica se a tarefa deve ser adicionada como dependente a dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependency(Task* t, bool addDependant = true);

	///adiciona dependente a tarefa
	///@param t tarefa a ser associada
	///@param addDependency indica se a tarefa deve ser adicionada como  dependencia ao dependente
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependant(Task* t, bool addDependency = true);

	///adiciona colaborador a tarefa
	///@param t1 colaborador a ser associado
	///@param hours numero de horas que o colaborador vai trabalhar na tarefa
	///@param addTask indica se a tarefa deve ser adicionada ao colaborador 
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);

	///remove colaborador da tarefa
	///@param c colaborador a ser desassociado
	///@param removeTask indica se a tarefa deve ser removida do colaborador
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool removeCollaborator(Collaborator* c, bool removeTask = true);

	///desassocia projeto da tarefa
	///@param removeTask indica se a tarefa deve ser removida do projeto
	///@return sucesso da operacao
	bool removeProject(bool removeTask=true);
	///remove todas as referencias a tarefa noutros objetos
	///@return sucesso da operacao
	bool removeTrace();
	///remove todas as referencias a tarefa noutros objetos, fora do projeto ao qual esta associado
	///@return sucesso da operacao
	bool removeTraceOutsideProject();
	///remove dependencia da tarefa
	///@param t tarefa a ser removida
	///@param removeDependant indica se a tarefa deve ser removida da sua dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependency(Task* t, bool removeDependant = true);
	///remove dependente da tarefa
	///@param t tarefa a ser removida
	///@param removeDependency indica se a tarefa deve ser removida da seu dependente
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
	///@param d data atual
	///@return data estimada de conclusao da tarefa
	Date getDateOfCompletion(const Date& d)const;
	///substitui IDs contidos na tarefa pelos apontadores para os objetos correspondentes
	void connect();
	///@return string com o nome e o ID da tarefa
	string toString() const;
	///poe o esforco da tarefa a 0, e remove todos os colaboradores da tarefa, adicionando a tarefa a lista de tarefas completadas dos colaboradores
	void complete();
	///@return indica se a tarefa esta concluida
	bool isCompleted() const;
	///atraso na tarefa
	///@param i atraso pretendido
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
	///@param t2 tarefa a ser comparada
	///@return tarefas sao iguais se tiverem o mesmo ID
	bool operator==(Task& t2);

	/// escrita de todos os dados da tarefa, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param out stream de saida
	/// @param t tarefa a ser escrita
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Task& t);

	/// leitura de todos os dados da tarefa, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param in stream de entrada
	/// @param t tarefa a ser lido
	/// @return stream de entrada
	friend istream & operator>>(istream& in, Task& t);
	///classe de excecao associada a tarefas
	class TaskExcept
	{
		///descricao da excecao
		string description;
	public:
		///construtor da excecao
		///@param description descricao
		///@param ID ID da tarefa
		TaskExcept(string description, int ID = -1);
		///@return descricao da excecao
		string operator()();
	};
	///interface de comparacao de tarefas
	class TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task& t1, const Task& t2) = 0;
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task* t1, const Task* t2) = 0;
		///@return abreviacao do comparador
		virtual string getAbbreviation() const=0;
	};
	///comparacao de tarefas por ordem alfabetica
	class TaskComparatorAlphabetic : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas por ID
	class TaskComparatorID : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas esforco restante
	class TaskComparatorEffort : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas por tempo estimado para a conclusao, sem dependencias
	class TaskComparatorEstimatedTime : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas por ordem alfabetica, com dependencias
	class TaskComparatorTimeToCompletion : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas por numero de dependentes
	class TaskComparatorNumDependants: public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre apontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de tarefas por numero de depencias
	class TaskComparatorNumDependencies : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2) ;
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
};
#endif
