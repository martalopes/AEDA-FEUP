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
	///class de excepção associada a Aplicações 
	class ApplicationExcept
	{
		string description;
	public:
		ApplicationExcept(string description);
		string operator()();
	};
protected:
	///construtor da classe não é acessivel fora da classe - apenas existirá um objeto da classe
	Application();
public:
	/// apenas pode existir um objeto da classe
	/// se ainda nao tiver sido criado um objeto da classe, é criado um, senao retorna um apontador para esse objeto
	/// @return apontador para aplicacao
	static Application* Instance();
	
	~Application();
	/// elimina todos os dados da aplicacao, permitindo a recuperacao da memoria ocupada por eles
	static void clear();
	static vector<Project*> getProjects();
	static vector<Client*> getClients();
	static vector<Collaborator*> getCollaborators();
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
	/// @throw 
	/// @param apontador para a tarefa
	static bool removeProject(Project* p);
	static bool removeClient(Client* c);
	static bool removeTask(Task* t);
	static bool removeCollaborator(Collaborator* c);


	/*escrita*/

	static void writeFiles(); //função que escreve nos ficheiros 
	static void writeProjects(ofstream& fout);
	static void writeClients(ofstream& fout);
	static void writeCollaborators(ofstream& fout);
	static void writeTasks(ofstream& fout);

	/*leitura*/

	static void readFiles(); //função que lê dos ficheiros
	static void readProjects(ifstream& fin);
	static void readClients(ifstream& fin);
	static void readCollaborators(ifstream& fin);
	static void readTasks(ifstream& fin);
	static void connect();

	static void tick(); //guarda no vector de projectos o custo de cada projecto
	static void genApplication(); //função geradora de Applications
	static Date getDate();
private:
	static vector<Project*> projects;
	static vector<Client*> clients;
	static vector<Collaborator*> collaborators;
	static vector<Task*> tasks;
	static Date d;
	static Application* instance;
};



#endif
