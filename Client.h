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
	class ClientExcept
		{
			string description;
		public:
			ClientExcept(string description) :description(description){};
			string operator()(){ return description; };
		};
	Client(string name):name(name),ID(++lastID){};
	Client(string name, int setID) :name(name), ID(setID) { if (setID > lastID) lastID = setID; };
	Client(int i)
	{
		stringstream s1, s2;
		s1 << "Name " << i;
		*this = Client(s1.str());
	};
	friend ostream & operator<<(ostream& out, const Client& p);
	friend istream & operator>>(istream& in, Client& c);
	void connect();
	string getName() const { return this->name; };
	vector<Project*> getProjects() const { return this->projects; };
	int getID()const {return ID;};
	void setName(string name) { this->name = name; };
	void addProject(Project* proj, bool setClient = true);
	bool operator==(const Client& c2) const { return this->ID == c2.ID; };

};

#endif
