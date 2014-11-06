#ifndef COLLABORATOR_H
#define COLLABORATOR_H



#include "Client.h"
#include "Project.h"
#include "Date.h"
#include "Application.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

#define PROGRAMMER_COST 35.71
#define ARCHITECT_COST 44.88
#define MANAGER_COST 40.54
#define TESTER_COST 25.89

class Task;
class Project;
class Programmer;
class Architect;
class Manager;
class Testers;

class Collaborator
{
protected:
	static int lastID;
private:
	int ID;
	string name;
	int maxweeklyhours;// numero de horas de trabalho por semana;
	int workinghours;// numero total de horas de trabalho;
	vector<Project*> projects;
	vector<pair<Task*, unsigned int> > tasks;
	vector<Task*> finishedtasks;
public:
	
	Collaborator();
	Collaborator(string name, int maxweeklyhours);
	Collaborator(string name, int maxweeklyhours, int setID);
	///cria um colaborador generico
	Collaborator(int i);
	///@return ID do colaborador
	int getID() const;

	///@return nome do colaborador
	string getName() const;

	///@return numero de horas que o colaborador trabalha atualmente
	int getWorkingHours() const;

	///@return numero maximo de horas que o colaborador pode trabalhar 
	int getMaxWeeklyHours() const;

	///@return projetos associados ao colaborador
	vector<Project*> getProjects() const;

	///@return associacao entre as tarefas e as horas que o colaborador trabalha em cada uma
	vector<pair<Task*, unsigned int> > getTasks() const;

	///@return tarefas terminadas do colaborador
	vector<Task*> getFinishedTasks() const;

	///remove tarefa e adiciona-a as tarefas terminadas
	///@return sucesso da operacao
	bool reassign(Task* t);
	
	///@return custo do colaborador
	virtual double getCost()const;
	///@return titulo do colaborador
	virtual string getTitle()const;

	///@return string com o nome e o ID do colaborador
	string toString() const;
	///modifica o ID do colaborador
	///@param novo ID do colaborador
	void setID(int newID);
	///modifica o nome do colaborador
	///@param novo nome do colaborador
	void setName(string newname);
	///modifica as horas semanais maximas do colaborador
	///@param novo maximo
	void setWeeklyHours(int newhours);

	///adiciona tarefa ao colaborador, atualizando os seus projetos
	///@param tarefa a ser adicionada
	///@param horas que o colaborador trabalha por semana
	///@param indica se o colaborador deve ser adicionado a tarefa
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addTask(Task* t1, unsigned int hours, bool addCollaborator=true);

	///remove tarefa do colaborador, atualizando os seus projetos
	///@param tarefa a ser removida
	///@param indica se o colaborador deve ser removido da tarefa
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeTask(Task* t, bool removeCollaborator = true);

	///remove projeto do colaborador
	///@param projeto a ser removida
	///@param indica se o colaborador deve ser removido do projeto
	///@throw projeto nao existe
	///@return sucesso da operacao
	//bool removeProject(Project* p, bool removeCollaborator = true);
	///remove todas as referencias ao colaborador noutros objetos
	///@return sucesso da operacao
	bool removeTrace();
	///altera as horas de trabalho numa tarefa
	///@param tarefa cujo horario se pretende alterar
	///
	bool changeTaskHours(Task* t1, unsigned int hours);////

	///adiciona projeto ao colaborador
	///@param projeto
	///@param indica se colaborador deve ser adicionado ao projeto
	///@throw projeto nao existe
	///@return sucesso da operacao
	//bool addProject(Project* p, bool addCollaborator = true);
	///cria um colaborador aleatorio e retorna um apontador para ele
	///@return apotador para colaborador criado
	static Collaborator* newRandomCollaborator(int i);
	/// cria um colaborador com um determinado titulo
	/// @param titulo do colaborador a criar
	/// @return apontador para o colaborador criado
	static Collaborator* newCollaboratorTitle(string title);
	/// substitui os IDs lidos pelos apontadores para os objetos aos quais pertencem 
	void connect();
	/// colabodores sao iguais se os seus IDs forem iguas
	/// @return igualdade de colaboradores
	bool operator==(const Collaborator& c2)const;

	/// leitura de todos os dados do colaborador, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param  stream de entrada
	/// @param  colaborador a ser lido
	/// @return stream de entreada
	friend ostream & operator<<(ostream& out, const Collaborator& c);

	/// leitura de todos os dados do colaborador, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param  stream de entrada
	/// @param  colaborador a ser lido
	/// @return stream de entrada
	friend istream & operator>>(istream& in, Collaborator& c);
	///atualizacao da lista de projetos do colaborador
	void updateProjects();
	///classe de excepcao do colaborador
	class CollaboratorExcept
	{
		string description;
	public:
		CollaboratorExcept(string description);
		///@return descricao da excepcao
		string operator()();
	};
	class CollaboratorComparator
	{
	public:
		///comparacao entre colaboradores
		///@return colaborador 1 < colaborador 2
		virtual bool operator()(const Collaborator& t1, const Collaborator& t2) = 0;
		///comparacao entre apontadores para colaboradores
		///@return colaborador 1 < colaborador 2
		virtual bool operator()(const Collaborator* t1, const Collaborator* t2) = 0;
		///@return abreviacao do comparador
		virtual string getAbbreviation() const = 0;
	};
	class CollaboratorComparatorAlphabetic : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorCost : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorID : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorWorkinghours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorMaxWeeklyHours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorNumTasks : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorExperience : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	class CollaboratorComparatorNumProjects : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2);
		bool operator()(const Collaborator* t1, const Collaborator* t2);
		string getAbbreviation() const;
	};
	private:
		///@return calcula os projetos em que o colaborador esta a trabalhar
		vector<Project*> calculateProjects()const;

};

class Programmer : public Collaborator
{
public:

	Programmer(string name, int maxweeklyhours);
	Programmer(string name, int maxweeklyhours, int setID);
	Programmer(int i);
	Programmer() ;
	double getCost() const;
	string getTitle() const;
private:

};
class Architect : public Collaborator
{
public:
	Architect(string name, int maxweeklyhours);
	Architect(string name, int maxweeklyhours, int setID);
	Architect(int i);
	Architect();
	double getCost() const ;
	string getTitle() const;
private:

};
class Manager : public Collaborator
{
public:
	Manager(string name, int maxweeklyhours);
	Manager(string name, int maxweeklyhours, int setID);
	Manager(int i);
	Manager();
	double getCost() const ;
	string getTitle() const;
private:

};
class Tester : public Collaborator
{
public:
	Tester(string name, int maxweeklyhours);
	Tester(string name, int maxweeklyhours, int setID) ;
	Tester(int i);
	Tester() ;
	double getCost() const ;
	string getTitle() const;
private:

};


#endif
