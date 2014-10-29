#ifndef COLLABORATOR_H
#define COLLABORATOR_H



#include "Client.h"
#include "Project.h"
#include "Date.h"
#include "Application.h"
//#include "Task.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

#define PROGRAMMER_COST 1
#define ARCHITECT_COST 2
#define MANAGER_COST 3
#define TESTER_COST 4

class Task;
class Project;
class Programmer;
class Architect;
class Manager;
class Testers;

class Collaborator
{
protected:
	static int lastID;
private:
	string name;
	int ID;
	int maxweeklyhours;// numero de horas de trabalho por semana;
	int workinghours;// numero total de horas de trabalho;
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
	class CollaboratorComparator
	{
	public:
		virtual bool operator()(const Collaborator& t1, const Collaborator& t2)=0;
	};
	class CollaboratorComparatorAlphabetic : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.name < t2.name; };
	};
	class CollaboratorComparatorCost : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.workinghours < t2.workinghours; };
	};
	class CollaboratorComparatorID : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getID() < t2.getID(); };
	};
	
	Collaborator(string name, int dailyhours) : name(name), maxweeklyhours(dailyhours),ID(++lastID),workinghours(0)	{};
	Collaborator(string name, int dailyhours, int setID) : name(name), maxweeklyhours(dailyhours), workinghours(0){ if (setID > lastID) lastID = setID; };
	Collaborator(int i)
	{
		stringstream s;
		s << "Collaborator " << i;
		*this = Collaborator(s.str(), (6 + rand() % 4)*5);
	};
	static Collaborator* newCollaborator(int i);
	friend ostream & operator<<(ostream& out, const Collaborator& c);
	//static int numCollaborators(){ return Collaborator::lastID; };
	int getID() const { return this->ID; };
	void setID(int newID) { lastID = newID; };
	string getName() const { return this->name; };
	int getWorkingHours() const { return  this->workinghours; };
	int getMaxWeeklyHours() const { return this->maxweeklyhours; };
	vector<Project*> getProjects() const { return this->projects; };
	vector<pair<Task*, unsigned int> > getTasks() const { return this->tasks; };
	void setName(string newname){ this->name = newname; };
	void setWeeklyHours(int newhours) { this->maxweeklyhours = newhours; };
	virtual float getCost() const{ return 0; };
	bool operator==(const Collaborator& c2){return this->ID == c2.ID;};
	bool addTask(Task* t1, unsigned int hours, bool addCollaborator=true);
	bool changeTaskHours(Task* t1, unsigned int hours)
	{
		for (size_t i = 0; i < this->tasks.size(); ++i)
		{
			if (tasks[i].first == t1)
			{
				if (workinghours - tasks[i].second + hours > maxweeklyhours)
					return false;
				else tasks[i].second = hours;
				workinghours = workinghours - tasks[i].second + hours;
			}
		}
		return false;
	};
	bool removeTask(Task* t, bool removeCollaborator = true);

};

class Programmer : public Collaborator
{
public:
	float getCost() const { return PROGRAMMER_COST; };
	Programmer(string name, int dailyhours): Collaborator(name, dailyhours){};
	Programmer(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Programmer(int i): Collaborator(i){};
private:

};
class Architect : public Collaborator
{
public:
	Architect(string name, int dailyhours): Collaborator(name, dailyhours){};
	Architect(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Architect(int i): Collaborator(i){};
	float getCost() const { return ARCHITECT_COST; };
private:

};
class Manager : public Collaborator
{
public:
	Manager(string name, int dailyhours): Collaborator(name, dailyhours){};
	Manager(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Manager(int i): Collaborator(i){};
	float getCost() const { return MANAGER_COST; };
private:

};
class Testers : public Collaborator
{
public:
	Testers(string name, int dailyhours): Collaborator(name, dailyhours){};
	Testers(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Testers(int i): Collaborator(i){};
	float getCost() const { return TESTER_COST; };
private:

};
static Collaborator* newCollaborator(int i)
{
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		return new Programmer(i);
		break;
	case 1:
		return new Architect(i);
		break;
	case 2:
		return new Manager(i);
		break;
	case 3:
		return new Testers(i);
		break;
	default:
		break;
	}
}

#endif
