#ifndef COLLABORATOR_H
#define COLLABORATOR_H



#include "Client.h"
#include "Project.h"
#include "Date.h"



#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

#define PROGRAMMER_COST 1
#define ARCHITECT_COST 2
#define MANAGER_COST 3
#define TESTER_COST 4

class Vazia;
class Project;
class Task;

class Collaborator
{
private:
	static int lastID;
	string name;
	int ID;
	int maxdailyhours;
	int workinghours;
	vector<Project*> projects;
	vector<pair<Task*, unsigned int> > tasks;
public:
	class CollaboratorExcept
	{
		string description;
	public:
		CollaboratorExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	Collaborator(string name, int weeklyhours) : name(name), maxdailyhours(weeklyhours){ ++Collaborator::lastID; this->ID = Collaborator::lastID; };
	//static int numCollaborators(){ return Collaborator::lastID; };
	int getID() const{ return this->ID; };
	void setID(int newID) { lastID = newID; };
	string getName() const { return this->name; };
	int getWorkingHours() const { return  this->workinghours; };
	int getMaxWeeklyHours() const { return this->maxdailyhours; };
	int getWorkinghours() const{ return this->workinghours; };
	vector<Project*> getProjects() const { return this->projects; };
	vector<pair<Task*, unsigned int> > getTasks() const { return this->tasks; };
	void setName(string newname){ this->name = newname; };
	void setWeeklyHours(int newhours) { this->maxdailyhours = newhours; };
	virtual float getCost() const;
	bool addTask(Task* t1, unsigned int hours) 
	{
		for (size_t i = 0; i < this->tasks.size(); ++i)
		{
			if (tasks[i].first == t1)
			{
				throw CollaboratorExcept("Task already exists");
			}
		}
		if (this->getWorkingHours() + hours > this->maxdailyhours)
			return false;
		tasks.push_back(make_pair(t1, hours));
		workinghours += hours;
		return true;		
	};
	bool changeTaskHours(Task* t1, unsigned int hours)
	{
		for (size_t i = 0; i < this->tasks.size(); ++i)
		{
			if (tasks[i].first == t1)
			{
				if (workinghours - tasks[i].second + hours >maxdailyhours)
					return false;
				else tasks[i].second = hours;
				workinghours = workinghours - tasks[i].second + hours;
			}
		}
		return false;
	};
	bool removeTask(const Task* t)
	{ 
		if (t == NULL)
			throw CollaboratorExcept("Invalid task");
		for (size_t i = 0; i < tasks.size(); ++i)
		if (tasks.at(i).first == t)
		{
			workinghours -= tasks.at(i).second;
			tasks.erase(tasks.begin() + i);
			return true;
		}
		return false;
	};
	static double averageCost()
	{
		vector<Collaborator*> v;
		return -1;
	}
};

class Programmer : public Collaborator
{
public:
	float getCost() const { return PROGRAMMER_COST; };
private:

};
class Architect : public Collaborator
{
public:
	float getCost() const { return ARCHITECT_COST; };
private:

};
class Manager : public Collaborator
{
public:
	float getCost() const { return MANAGER_COST; };
private:

};
class Testers : public Collaborator
{
public:
	float getCost() const { return TESTER_COST; };
private:

};


#endif
