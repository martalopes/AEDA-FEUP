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
	///ID do cliente
	int ID;
	///Antigo ID do cliente
	static int lastID; 
	///numero de identificacao fiscal do cliente
	int fiscal;
	///nome do cliente
	string name;
	///projectos do cliente
	vector<Project*> projects;
public:
	///construtor por defeito
	Client();

	///@brief construtor sem ID especificado
	///@param name nome de Cliente
	Client(string name);

	///@brief construtor sem ID especificado, com informacao fiscal
	///@param name nome de Cliente
	///@param dados fiscais
	Client(int fiscal, string name);

	///@brief construtor com ID
	///@param name nome de Cliente
	///@param setID ID do Cliente
	Client(string name, int setID);

	///@brief client generico
	///@param i indice de Cliente	
	Client(int i);

	///@brief retorna o nome do cliente
	///@return nome do cliente
	string getName() const ;

	///@brief retorna string com o nome e ID do cliente
	///@return string com o nome e ID do cliente
	string toString() const;

	///@brief retorna projetos do cliente
	///@return projetos do cliente
	vector<Project*> getProjects() const;

	///@brief retorna ID do cliente
	///@return ID do cliente
	int getID()const;

	///@brief modificar o nome do cliente
	///@param name novo nome de Cliente
	void setName(string name);

	///@brief adicionar projeto a cliente
	///@throw projeto nao existe
	///@param proj projeto
	///@param setClient indica se o cliente deve ser associado ao projeto
	///@return sucesso da operacao
	bool addProject(Project* proj, bool setClient = true);

	///@brief substitui os IDs dos objetos pelos apontadores para os objetos
	///@throw objeto nao existe na aplicacao
	void connect();

	///@brief remover projeto de cliente
	///@throw projeto nao existe
	///@param p projeto a ser removido 
	///@param removeClient indica se o cliente deve ser removido ao projeto
	///@return sucesso da operacao
	bool removeProject(Project* p, bool removeClient = true);

	///@brief retorna custo total de todos os projetos do cliente
	///@return custo total de todos os projetos do cliente
	double getTotal() const;

	///@brief retorna informacao fiscal do cliente
	///@return informacao fiscal do cliente
	int getFiscal()const;

	///@brief modificar informacao fiscal do cliente
	///@param newfiscal nova informacao fiscal
	void setFiscal(int newfiscal);

	///@brief dois clientes sao iguais se os seus IDs forem iguais
	///@param c2 cliente a ser comparado
	///@return verdadeiro se sao iguais
	bool operator==(const Client& c2) const;

	///@brief operador menor associado a ordenacao de clientes que é baseada no montante acumulado
	///@brief clientes com o mesmo valor pago sao diferenciados pelo numero de projectos
	///@brief clientes com o mesmo numero de projectos e com o mesmo valor pago sao diferenciados pelo ID de cada um
	///@param c2 cliente a ser comparado
	///@return verdadeiro se sao iguais
	bool operator < (const Client& c2) const;

	///@brief escrita de todos os dados do cliente, no lugar dos apontadores sao escritos os IDs dos objetos
	///@param out stream de saida
	///@param c cliente a ser escrito
	///@return stream de saida
	friend ostream & operator<<(ostream& out, const Client& c);

	///@brief leitura de todos os dados do cliente, no lugar dos apontadores sao lidos os IDs dos objetos
	///@param in stream de entrada
	///@param c cliente a ser lido
	///@return stream de entreada
	friend istream & operator>>(istream& in, Client& c);

	///class de excepcao associada a Clientes
	class ClientExcept
	{
		string description;
	public:
		///@brief construtor da classe
		///@param description descrição
		ClientExcept(string description);
		///retorna descricao da excepcao
		///@return descricao da excepcao
		string operator()();
	};
	///interface de comparadores para clientes
	class ClientComparator
	{
	public:
		///@brief comparacao entre clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		virtual bool operator()(const Client& c1, const Client& c2) = 0;
		///@brief comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		virtual bool operator()(const Client* c1, const Client* c2) = 0;
		///@brief retorna string que contem uma abreviacao do nome do comparador
		///@return string que contem uma abreviacao do nome do comparador
		virtual string getAbbreviation() const=0;
	};
	///comparacao de clientes por ID
	class ClientComparatorID: public ClientComparator
	{
	public:
		///@brief comparacao entre clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///@brief comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@brief retorna string que contem uma abreviacao do nome do comparador
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por ordem alfabetica
	class ClientComparatorAlphabetic : public ClientComparator
	{
	public:
		///@brief comparacao entre clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///@brief comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@brief retorna string que contem uma abreviacao do nome do comparador
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por numero de projetos
	class ClientComparatorNumProjects : public ClientComparator
	{
	public:
		///@brief comparacao entre clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///@brief comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@brief rertorna string que contem uma abreviacao do nome do comparador
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	///comparacao de clientes por custo total
	class ClientComparatorTotal : public ClientComparator
	{
	public:
		///@brief comparacao entre clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client& c1, const Client& c2);
		///@brief comparacao entre apontadores para clientes
		///@param c1 objecto1
		///@param c2 objecto2
		///@return c1 < c2
		bool operator()(const Client* c1, const Client* c2);
		///@brief retorna string que contem uma abreviacao do nome do comparador
		///@return string que contem uma abreviacao do nome do comparador
		string getAbbreviation() const;
	};
	friend class ClientPtr;
};


#endif
