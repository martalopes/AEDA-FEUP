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
<<<<<<< HEAD
	///construtor por defeito
	Task();
	///construtor sem ID especificado
	///@param name nome da tarefa
	///@param type tipo da tarefa
	///@param deadline prazo da tarefa
	///@param cost custo da tarefa
	Task(string name, string description, unsigned int effort);
	///construtor sem ID especificado
	///@param name nome da tarefa
	///@param type tipo da tarefa
	///@param deadline prazo da tarefa
	///@param cost custo da tarefa
	///@param setID o ID da tarefa
	Task(string name, string description, unsigned int effort, int setID);
	///@param i indice da tarefa
=======
	Task();
	Task(string name, string description, unsigned int effort);
	Task(string name, string description, unsigned int effort, int setID);
>>>>>>> origin/master
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
<<<<<<< HEAD
	///@param s string da nova descricao
	void setDescription(string s);

	///modifica nome da tarefa
	///@param nm string com o novo nome
	void setName(string nm);

	///modifica esforco da tarefa
	///@param ef novo esforco da tarefa
=======
	void setDescription(string s);

	///modifica nome da tarefa
	void setName(string nm);

	///modifica esforco da tarefa
>>>>>>> origin/master
	void setEffort(unsigned int ef);

	///@return esforco da tarefa
	int getEffort()const;

	///associa projeto a tarefa
<<<<<<< HEAD
	///@param p projeto a ser associado
	///@param addTask indica se a tarefa deve ser adicionada ao projeto
=======
	///@param projeto a ser associado
	///@param indica se a tarefa deve ser adicionada ao projeto
>>>>>>> origin/master
	///@throw projeto nao existe
	///@return sucesso da operacao
	bool setProject(Project* p, bool addTask = true);

	///adiciona dependencia a tarefa
<<<<<<< HEAD
	///@param t tarefa a ser associada
	///@param addDependant indica se a tarefa deve ser adicionada como dependente a dependencia
=======
	///@param tarefa a ser associada
	///@param indica se a tarefa deve ser adicionada como dependente a dependencia
>>>>>>> origin/master
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependency(Task* t, bool addDependant = true);

	///adiciona dependente a tarefa
<<<<<<< HEAD
	///@param t tarefa a ser associada
	///@param addDependency indica se a tarefa deve ser adicionada como  dependencia ao dependente
=======
	///@param tarefa a ser associada
	///@param indica se a tarefa deve ser adicionada como  dependencia ao dependente
>>>>>>> origin/master
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependant(Task* t, bool addDependency = true);

	///adiciona colaborador a tarefa
<<<<<<< HEAD
	///@param t1 colaborador a ser associado
	///@param hours numero de horas que o colaborador vai trabalhar na tarefa
	///@param addTask indica se a tarefa deve ser adicionada ao colaborador 
=======
	///@param colaborador a ser associado
	///@param numero de horas que o colaborador vai trabalhar na tarefa
>>>>>>> origin/master
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);

	///remove colaborador da tarefa
<<<<<<< HEAD
	///@param c colaborador a ser desassociado
	///@param removeTask indica se a tarefa deve ser removida do colaborador
=======
	///@param colaborador a ser desassociado
	///@param indica se a tarefa deve ser removida do colaborador
>>>>>>> origin/master
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool removeCollaborator(Collaborator* c, bool removeTask = true);

	///desassocia projeto da tarefa
<<<<<<< HEAD
	///@param removeTask indica se a tarefa deve ser removida do projeto
=======
	///@param indica se a tarefa deve ser removida do projeto
>>>>>>> origin/master
	///@return sucesso da operacao
	bool removeProject(bool removeTask=true);
	///remove todas as referencias a tarefa noutros objetos
	///@return sucesso da operacao
	bool removeTrace();
	///remove todas as referencias a tarefa noutros objetos, fora do projeto ao qual esta associado
	///@return sucesso da operacao
	bool removeTraceOutsideProject();
	///remove dependencia da tarefa
<<<<<<< HEAD
	///@param t tarefa a ser removida
	///@param removeDependant indica se a tarefa deve ser removida da sua dependencia
=======
	///@param tarefa a ser removida
	///@param indica se a tarefa deve ser removida da sua dependencia
>>>>>>> origin/master
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependency(Task* t, bool removeDependant = true);
	///remove dependente da tarefa
<<<<<<< HEAD
	///@param t tarefa a ser removida
	///@param removeDependency indica se a tarefa deve ser removida da seu dependente
=======
	///@param tarefa a ser removida
	///@param indica se a tarefa deve ser removida da seu dependente
>>>>>>> origin/master
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
<<<<<<< HEAD
	///@param d data atual
=======
	///@param data atual
>>>>>>> origin/master
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
<<<<<<< HEAD
	///@param i atraso pretendido
=======
	///@param atraso pretendido
>>>>>>> origin/master
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
<<<<<<< HEAD
	///@param t2 tarefa a ser comparada
=======
>>>>>>> origin/master
	///@return tarefas sao iguais se tiverem o mesmo ID
	bool operator==(Task& t2);

	/// escrita de todos os dados da tarefa, no lugar dos apontadores sao escritos os IDs dos objetos
<<<<<<< HEAD
	/// @param out stream de saida
	/// @param t tarefa a ser escrita
=======
	/// @param  stream de saida
	/// @param  tarefa a ser escrita
>>>>>>> origin/master
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Task& t);

	/// leitura de todos os dados da tarefa, no lugar dos apontadores sao lidos os IDs dos objetos
<<<<<<< HEAD
	/// @param in stream de entrada
	/// @param t tarefa a ser lido
=======
	/// @param  stream de entrada
	/// @param  tarefa a ser lido
>>>>>>> origin/master
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
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task& t1, const Task& t2) = 0;
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task& t1, const Task& t2) = 0;
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task* t1, const Task* t2) = 0;
		///@return abreviacao do comparador
		virtual string getAbbreviation() const=0;
	};
	class TaskComparatorAlphabetic : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorID : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorEffort : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorEstimatedTime : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorTimeToCompletion : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorNumDependants: public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	class TaskComparatorNumDependencies : public TaskComparator
	{
	public:
		///comparacao entre objetos da classe
<<<<<<< HEAD
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2) ;
		///comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
=======
		///@param objeto 1
		///@param objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2) ;
		///comparacao entre ápontadores para objetos da classe
		///@param objeto 1
		///@param objeto 2
>>>>>>> origin/master
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
};
#endif
