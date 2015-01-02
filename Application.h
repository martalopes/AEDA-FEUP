#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"
#include "BST.h"
#include "SmartPtr.h"
#include "CV.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <unordered_set>

#define NUM_PROJECTS 10
#define NUM_CLIENTS 5
#define NUM_COLLABORATOR 50
#define NUM_TASKS 100
#define NUM_CVS 50

using namespace std;


class Collaborator;
class CV;

struct CollaboratorEqual
{
	///@param c1 colaborador
	///@param c2 colaborador
	///@return verdadeiro se os colaboradores forem iguais
	bool operator()(Collaborator* const c1, Collaborator* const c2) const;
};
struct  CollaboratorHash
{
	///@param c colaborador
	///@return ID do colaborador
	size_t operator()(Collaborator* const  c) const;
};
class CVcomparator
{
public:
	///@param c1 candidato
	///@param c2 candidato
	///@return verdadeiro se os candidatos forem iguais
	bool operator()(const CV* c1, const CV* c2);
};
typedef unordered_set<Collaborator*, CollaboratorHash, CollaboratorEqual> Colhash;
typedef unordered_set<Collaborator*, CollaboratorHash, CollaboratorEqual>::iterator Colhash_it;
typedef unordered_set<Collaborator*, CollaboratorHash, CollaboratorEqual>::const_iterator const_Colhash_it;

typedef priority_queue<CV*, vector<CV*>, CVcomparator> CV_queue;

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
	///@return clientes /////////////////////////////////////////////////////////////////////
	static vector<Client*> getClients(BSTItr<SmartPtr<Client>> * it);
	static vector<Client*> getClients_InOrder();
	static vector<Client*> getClients_PreOrder();
	static vector<Client*> getClients_PostOrder();
	static vector<Client*> getClients_Level();

	///cria a bst
	static void fillBST();

	///atualiza as ordens dos clientes
	static void updateClientOrder();

	////////////////////////////////////////////////////////////////////
	///@return colaboradores
	static vector<Collaborator*> getCollaborators();
	
	///@return colaboradores antigos
	static vector<Collaborator*> getFormerCollaborators();

	///@return candidatos
	static vector<CV*> getCVs();

	///atualiza a ordem dos candidatos
	static void updateCVorder();

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

	/// faz com quem um certo colaborador atual passe a ser um colaborador antigo
	/// @throw se o colaborador já estiver na lista de colaboradores antigos
	/// @param c apontador para o colaborador
	static void setFormer(Collaborator* c);

	///adiciona um candidato novo
	///@param c candidato
	static void addCV(CV* c);

	///transforma um candidato em colaborador
	///@param c candidato
	///@param weeklyHours horas máximas que ele trabalhará
	static void hire(CV * c, int weeklyHours);

	///remove um candidato
	///@param c candidato
	static void removeCV(CV* c);

	/// adicionar tarefa a aplicacao
	/// @throw tarefa ja existe
	/// @param t apontador para a tarefa
	static void addTask(Task* t);
	
	/// remove projeto da aplicacao
	/// @throw projeto nao existe
	/// @param p apontador para o projeto
	/// @return sucesso da operacao
	static bool removeProject(Project* p);

	/// remove cliente da aplicacao
	/// @throw cliente nao existe
	/// @param c apontador para o cliente
	/// @return sucesso da operacao
	static bool removeClient(Client* c);

	/// remove tarefa da aplicacao
	/// @throw tarefa nao existe
	/// @param t apontador para a tarefa
	/// @return sucesso da operacao
	static bool removeTask(Task* t);

	/// remove colaborador da aplicacao
	/// @throw colaborador nao existe
	/// @param c apontador para o colaborador
	/// @return sucesso da operacao
	static bool removeCollaborator(Collaborator* c);

	/// remove colaborador antigo da aplicacao
	/// @throw colaborador antigo nao existe
	/// @param c apontador para o colaborador antigo
	/// @return sucesso da operacao
	static bool removeFormerCollaborator(Collaborator* c);

	/// faz com que o colaborador deixe de ser antigo
	/// @throw se o colaborador já estiver empregue na empresa
	/// @throw se o colaborador não existir
	/// @param c apontador para o colaborador antigo
	static void unsetFormer(Collaborator* c);

	/*escrita*/

	///escreve os dados do sistema em ficheiros
	static void writeFiles();
	///escreve os projetos do sistema em ficheiros
	///@param fout output file stream
	static void writeProjects(ofstream& fout);

	///escreve os clientes do sistema em ficheiros
	///@param fout output file stream
	static void writeClients(ofstream& fout);

	///escreve os colaboradores do sistema em ficheiros
	///@param fout output file stream
	static void writeCollaborators(ofstream& fout);

	///escreve os colaboradores antigos em ficheiros
	///@param fout output file stream
	static void writeFormerCollaborators(ofstream& fout);

	///escreve todos os candidatos em ficheiros
	///@param fout output file stream
	static void writeCVs(ofstream& fout);

	///escreve os tarefas do sistema em ficheiros
	///@param fout output file stream
	static void writeTasks(ofstream& fout);

	/*leitura*/
	///le dos ficheiros os dados do sistema
	static void readFiles();
	///le os projetos do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
	///@param fin input file stream
	static void readProjects(ifstream& fin);

	///le os clientes do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
	///@param fin input file stream
	static void readClients(ifstream& fin);

	///le os colaboradores do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
	///@param fin input file stream
	static void readCollaborators(ifstream& fin);

	static void readFormerCollaborators(ifstream& fin);

	static void readCVs(ifstream& fin);

	///le os tarefas do sistema
	///no lugar dos apontadores escreve os IDs dos objetos para os quais apontam
	///@throw ficheiro nao existe
	///@param fin input file stream
	static void readTasks(ifstream& fin);

	///le a data do sistema
	///@throw ficheiro nao existe
	///@param fin input file stream
	static void readApp(ifstream& fin);
	
	///escreve a data do sistema
	//@param fout output file stream
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
	static BST<SmartPtr<Client>> clients;
	///colaboradores guardados no sistema
	static vector<Collaborator*> collaborators;
	///tarefas guaradas no sistema
	static vector<Task*> tasks;

	///antigos colaboradores
	static Colhash former_collaborators;

	///candidatos
	static CV_queue cvs;

	///data atual
	static Date d;
	///apontador para o unico objeto da class
	static Application* instance;
};




#endif
