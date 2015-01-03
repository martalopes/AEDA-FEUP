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
	string contact;
	string address;
	int maxweeklyhours;// numero de horas de trabalho por semana;
	int workinghours;// numero total de horas de trabalho;
	vector<Project*> projects;
	vector<pair<Task*, unsigned int> > tasks;
	vector<Task*> finishedtasks;
public:
	///@brief construtor por defeito
	Collaborator();

	///@brief construtor sem ID especificado
	///@param name nome do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Collaborator(string name, int maxweeklyhours);

	///@brief construtor sem ID especificado, com contacto, morada
	///@param name nome do colaborador
	///@param name contacto do colaborador
	///@param name morada do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Collaborator(string name, string contact, string address, int maxweeklyhours);

	///@brief construtor com ID especificado
	///@param name nome do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	///@param setID ID do Colaborador
	Collaborator(string name, int maxweeklyhours, int setID);

	///@brief cria um colaborador generico
	///@param i indice do colaborador
	Collaborator(int i);

	///@brief retorna ID do colaborador 
	///@return ID do colaborador
	int getID() const;

	///@brief retorna nome do colaborador 
	///@return nome do colaborador
	string getName() const;

	///@brief retorna contacto do colaborador
	///@return contacto do colaborador
	string getContact() const;

	///@brief retorna morada do colaborador 
	///@return morada do colaborador
	string getAddress() const;

	///@brief retorna numero de horas que o colaborador trabalha atualmente  
	///@return numero de horas que o colaborador trabalha atualmente
	int getWorkingHours() const;

	///@brief retorna numero maximo de horas que o colaborador pode trabalhar  
	///@return numero maximo de horas que o colaborador pode trabalhar 
	int getMaxWeeklyHours() const;

	///@brief retorna projetos associados ao colaborador 
	///@return projetos associados ao colaborador
	vector<Project*> getProjects() const;

	///@brief retorna associacao entre as tarefas e as horas que o colaborador trabalha em cada uma 
	///@return associacao entre as tarefas e as horas que o colaborador trabalha em cada uma
	vector<pair<Task*, unsigned int> > getTasks() const;

	///@brief retorna tarefas terminadas do colaborador 
	///@return tarefas terminadas do colaborador
	vector<Task*> getFinishedTasks() const;

	///@briefremove tarefa e adiciona-a as tarefas terminadas
	///@param t tarefa a ser adicionada
	///@return sucesso da operacao
	bool reassign(Task* t);
	
	///retorna custo do colaborador 
	///@return custo do colaborador
	virtual double getCost()const;

	///@brief retorna titulo do colaborador 
	///@return titulo do colaborador
	virtual string getTitle()const;

	///@brief retorna string com o nome e o ID do colaborador 
	///@return string com o nome e o ID do colaborador
	string toString() const;

	///@brief modifica o ID do colaborador
	///@param newID novo ID do colaborador
	void setID(int newID);

	///@brief modifica o nome do colaborador
	///@param newname novo nome do colaborador
	void setName(string newname);

	///@brief modifica o contacto do colaborador
	///@param newcontact novo contacto do colaborador
	void setContact(string newcontact);

	///@brief modifica a morada do colaborador
	///@param nova morada do colaborador
	void setAddress(string newaddress);

	///@brief modifica as horas semanais maximas do colaborador
	///@param newhours novo maximo de horas de trabalho semanais
	void setWeeklyHours(int newhours);

	///@brief adiciona tarefa ao colaborador, atualizando os seus projetos
	///@param t1 tarefa a ser adicionada
	///@param hours horas que o colaborador trabalha por semana
	///@param addCollaborator indica se o colaborador deve ser adicionado a tarefa
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool addTask(Task* t1, unsigned int hours, bool addCollaborator=true);

	///@brief remove tarefa do colaborador, atualizando os seus projetos
	///@param t tarefa a ser removida
	///@param removeCollaborator indica se o colaborador deve ser removido da tarefa
	///@throw tarefa nao existe
	///@return sucesso da operacao
	bool removeTask(Task* t, bool removeCollaborator = true);

	///@brief remove todas as referencias ao colaborador noutros objetos
	///@return sucesso da operacao
	bool removeTrace();

	///@brief altera as horas de trabalho numa tarefa
	///@param t1 tarefa cujo horario se pretende alterar
	///@param hours novas horas da tarefa
	///@throw tarefa nula
	///@return sucesso da operacao
	bool changeTaskHours(Task* t1, unsigned int hours);

	///@brief cria um colaborador aleatorio e retorna um apontador para ele
	///@param i indice do colaborador
	///@return apontador para colaborador criado
	static Collaborator* newRandomCollaborator(int i);

	///@brief cria um colaborador com um determinado titulo
	///@param title titulo do colaborador a criar
	///@return apontador para o colaborador criado
	static Collaborator* newCollaboratorTitle(string title);

	///substitui os IDs lidos pelos apontadores para os objetos aos quais pertencem
	void connect();

	///@brief colabodores sao iguais se os seus IDs forem iguas
	///@param c2 colaborador a ser comparado
	///@return igualdade de colaboradores
	bool operator==(const Collaborator& c2)const;

	///@brief leitura de todos os dados do colaborador, no lugar dos apontadores sao lidos os IDs dos objetos
	///@param out stream de entrada
	///@param c colaborador a ser lido
	///@return stream de entreada
	friend ostream & operator<<(ostream& out, const Collaborator& c);

	///@brief leitura de todos os dados do colaborador, no lugar dos apontadores sao escritos os IDs dos objetos
	///@param in stream de entrada
	///@param c colaborador a ser lido
	///@return stream de entrada
	friend istream & operator>>(istream& in, Collaborator& c);

	///atualizacao da lista de projetos do colaborador
	void updateProjects();

	///saida do colaborador
	bool leave();

	///reentrada do colaborador
	bool reinstate();

	///indica se colaborador ja nao trabalha para a empresa
	bool isFormer()const;

	///classe de excepcao do colaborador
	class CollaboratorExcept
	{
		string description;
	public:
		///@brief class de excepcao associada a Colaboradores 
		///@param description descricao da excecao
		CollaboratorExcept(string description);

		///@return descricao da excepcao
		string operator()();
	};
	///interface de comparacao de colaboradores
	class CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		virtual bool operator()(const Collaborator& t1, const Collaborator& t2) = 0;

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		virtual bool operator()(const Collaborator* t1, const Collaborator* t2) = 0;

		///@return abreviacao do comparador
		virtual string getAbbreviation() const = 0;
	};
	///comparacao de colaboradores por ordem alfabetica
	class CollaboratorComparatorAlphabetic : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por custo
	class CollaboratorComparatorCost : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por ID
	class CollaboratorComparatorID : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por horas de trabalho semanais
	class CollaboratorComparatorWorkinghours : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por maximo de horas de trabalho semanais 
	class CollaboratorComparatorMaxWeeklyHours : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por numero de tarefas
	class CollaboratorComparatorNumTasks : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por experiencia (numero de tarefas terminadas)
	class CollaboratorComparatorExperience : public CollaboratorComparator
	{
	public:
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	///comparacao de colaboradores por numero de projetos em que estao envolvidos
	class CollaboratorComparatorNumProjects : public CollaboratorComparator
	{
	public:		
		///@brief comparacao entre colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator& t1, const Collaborator& t2);

		///@brief comparacao entre apontadores para colaboradores
		///@param t1 objecto1
		///@param t2 objecto2
		///@return colaborador 1 < colaborador 2
		bool operator()(const Collaborator* t1, const Collaborator* t2);

		///@return abreviacao do comparador
		string getAbbreviation() const;
	};
	private:
		///@return calcula os projetos em que o colaborador esta a trabalhar
		vector<Project*> calculateProjects()const;

};
/// especializacao de colaborador
class Programmer : public Collaborator
{
public:
	///@brief construtor sem ID
	///@param name nome do programador 
	///@param maxweeklyhours numero maximo de horas semanais
	Programmer(string name, int maxweeklyhours);

