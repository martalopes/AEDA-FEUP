#ifndef PROJECT_H
#define PROJECT_H


#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"
#include "Application.h"
#include "Menu.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
Project Class:
Cada projecto vai ser composto/identificado:
por nome,
por um tipo,
para facilitar a identificação do projecto será atribuido um ID a cada um,
tem um prazo associado,
é composto por tarefas,
colaboradores, pois cada projecto vai ser implementado por colaboradores diferentes.
tem um cliente associado.
*/

using namespace std;

class Client;
class Task;
class Collaborator;

class Project
{
private:
	int ID;
	static int lastID;
	string name;
	string type;
	Client* client;
	double cost;
	Date deadline;
	vector<Task*> tasks; //vector de tarefas;
	vector<Collaborator*> collaborators; //vector de colaboradores;
public:
	 
	
	Project();
	Project(string name, string type, Date deadline, double cost );
	Project(string name, string type, Date deadline, double cost, int setID);
	Project(int i);
	/// converter projeto em string
	/// @return string correspondente ao projeto
	string toString() const;
	int getID() const;
	static int getLastID();
	string getName() const;
	string getType() const ;
	Client* getClient()const;
	double getCost() const;
	Date getDeadline()const;
	void setDeadline(const Date& d);
	/// compara a data atual com o prazo do projeto
	/// @param  data atual
	/// @return verdadeiro se a data passada como argumento for posterior ao prazo do projeto
	bool isPastDeadline(const Date& currentdate);

	/// calcula o numero de semanas necessarias para terminar o projeto
	/// @return numero de semanas ate o projeto estar concluido, ou -1 se alguma tarefa nao estiver a ser trabalhada
	double weeksToFinish() const;

	/// data estimada de conclusao do projeto
	/// @param data atual
	/// @return data de conclusao do projeto
	Date projectedFinishDate(const Date& currentdate) const;
	vector<Task*> getTasks() const;
	vector<Collaborator*> getCollaborators() const;
	void setID(int ID);
	static void setLastID(int lID) ;
	bool setClient(Client* c, bool addProject = true);
	void setName(string newname);
	void setType(string newtype);

	/// adiciona colaborador
	/// @throw	colaborador nao existe
	/// @param  apontador para colaborador a ser adicionado
	/// @param  bool que indica se o projeto deve ser adicionado ao colaborador
	/// @return indica o sucesso da operacao
	bool addCollaborator(Collaborator* c, bool addProject = true);


	/// adiciona tarefa, atualizando a lista de colaboradores do projeto
	/// @throw	tarefa nao existe
	/// @param  apontador para colaborador a ser adicionado
	/// @param  bool que indica se o projeto deve ser adicionado a tarefa
	/// @return indica o sucesso da operacao
	bool addTask(Task * t, bool setProject = true);


	/// simulacao de uma semana de trabalho do projeto, atualizando o custo do projeto
	/// @return indica o sucesso da operacao
	bool tick();

	/// projeto esta concluido se todas as suas tarefas estiverem concluidas
	/// @return estado do projeto
	bool isCompleted(); 

	/// na leitura do objeto, todos os apontadores sao inicializados com o ID do objecto que devem referenciar durante o funcionamento do sistema
	/// substitui os iDs pelos apontadores para os objetos correspondentes
	/// @throw objeto cujo ID esta num dos apontadores do objeto nao existe na aplicacao
	void connect();


	/// remove tarefa
	/// @throw	tarefa nao existe
	/// @param  apontador para tarefa a ser removida
	/// @param  bool que indica se o projeto deve ser removido  da tarefa
	/// @return indica o sucesso da operacao
	bool removeTask(Task* t, bool removeProject = true);

	/// remove referencias de todos os outros objetos a tarefa
	/// @throw	tarefa nao existe
	/// @return indica o sucesso da operacao
	bool removeTrace();

	/// remove cliente
	/// @param  bool que indica se o projeto deve ser removido  do cliente
	/// @return indica o sucesso da operacao
	bool removeClient(bool removeProject = true);

	/// remove colaborador
	/// @throw	colaborador nao existe
	/// @param  apontador para colaborador a ser removido
	/// @param  bool que indica se o projeto deve ser removido do colaborador
	/// @return indica o sucesso da operacao
	bool removeCollaborator(Collaborator* c, bool removeProject = true);

	/// igualdade entre projetos se tiverem IDs iguais
	/// @return igualdade dos projetos
	bool operator==(const Project& p2) const;

	/// escrita de todos os dados do projeto, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param  stream de saida
	/// @param  projeto a ser escrito
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Project& p);


	/// leitura de todos os dados do projeto, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param  stream de entrada
	/// @param  projeto a ser lido
	/// @return stream de entreada
	friend istream & operator>>(istream& in, Project& p);

	/// atualizacao da lista de colaboradores que trabalham na tarefa
	void updateCollaborators();
private:
	/// calculo da lista de colaboradores que trabalham na tarefa
		vector<Collaborator*> calculateCollaborators()const;
public:
		///class de excepção associada a Projectos
		class ProjectExcept
		{
			string description;
		public:
			ProjectExcept(string description);
			string operator()();
		};
		///interface de comparacao de projetos
		class ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			virtual bool operator()(const Project& t1, const Project& t2) = 0;
			///comparacao entre objetos da classe
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			virtual bool operator()(const Project* t1, const Project* t2) = 0;
			///comparacao entre apontadores para objetos da classe
			///@param apontador para objeto 1
			///@param apontador para objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			virtual string getAbbreviation() const = 0;
		};
		///class de comparação para ordenar os projectos de forma alfabetica
		class ProjectComparatorAlphabetic : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação para ordenar os projectos em função do custo
		class ProjectComparatorCost : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação para ordenar os projectos por ID
		class ProjectComparatorID : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação que servirá para ordenar os projectos por numero de tarefas
		class ProjectComparatorNumTasks : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação que servirá para ordenar os projectos por numero de colaboradores
		class ProjectComparatorNumCollaborators : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação que servirá para ordenar os projectos por tipo
		class ProjectComparatorType : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação que servirá para ordenar os projectos por prazo
		class ProjectComparatorDeadline : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
		///class de comparação que servirá para ordenar os projectos por data estimada de terminacao do projecto
		class ProjectComparatorTimeToFinish : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2);
			bool operator()(const Project* t1, const Project* t2);
			string getAbbreviation() const;
		};
};
#endif
