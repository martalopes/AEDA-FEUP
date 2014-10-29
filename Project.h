#ifndef PROJECT_H
#define PROJECT_H


#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"
#include "Application.h"

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
	int cost;
	Date deadline;
	vector<Task*> tasks;
	vector<Collaborator*> collaborators;
public:
	class ProjectExcept
	{
		string description;
	public:
		ProjectExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	class ProjectComparator
	{
	public:
		virtual bool operator()(const Project& t1, const Project& t2)=0;
	};
	class ProjectComparatorAlphabetic : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.name < t2.name; };
	};
	class ProjectComparatorCost : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.cost < t2.cost; };
	};
	class ProjectComparatorID : public ProjectComparator
	{
	public:
		bool operator()(const Project& t1, const Project& t2) { return t1.getID() < t2.getID(); };
	};
	Project(string name, string type, Date deadline ) : deadline(deadline), name(name), type(type), ID(++lastID), cost(0){};
	Project(string name, string type, Date deadline, int setID) :  name(name), type(type), ID(++lastID),deadline(deadline), cost(0){ if (setID > lastID) lastID = setID; };
	Project(int i);
	friend ostream & operator<<(ostream& out, const Project& p);
	friend istream & operator>>(istream& in,Project& p);
	int getID() const		{ return this->ID; };
	static int getLastID()  { return lastID; };
	string getName() const	{ return this->name; };
	string getType() const  { return this->type; };
	Client* getClient()	{ return this->client; };
	int getCost() const	{ return this->cost; };
	vector<Task*> getTasks() const { return this->tasks; };
	vector<Collaborator*> getCollaborators() const { return this->collaborators; };
	void setID(int ID) { this->ID = ID; };
	static void setLastID(int lID) { lastID = lID; };
	bool operator==(const Project& p2) const { return (this->ID) == (p2.ID); };
	void setClient(Client* c, bool addProject = true);
	void setName(string newname){ name = newname; };
	void setType(string newtype){ type = newtype; };
	Date getDeadline()const {return deadline;};
	bool tick();
	bool isCompleted();
	void addTask(Task * t, bool setProject = true);

};
#endif