	///@brief construtor sem ID especificado, com contacto, morada
	///@param name nome do colaborador
	///@param name contacto do colaborador
	///@param name morada do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Programmer(string name, string contact, string address, int maxweeklyhours);

	///@brief construtor com ID
	///@param name nome do programador
	///@param maxweeklyhours numero maximo de horas semanais
	///@param setID ID do programador
	Programmer(string name, int maxweeklyhours, int setID);

	///@brief programador generico
	///@param i indice de programador
	Programmer(int i);

	///construtor por defeito
	Programmer();

	///@return custo do programador, igual para todos
	double getCost() const;

	///@return titulo do programador
	string getTitle() const;
private:

};
/// especializacao de colaborador
class Architect : public Collaborator
{
public:
	///@brief construtor sem ID
	///@param name nome do Arquitecto
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	Architect(string name, int maxweeklyhours);

	///@brief construtor sem ID especificado, com contacto, morada
	///@param name nome do colaborador
	///@param name contacto do colaborador
	///@param name morada do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Architect(string name, string contact, string address, int maxweeklyhours);

	///@brief construtor com ID
	///@param name nome do Arquitecto
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	///@param setID ID do Arquitecto
	Architect(string name, int maxweeklyhours, int setID);

	///@brief arquiteto generico
	///@param i indice de Arquitecto
	Architect(int i);

	///contrutor por defeito
	Architect();

	///@return custo de um arquitecto, igual para todos
	double getCost() const ;

	///@return titulo do arquitecto
	string getTitle() const;
private:

};
/// especializacao de colaborador
class Manager : public Collaborator
{
public:
	///@brief construtor sem ID
	///@param name nome do Gestor
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	Manager(string name, int maxweeklyhours);

	///@brief construtor sem ID especificado, com contacto, morada
	///@param name nome do colaborador
	///@param name contacto do colaborador
	///@param name morada do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Manager(string name, string contact, string address, int maxweeklyhours);

	///@brief construtor com ID
	///@param name nome do Gestor
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	///@param setID o ID do gestor
	Manager(string name, int maxweeklyhours, int setID);

	///@brief gestor generico
	///@param i indice de Gestor
	Manager(int i);

	///construtor por defeito
	Manager();

	///@return custo de um gestor, igual para todos
	double getCost() const;

	///@return titulo de um arquitecto, igual para todos
	string getTitle() const;
private:

};
/// especializacao de colaborador
class Tester : public Collaborator
{
public:
	///@brief construtor sem ID
	///@param name nome do Tester
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	Tester(string name, int maxweeklyhours);

	///@brief construtor sem ID especificado, com contacto, morada
	///@param name nome do colaborador
	///@param name contacto do colaborador
	///@param name morada do colaborador
	///@param maxweeklyhours numero maximo de horas por semana  
	Tester(string name, string contact, string address, int maxweeklyhours);

	///@brief construtor com ID
	///@param name nome do Tester
	///@param maxweeklyhours numero maximo de horas semanais de trabalho
	///@param setID o ID do Tester 
	Tester(string name, int maxweeklyhours, int setID) ;

	///@brief tester generico
	///@param i indice de Tester
	Tester(int i);

	///construtor por defeito
	Tester();

	///@return custo de um tester, igual para todos
	double getCost() const;

	///@return titulo de um tester, igual para todos
	string getTitle() const;
private:

};


#endif
