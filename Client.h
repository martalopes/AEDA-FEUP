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
	int fiscal;
	string name;
	vector<Project*> projects;
public:
	///construtor por defeito
	Client();

	///construtor sem ID especificado
	///@param name nome de Cliente
	Client(string name);

	///construtor sem ID especificado, com informacao fiscal
	///@param name nome de Cliente
	///@param dados fiscais
	Client(int fiscal, string name);

	///construtor com ID
	///@param name nome de Cliente
	///@param setID ID do Cliente
	Client(string name, int setID);

	///client generico
	///@param i indice de Cliente	
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
	///@param name novo nome de Cliente
	void setName(string name);

	///adicionar projeto a colaborador
	///@throw projeto nao existe
	///@param proj projeto
	///@param setClient indica se o cliente deve ser associado ao projeto
	///@return sucesso da operacao
	bool addProject(Project* proj, bool setClient = true);

	///substitui os IDs dos objetos pelos apontadores para os objetos
	///@throw objeto nao existe na aplicacao
	void connect();

	///remover projeto de colaborador
	///@throw projeto nao existe
	///@param p projeto
	///@param removeClient indica se o cliente deve ser removido ao projeto
	///@return sucesso da operacao
	bool removeProject(Project* p, bool removeClient = true);

	///@return custo total de todos os projetos do cliente
	double getTotal() const;

	///@return informacao fiscal do cliente
	int getFiscal()const;

	///modificar informacao fiscal do cliente
	///@param newfiscal nova informacao fiscal
	void setFiscal(int newfiscal);

	///dois clientes sao iguais se os seus IDs forem iguais
	///@param c2 cliente a ser comparado
	///@return verdadeiro se sao iguais
	bool operator==(const Client& c2) const;

	bool operator < (const Client& c2) const;

	/// escrita de todos os dados do client, no lugar dos apontadores sao escritos os IDs dos objetos
	/// @param out stream de saida
	/// @param c cliente a ser escrito
	/// @return stream de saida
	friend ostream & operator<<(ostream& out, const Client& c);

	/// leitura de todos os dados do cliente, no lugar dos apontadores sao lidos os IDs dos objetos
	/// @param in stream de entrada
	/// @param c cliente a ser lido
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
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		virtual bool operator()(const Client& c1, const Client& c2) = 0;
		///comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
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
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
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
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
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
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
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
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	friend class ClientPtr;
};


#endif
