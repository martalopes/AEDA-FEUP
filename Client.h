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
	Client(string name):name(name),ID(++lastID){};
	Client(string name, int setID) :name(name), ID(ID) { if (setID > lastID) lastID = setID; };
	string getName() const { return this->name; };
	vector<Project*> getProjects() const { return this->projects; };
	string setName(string name) { this->name = name; };
	bool addProject(Project* proj){ projects.push_back(proj); };
	bool operator==(const Client& c2) const { return this->ID == c2.ID; };

};

#endif