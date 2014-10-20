#ifndef CLIENT_H
#define CLIENT_H

#include "Project.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"

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
	string getName() const { return this->name; };
	vector<Project*> getProjects() const { return this->projects; };
	int getID()const {return ID;};
	string setName(string name) { this->name = name; };
	bool addProject(Project* proj)
	{
		for(size_t i = 0; i< projects.size(); ++i)
			if(*projects.at(i) == *proj)
				throw ClientExcept("Project already exists");
		projects.push_back(proj);
	};
	bool operator==(const Client& c2) const { return this->ID == c2.ID; };

};

#endif
