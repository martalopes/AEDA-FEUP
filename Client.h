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
Cada Cliente é composto/identificado:
por nome,
para facilitar a identificação do projecto será atribuido um ID a cada um,
tem um conjunto de projectos a que está associado.
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
	
	Client();
	Client(string name);
	Client(string name, int setID);
	Client(int i);

	string getName() const ;
	string toString() const;
	vector<Project*> getProjects() const;
	int getID()const;
	void setName(string name);
	bool addProject(Project* proj, bool setClient = true);
	void connect();
	bool removeProject(Project* p, bool removeClient = true);
	double getTotal() const;
	bool operator==(const Client& c2) const;
	friend ostream & operator<<(ostream& out, const Client& p);
	friend istream & operator>>(istream& in, Client& c);
	//class de excepção associada a Clientes
	class ClientExcept
	{
		string description;
	public:
		ClientExcept(string description);
		string operator()();
	};
	class ClientComparator
	{
	public:
		virtual bool operator()(const Client& c1, const Client& c2) = 0;
		virtual bool operator()(const Client* c1, const Client* c2) = 0;
		virtual string getAbbreviation() const=0;
	};
	class ClientComparatorID: public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2);
		bool operator()(const Client* c1, const Client* c2);
		string getAbbreviation() const;
	};
	class ClientComparatorAlphabetic : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2);
		bool operator()(const Client* c1, const Client* c2);
		string getAbbreviation() const;
	};
	class ClientComparatorNumProjects : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2);
		bool operator()(const Client* c1, const Client* c2);
		string getAbbreviation() const;
	};
	class ClientComparatorTotal : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2);
		bool operator()(const Client* c1, const Client* c2);
		string getAbbreviation() const;
	};

};

#endif
