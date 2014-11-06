#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"


#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

#define NUM_PROJECTS 10
#define NUM_CLIENTS 5
#define NUM_COLLABORATOR 50
#define NUM_TASKS 100

using namespace std;


class Application
{
	friend class Client;
	friend class Task;
	friend class Collaborator;
	friend class Project;
public:
	///class de excepcao associada a Aplicacao
	class ApplicationExcept
	{
		string description;
	public:
		ApplicationExcept(string description);
		/// @return descricao
		string operator()();
	};
protected:
	///construtor da classe nao e acessivel fora da classe - apenas existira um objeto da classe
	Application();
public:
	/// apenas pode existir um objeto da classe
	/// se ainda nao tiver sido criado um objeto da classe, e criado um, senao retorna um apontador para esse objeto
	/// @return apontador para aplicacao
	static Application* Instance();
	///destrutor
	~Application();
	/// elimina todos os dados da aplicacao, permitindo a recuperacao da memoria ocupada por eles
	static void clear();
	///@return projetos
	static vector<Project*> getProjects();
	///@return clientes
	static vector<Client*> getClients();
	///@return colaboradores
	static vector<Collaborator*> getCollaborators();
	///@return tarefas
	static vector<Task*> getTasks();
	/// obter um projeto a partir do seu ID
	/// @throw projeto nao existe
	/// @param ID do projeto
	/// @return apontador para o projeto
	static Project* getProjectPtr(int ID);

	/// obter um cliente a partir do seu ID
	/// @throw cliente nao existe
	/// @param ID do cliente
	/// @return apontador para o cliente
	static Client* getClientPtr(int ID);

	/// obter um colaborador a partir do seu ID
	/// @throw colaborador nao existe
	/// @param ID do colaborador
	/// @return apontador para o colaborador
	static Collaborator* getCollaboratorPtr(int ID);

	/// obter uma tarefa a partir do seu ID
	/// @throw tarefa nao existe
	/// @param ID da tarefa
	/// @return apontador para a tarefa
	static Task* getTaskPtr(int ID);

	/// adicionar projeto a aplicacao
	/// @throw projeto ja existe
	/// @param apontador para o projeto
	static void addProject(Project* p);

	/// adicionar cliente a aplicacao
	/// @throw cliente ja existe
	/// @param apontador para o cliente
	static void addClient(Client* c);

	/// adicionar colaborador a aplicacao
	/// @throw colaborador ja existe
	/// @param apontador para o colaborador
	static void addCollaborator(Collaborator* c);

	/// adicionar tarefa a aplicacao
	/// @throw tarefa ja existe
	/// @param apontador para a tarefa
	static void addTask(Task* t);
	
	/// remove projeto da aplicacao
	/// @throw projeto nao existe
	/// @param apontador para a projeto
	/// @return sucesso da operacao
	static bool removeProject(Project* p);

	/// remove cliente da aplicacao
	/// @throw cliente nao existe
	/// @param apontador para a cliente
	/// @return sucesso da operacao
	static bool removeClient(Client* c);

	/// remove tarefa da aplicacao
	/// @throw tarefa nao existe
	/// @param apontador para a tarefa
	/// @return sucesso da operacao
	static bool removeTask(Task* t);

	/// remove colaborador da aplicacao
	/// @throw colaborador nao existe
	/// @param apontador para a colaborador
	/// @return sucesso da operacao
	static bool removeCollaborator(Collaborator* c);


	/*escrita*/

	///escreve os dados do sistema em ficheiros
	static void writeFiles();
	///escreve os projetos do sistema em ficheiros
	///@param output file stream
	static void writeProjects(ofstream& fout);

	///escreve os clientes do sistema em ficheiros
	///@param output file stream
	static void writeClients(ofstream& fout);

	///escreve os colaboradores do sistema em ficheiros
	///@param output file stream
	static void writeCollaborators(ofstream& fout);

	///escreve os tarefas do sistema em ficheiros
	///@param output file stream
	static void writeTasks(ofstream& fout);

	/*leitura*/
	///le dos ficheiros os dados do sistema
	static void readFiles();
	///le os projetos do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@param input file stream
	static void readProjects(ifstream& fin);

	///le os clientes do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@param input file stream
	static void readClients(ifstream& fin);

	///le os colaboradores do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@param input file stream
	static void readCollaborators(ifstream& fin);

	///le os tarefas do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@param input file stream
	static void readTasks(ifstream& fin);

	///substitui os IDs nos atributos pelos apontadores para os objetos corretos
	static void connect();

	///simula uma semana de trabalho
	static void tick();

	///gera os dados da aplicacao
	static void genApplication();
	///@return data atual da aplicacao
	static Date getDate();
private:
	static vector<Project*> projects;
	static vector<Client*> clients;
	static vector<Collaborator*> collaborators;
	static vector<Task*> tasks;
	///data atual
	static Date d;
	///apontador para o unico objeto da class
	static Application* instance;
};



#endif
