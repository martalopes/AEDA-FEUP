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
	
	Client():ID(0){};
	Client(string name):name(name),ID(++lastID){};
	Client(string name, int setID) :name(name), ID(setID) { if (setID > lastID) lastID = setID; };
	Client(int i)
	{
		stringstream s1, s2;
		s1 << "Name " << i;
		*this = Client(s1.str());
	};
	string getName() const { return this->name; };
	string toString() const;
	vector<Project*> getProjects() const { return this->projects; };
	int getID()const {return ID;};
	void setName(string name) { this->name = name; };
	bool addProject(Project* proj, bool setClient = true);
	void connect();
	bool removeProject(Project* p, bool removeClient = true);
	double getTotal() const;
	bool operator==(const Client& c2) const { return this->ID == c2.ID; };
	friend ostream & operator<<(ostream& out, const Client& p);
	friend istream & operator>>(istream& in, Client& c);
	//class de excepção associada a Clientes
	class ClientExcept
	{
		string description;
	public:
		ClientExcept(string description) :description(description){};
		string operator()(){ return description; };
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
		bool operator()(const Client& c1, const Client& c2){ return c1.getID() < c2.getID(); };
		bool operator()(const Client* c1, const Client* c2){ return c1->getID() < c2->getID(); };
		string getAbbreviation() const { return "ID"; };
	};
	class ClientComparatorAlphabetic : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2){ return c1.getName() < c2.getName(); };
		bool operator()(const Client* c1, const Client* c2){ return c1->getName() < c2->getName(); };
		string getAbbreviation() const { return "Alph"; };
	};
	class ClientComparatorNumProjects : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2){ return c1.getProjects().size() < c2.getProjects().size(); };
		bool operator()(const Client* c1, const Client* c2){ return c1->getProjects().size() < c2->getProjects().size(); };
		string getAbbreviation() const { return "N Proj"; };
	};
	class ClientComparatorTotal : public ClientComparator
	{
	public:
		bool operator()(const Client& c1, const Client& c2){ return c1.getTotal() < c2.getTotal(); };
		bool operator()(const Client* c1, const Client* c2){ return c1->getTotal() < c2->getTotal(); };
		string getAbbreviation() const { return "Total"; };
	};

};

#endif
