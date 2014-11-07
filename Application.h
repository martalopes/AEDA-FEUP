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
		///descricao da excecao
		string description;
	public:
		///construtor de excecao
		ApplicationExcept(string description);
		/// @return descricao da excecao
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
	/// @param ID ID do projeto
	/// @return apontador para o projeto
	static Project* getProjectPtr(int ID);

	/// obter um cliente a partir do seu ID
	/// @throw cliente nao existe
	/// @param ID ID do cliente
	/// @return apontador para o cliente
	static Client* getClientPtr(int ID);

	/// obter um colaborador a partir do seu ID
	/// @throw colaborador nao existe
	/// @param ID ID do colaborador
	/// @return apontador para o colaborador
	static Collaborator* getCollaboratorPtr(int ID);

	/// obter uma tarefa a partir do seu ID
	/// @throw tarefa nao existe
	/// @param ID ID da tarefa
	/// @return apontador para a tarefa
	static Task* getTaskPtr(int ID);

	/// adicionar projeto a aplicacao
	/// @throw projeto ja existe
	/// @param p apontador para o projeto
	static void addProject(Project* p);

	/// adicionar cliente a aplicacao
	/// @throw cliente ja existe
	/// @param c apontador para o cliente
	static void addClient(Client* c);

	/// adicionar colaborador a aplicacao
	/// @throw colaborador ja existe
	/// @param c apontador para o colaborador
	static void addCollaborator(Collaborator* c);

	/// adicionar tarefa a aplicacao
	/// @throw tarefa ja existe
	/// @param t apontador para a tarefa
	static void addTask(Task* t);
	
	/// remove projeto da aplicacao
	/// @throw projeto nao existe
<<<<<<< HEAD
	/// @param p apontador para o projeto
=======
	/// @param apontador para o projeto
>>>>>>> origin/master
	/// @return sucesso da operacao
	static bool removeProject(Project* p);

	/// remove cliente da aplicacao
	/// @throw cliente nao existe
<<<<<<< HEAD
	/// @param c apontador para o cliente
=======
	/// @param apontador para o cliente
>>>>>>> origin/master
	/// @return sucesso da operacao
	static bool removeClient(Client* c);

	/// remove tarefa da aplicacao
	/// @throw tarefa nao existe
<<<<<<< HEAD
	/// @param t apontador para a tarefa
=======
	/// @param apontador para a tarefa
>>>>>>> origin/master
	/// @return sucesso da operacao
	static bool removeTask(Task* t);

	/// remove colaborador da aplicacao
	/// @throw colaborador nao existe
<<<<<<< HEAD
	/// @param c apontador para o colaborador
=======
	/// @param apontador para o colaborador
>>>>>>> origin/master
	/// @return sucesso da operacao
	static bool removeCollaborator(Collaborator* c);


	/*escrita*/

	///escreve os dados do sistema em ficheiros
	static void writeFiles();
	///escreve os projetos do sistema em ficheiros
<<<<<<< HEAD
	///@param fout output file stream
	static void writeProjects(ofstream& fout);

	///escreve os clientes do sistema em ficheiros
	///@param fout output file stream
	static void writeClients(ofstream& fout);

	///escreve os colaboradores do sistema em ficheiros
	///@param fout output file stream
	static void writeCollaborators(ofstream& fout);

	///escreve os tarefas do sistema em ficheiros
	///@param fout output file stream
=======
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
>>>>>>> origin/master
	static void writeTasks(ofstream& fout);

	/*leitura*/
	///le dos ficheiros os dados do sistema
	static void readFiles();
	///le os projetos do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
<<<<<<< HEAD
	///@param fin input file stream
=======
	///@param input file stream
>>>>>>> origin/master
	static void readProjects(ifstream& fin);

	///le os clientes do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
<<<<<<< HEAD
	///@param fin input file stream
=======
	///@param input file stream
>>>>>>> origin/master
	static void readClients(ifstream& fin);

	///le os colaboradores do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
<<<<<<< HEAD
	///@param fin input file stream
=======
	///@param input file stream
>>>>>>> origin/master
	static void readCollaborators(ifstream& fin);

	///le os tarefas do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
<<<<<<< HEAD
	///@param fin input file stream
=======
	///@param input file stream
>>>>>>> origin/master
	static void readTasks(ifstream& fin);

	///le a data do sistema
	///@throw ficheiro nao existe
<<<<<<< HEAD
	///@param fin input file stream
	static void readApp(ifstream& fin);
	
	///escreve a data do sistema
	//@param fout output file stream
=======
	///@param input file stream
	static void readApp(ifstream& fin);
	
	///escreve a data do sistema
	//@param output file stream
>>>>>>> origin/master
	static void writeApp(ofstream& fout);

	///substitui os IDs nos atributos pelos apontadores para os objetos corretos
	static void connect();

	///simula uma semana de trabalho
	static void tick();

	///gera os dados da aplicacao
	static void genApplication();
	///@return data atual da aplicacao
	static Date getDate();
private:
	///projetos guardados no sistema
	static vector<Project*> projects;
	///clientes guardados no sistema
	static vector<Client*> clients;
	///colaboradores guardados no sistema
	static vector<Collaborator*> collaborators;
	///tarefas guaradas no sistema
	static vector<Task*> tasks;
	///data atual
	static Date d;
	///apontador para o unico objeto da class
	static Application* instance;
};



#endif
