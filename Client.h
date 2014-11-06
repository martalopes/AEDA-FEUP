#ifndef CLIENT_H
#define CLIENT_H

#include "Project.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <string>
#include <utility>
#include <vector>

/*
Project Client:
Cada Cliente e composto/identificado:
por nome,
para facilitar a identificacao do projecto sera atribuido um ID a cada um,
tem um conjunto de projectos a que esta associado.
*/


using namespace std;

class Project;

class Client
{
private:
	int ID;
	static int lastID; 
	string name;
	vector<Project*> projects;
public:
	///construtor por defeito
	Client();
	///construtor sem ID especidficado
	Client(string name);
	///construtor com ID
	Client(string name, int setID);
	///client generico
	Client(int i);
	///@return nome do client
	string getName() const ;
	///@return string com o nome e ID do cliente
	string toString() const;
	///@return projetos do cliente
	vector<Project*> getProjects() const;
	///@return ID do cliente
	int getID()const;
	///modificar o nome do cliente
	void setName(string name);
	///adicionar projeto a colaborador
	///@throw projeto nao existe
	///@param projeto
	///@param indica se o cliente deve ser associado ao projeto
	///@return sucesso da operacao
	bool addProject(Project* proj, bool setClient = true);
	///substitui os IDs dos objetos pelos apontadores para os objetos
	///@throw objeto nao existe na aplicacao
	void connect();

	///remover projeto de colaborador
	///@throw projeto nao existe
	///@param projeto
	///@param indica se o cliente deve ser removido ao projeto
	///@return sucesso da operacao
	bool removeProject(Project* p, bool removeClient = true);

	///@return custo total de todos os projetos do cliente
	double getTotal() const;
	///dois clientes sao iguais se os seus IDs forem iguais
	///@return verdadeiro se sao iguais
	bool operator==(const Client& c2) const;

	/// escrita de todos os dados do client, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param  stream de saida
	/// @param  client a ser escrito
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Client& p);

	/// leitura de todos os dados do cliente, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param  stream de entrada
	/// @param  cliente a ser lido
	/// @return stream de entreada
	friend istream & operator>>(istream& in, Client& c);

	///class de excepcao associada a Clientes
	class ClientExcept
	{
		string description;
	public:
		ClientExcept(string description);
		///@return descricao da excepcao
		string operator()();
	};
	///interface de comparadores para clientes
	class ClientComparator
	{
	public:
		///comparacao entre clientes
		///@return c1 < c2
		virtual bool operator()(const Client& c1, const Client& c2) = 0;
		///comparacao entre apontadores para clientes
		///@return c1 < c2
		virtual bool operator()(const Client* c1, const Client* c2) = 0;
		///@return string que contem uma abreviacao do nome do comparador
		virtual string getAbbreviation() const=0;
	};
	///comparacao de clientes por ID
	class ClientComparatorID: public ClientComparator
	{
	public:
		///comparacao entre clientes
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por ordem alfabetica
	class ClientComparatorAlphabetic : public ClientComparator
	{
	public:
		///comparacao entre clientes
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por numero de projetos
	class ClientComparatorNumProjects : public ClientComparator
	{
	public:
		///comparacao entre clientes
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por custo total
	class ClientComparatorTotal : public ClientComparator
	{
	public:
		///comparacao entre clientes
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};

};

#endif
