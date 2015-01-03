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
	///@brief construtor sem ID especificado
	///@param name nome da tarefa
	///@param description descricao da tarefa
	///@param effort esforco restante para terminar a tarefa
	Task(string name, string description, unsigned int effort);
	///@brief construtor sem ID especificado
	///@param name nome da tarefa
	///@param description descricao da tarefa
	///@param effort esforco restante para terminar a tarefa
	///@param setID o ID da tarefa
	Task(string name, string description, unsigned int effort, int setID);
	///@brief retorna indice da tarefa
	///@param i indice da tarefa
	Task(int i);
	///@brief retorna nome da tarefa
	///@return nome da tarefa
	string getName() const;
	///@brief retorna ID da tarefa 
	///@return ID da tarefa
	int getID() const ;
	///@brief retorna projeto associado a tarefa  
	///@return projeto associado a tarefa
	Project* getProject()const;
	///@brief retorna tarefas que dependem da tarefa  
	///@return tarefas que dependem da tarefa
	vector<Task*> getDependants() const;
	///@brief retorna tarefas das quais depende a tarefa  
	///@return tarefas das quais depende a tarefa
	vector<Task*> getDependencies() const;
	///@brief retorna lista de pares formado pelo colaborador e as horas que dedica a essa tarefa  
	///@return lista de pares formado pelo colaborador e as horas que dedica a essa tarefa
	vector<pair<Collaborator*, unsigned int> > getCollaborators() const;
	///@brief retorna descricao da tarefa 
	///@return descricao da tarefa
	string getDescription()const;
	///@brief modifica descricao da tarefa
	///@param s string da nova descricao
	void setDescription(string s);

	///@brief modifica nome da tarefa
	///@param nm string com o novo nome
	void setName(string nm);

	///@brief modifica esforco da tarefa
	///@param ef novo esforco da tarefa
	void setEffort(unsigned int ef);

	///@brief retorna esforco da tarefa 
	///@return esforco da tarefa
	int getEffort()const;

	///@brief associa projeto a tarefa
	///@param p projeto a ser associado
	///@param addTask indica se a tarefa deve ser adicionada ao projeto
	///@throw projeto nao existe
	///@return sucesso da operacao
	bool setProject(Project* p, bool addTask = true);

	///@brief adiciona dependencia a tarefa
	///@param t tarefa a ser associada
	///@param addDependant indica se a tarefa deve ser adicionada como dependente a dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependency(Task* t, bool addDependant = true);

	///@brief adiciona dependente a tarefa
	///@param t tarefa a ser associada
	///@param addDependency indica se a tarefa deve ser adicionada como  dependencia ao dependente
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addDependant(Task* t, bool addDependency = true);

	///@brief adiciona colaborador a tarefa
	///@param t1 colaborador a ser associado
	///@param hours numero de horas que o colaborador vai trabalhar na tarefa
	///@param addTask indica se a tarefa deve ser adicionada ao colaborador 
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool addCollaborator(Collaborator* t1, unsigned int hours, bool addTask = true);

	///@brief remove colaborador da tarefa
	///@param c colaborador a ser desassociado
	///@param removeTask indica se a tarefa deve ser removida do colaborador
	///@throw colaborador nao existe
	///@return sucesso da operacao
	bool removeCollaborator(Collaborator* c, bool removeTask = true);

	///@brief desassocia projeto da tarefa
	///@param removeTask indica se a tarefa deve ser removida do projeto
	///@return sucesso da operacao
	bool removeProject(bool removeTask=true);
	///@brief remove todas as referencias a tarefa noutros objetos
	///@return sucesso da operacao
	bool removeTrace();
	///@brief remove todas as referencias a tarefa noutros objetos, fora do projeto ao qual esta associado
	///@return sucesso da operacao
	bool removeTraceOutsideProject();
	///@brief remove dependencia da tarefa
	///@param t tarefa a ser removida
	///@param removeDependant indica se a tarefa deve ser removida da sua dependencia
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependency(Task* t, bool removeDependant = true);
	///@brief remove dependente da tarefa
	///@param t tarefa a ser removida
	///@param removeDependency indica se a tarefa deve ser removida da seu dependente
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeDependant(Task* t, bool removeDependency = true);
	///@brief retorna o 
	///@return tempo estimado de realizacao da tarefa, sem contar com dependencias, em semanas, -1 se a tarefa nao estiver a ser trabalhada
	double calculateEstimatedTime() const; 
	///@brief retorna tempo que falta para a conclusao da tarefa, a contar com dependencias, em semanas, -1 se a tarefa ou 1 das suas dependencias nao estivera ser trabalhada 
	///@return tempo que falta para a conclusao da tarefa, a contar com dependencias, em semanas, -1 se a tarefa ou 1 das suas dependencias nao estivera ser trabalhada
	double calculateTimeToCompletion() const;
	///@brief verifica se uma tarefa pode ser trabalhada quando todas as tarefas de que depende ja se encontram realizadas 
	///@return uma tarefa pode ser trabalhada quando todas as tarefas de que depende ja se encontram realizadas
	bool isReady()const; 
	///@brief semana de trabalho
	///@return custo daquela semana de trabalho
	double tick();
	///@brief retorna data estimada de conclusao da tarefa  
	///@param d data atual
	///@return data estimada de conclusao da tarefa
	Date getDateOfCompletion(const Date& d)const;
	///substitui IDs contidos na tarefa pelos apontadores para os objetos correspondentes
	void connect();
	///@brief retorna string com o nome e o ID da tarefa  
	///@return string com o nome e o ID da tarefa
	string toString() const;
	///poe o esforco da tarefa a 0, e remove todos os colaboradores da tarefa, adicionando a tarefa a lista de tarefas completadas dos colaboradores
	void complete();
	///@brief verifica se a tarefa esta concluida 
	///@return indica se a tarefa esta concluida
	bool isCompleted() const;
	///@brief atraso na tarefa
	///@param i atraso pretendido
	///@return sucesso da operacao
	bool delay(int i);
	///@brief atraso aleatorio na tarefa
	///@return sucesso da operacao
	bool delay();
	///@brief adiantamento aleatorio na tarefa
	///@return sucesso da operacao
	bool speedup();
	///@brief verifica se uma tarefa nao esta associada a outras por dependencias 
	///@return verdadeiro se uma tarefa nao esta associada a outras por dependencias
	bool isIsolated()const;
	///@brief overload do operador de igualdade associado a tarefas  
	///@param t2 tarefa a ser comparada
	///@return tarefas sao iguais se tiverem o mesmo ID
	bool operator==(Task& t2);

	///@brief escrita de todos os dados da tarefa, no lugar dos apontadores sao escritos os IDs dos objetos
	///@param out stream de saida
	///@param t tarefa a ser escrita
	///@return stream de saida
	friend ostream & operator<<(ostream& out, const Task& t);

	///@brief leitura de todos os dados da tarefa, no lugar dos apontadores sao lidos os IDs dos objetos
	///@param in stream de entrada
	///@param t tarefa a ser lido
	///@return stream de entrada
	friend istream & operator>>(istream& in, Task& t);
	///classe de excecao associada a tarefas
	class TaskExcept
	{
		///descricao da excecao
		string description;
	public:
		///@brief construtor da excecao
		///@param description descricao
		///@param ID ID da tarefa
		TaskExcept(string description, int ID = -1);
		///@brief retorna descricao da excecao
		///@return descricao da excecao
		string operator()();
	};
	///interface de comparacao de tarefas
	class TaskComparator
	{
	public:
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		virtual bool operator()(const Task& t1, const Task& t2) = 0;
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre ápontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2);
		///@brief comparacao entre apontadores para objetos da classe
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
		///@brief comparacao entre objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task& t1, const Task& t2) ;
		///@brief comparacao entre ápontadores para objetos da classe
		///@param t1 objeto 1
		///@param t2 objeto 2
		///@return verdadeiro se objeto 1 < objeto 2
		bool operator()(const Task* t1, const Task* t2);
		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
};
#endif
