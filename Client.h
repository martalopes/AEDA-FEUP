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
	//class de excepção associada a Clientes
	class ClientExcept
	{
		string description;
	public:
		ClientExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	string getName() const { return this->name; };
	vector<Project*> getProjects() const { return this->projects; };
	int getID()const {return ID;};
	void setName(string name) { this->name = name; };
	void addProject(Project* proj, bool setClient = true);
	void connect();
	bool removeProject(Project* p, bool removeClient = true);
	double getTotal() const;
	bool operator==(const Client& c2) const { return this->ID == c2.ID; };
	friend ostream & operator<<(ostream& out, const Client& p);
	friend istream & operator>>(istream& in, Client& c);

};

#endif
