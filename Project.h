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
	 
	///construtor por defeito
	Project();
	///construtor sem ID especificado
<<<<<<< HEAD
	///@param name nome do projecto
	///@param type tipo de projecto
	///@param deadline prazo do projecto
	///@param cost custo do projecto
	Project(string name, string type, Date deadline, double cost );
	///construtor com ID especificado
	///@param name nome do projecto
	///@param type tipo de projecto
	///@param deadline prazo do projecto
	///@param cost custo do projecto
	///@param setID ID do projecto
	Project(string name, string type, Date deadline, double cost, int setID);
	///projeto generico
	///@param i indice do projecto
=======
	Project(string name, string type, Date deadline, double cost );
	///construtor com ID especificado
	Project(string name, string type, Date deadline, double cost, int setID);
	///projeto generico
>>>>>>> origin/master
	Project(int i);

	/// converter projeto em string
	/// @return string correspondente ao projeto
	string toString() const;

	///@return ID do projeto
	int getID() const;

	///@return ultimo ID a ser utilizado
	static int getLastID();

	///@return nome do projeto
	string getName() const;

	///@return tipo do projeto
	string getType() const ;

	///@return cliente associado ao projeto
	Client* getClient()const;

	///@return custo do projeto
	double getCost() const;

	///@return data do prazo do projeto
	Date getDeadline()const;

	///modifica o prazo do projeto
<<<<<<< HEAD
	///@param d novo prazo do projeto
=======
	///@param novo prazo do projeto
>>>>>>> origin/master
	void setDeadline(const Date& d);

	/// compara a data atual com o prazo do projeto
	/// @param currentdate data atual
	/// @return verdadeiro se a data passada como argumento for posterior ao prazo do projeto
	bool isPastDeadline(const Date& currentdate);

	/// calcula o numero de semanas necessarias para terminar o projeto
	/// @return numero de semanas ate o projeto estar concluido, ou -1 se alguma tarefa nao estiver a ser trabalhada
	double weeksToFinish() const;

	/// data estimada de conclusao do projeto
	/// @param currentdate data atual
	/// @return data de conclusao do projeto
	Date projectedFinishDate(const Date& currentdate) const;

	///@return taredas do projeto
	vector<Task*> getTasks() const;

	///@return colaboradores do projeto
	vector<Collaborator*> getCollaborators() const;

	/// modifica ID do projeto
<<<<<<< HEAD
	/// @param ID novo ID
	void setID(int ID);
	///modifica o ultimo ID a ser utilizado da classe projeto
	///@param lID ultimo ID 
	static void setLastID(int lID);

	///associa cliente a projeto
	///@param c cliente a ser associado
	///@param addProject indica se o projeto deve ser adicionado ao cliente
=======
	/// @param novo ID
	void setID(int ID);
	///modifica o ultimo ID a ser utilizado da classe projeto
	static void setLastID(int lID);

	///associa cliente a projeto
	///@param cliente a ser associado
	///@param indica se o projeto deve ser adicionado ao cliente
>>>>>>> origin/master
	///@throw cliente nao existre
	///@return sucesso da operacao
	bool setClient(Client* c, bool addProject = true);

	///modifica nome do projeto
	///@param novo nome
	void setName(string newname);

	///modifica tipo do projeto
	///@param novo tipo do projeto
	void setType(string newtype);

	/// adiciona colaborador
	/// @throw	colaborador nao existe
	/// @param c apontador para colaborador a ser adicionado
	/// @param addProject bool que indica se o projeto deve ser adicionado ao colaborador
	/// @return indica o sucesso da operacao
	//bool addCollaborator(Collaborator* c, bool addProject = true);


	/// adiciona tarefa, atualizando a lista de colaboradores do projeto
	/// @throw	tarefa nao existe
	/// @param t apontador para colaborador a ser adicionado
	/// @param setProject bool que indica se o projeto deve ser adicionado a tarefa
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
	/// @param t apontador para tarefa a ser removida
	/// @param removeProject bool que indica se o projeto deve ser removido  da tarefa
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
	/// @throw colaborador nao existe
	/// @param c apontador para colaborador a ser removido
	/// @param removeProject bool que indica se o projeto deve ser removido do colaborador
	/// @return indica o sucesso da operacao
	//bool removeCollaborator(Collaborator* c, bool removeProject = true);

	/// igualdade entre projetos se tiverem IDs iguais
	/// @param p2 projecto a ser comparado
	/// @return igualdade dos projetos
	bool operator==(const Project& p2) const;

	/// escrita de todos os dados do projeto, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param out stream de saida
	/// @param p projeto a ser escrito
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Project& p);


	/// leitura de todos os dados do projeto, no lugar dos apontadores sao lidos os IDs dos objetos
<<<<<<< HEAD
	/// @param in stream de entrada
	/// @param p projeto a ser lido
=======
	/// @param  stream de entrada
	/// @param  projeto a ser lido
>>>>>>> origin/master
	/// @return stream de entrada
	friend istream & operator>>(istream& in, Project& p);

	/// atualizacao da lista de colaboradores que trabalham na tarefa
	void updateCollaborators();
private:
	/// calculo da lista de colaboradores que trabalham na tarefa
		vector<Collaborator*> calculateCollaborators()const;
public:
		///class de excepcao associada a Projectos
		class ProjectExcept
		{
			string description;
		public:
			ProjectExcept(string description);
			///@return descricao da excecao
			string operator()();
		};
		///interface de comparacao de projetos
		class ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			virtual bool operator()(const Project& t1, const Project& t2) = 0;
			///comparacao entre apontadores para objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			virtual bool operator()(const Project* t1, const Project* t2) = 0;
			///@return abreviacao do comparador
			virtual string getAbbreviation() const = 0;
		};
		///class de comparacao para ordenar os projectos de forma alfabetica
		class ProjectComparatorAlphabetic : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao para ordenar os projectos em funcao do custo
		class ProjectComparatorCost : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao para ordenar os projectos por ID
		class ProjectComparatorID : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao que servira para ordenar os projectos por numero de tarefas
		class ProjectComparatorNumTasks : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao que servira para ordenar os projectos por numero de colaboradores
		class ProjectComparatorNumCollaborators : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao que servira para ordenar os projectos por tipo
		class ProjectComparatorType : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao que servira para ordenar os projectos por prazo
		class ProjectComparatorDeadline : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
		///class de comparacao que servira para ordenar os projectos por data estimada de terminacao do projecto
		class ProjectComparatorTimeToFinish : public ProjectComparator
		{
		public:
			///comparacao entre objetos da classe
<<<<<<< HEAD
			///@param t1 objeto 1
			///@param t2 objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param t1 objeto 1
			///@param t2 objeto 2
=======
			///@param objeto 1
			///@param objeto 2
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project& t1, const Project& t2);
			///comparacao entre apontadores para objetos da classe
			///@param objeto 1
			///@param objeto 2
>>>>>>> origin/master
			///@return verdadeiro se objeto 1 < objeto 2
			bool operator()(const Project* t1, const Project* t2);
			///@return abreviacao do comparador
			string getAbbreviation() const;
		};
};
#endif
