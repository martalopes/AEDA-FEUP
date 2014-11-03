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

#define PROGRAMMER_COST 35.71
#define ARCHITECT_COST 44.88
#define MANAGER_COST 40.54
#define TESTER_COST 25.89

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
	int ID;
	string name;
	int maxweeklyhours;// numero de horas de trabalho por semana;
	int workinghours;// numero total de horas de trabalho;
	vector<Project*> projects;
	vector<pair<Task*, unsigned int> > tasks;
	vector<Task*> finishedtasks;
	string password;
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
		virtual bool operator()(const Collaborator& t1, const Collaborator& t2) = 0;
	};
	class CollaboratorComparatorAlphabetic : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.name < t2.name; };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->name < t2->name; };
	};
	class CollaboratorComparatorCost : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.workinghours < t2.workinghours; };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->workinghours < t2->workinghours; };
	};
	class CollaboratorComparatorID : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getID() < t2.getID(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getID() < t2->getID(); };
	};
	class CollaboratorComparatorWorkinghours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getWorkingHours() < t2.getWorkingHours(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getWorkingHours() < t2->getWorkingHours(); };
	};
	class CollaboratorComparatorMaxWeeklyHours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getMaxWeeklyHours() < t2.getMaxWeeklyHours(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getMaxWeeklyHours() < t2->getMaxWeeklyHours(); };
	};
	class CollaboratorComparatorNumTasks : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getTasks().size() < t2.getTasks().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getTasks().size() < t2->getTasks().size(); };
	};
	class CollaboratorComparatorExperience : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getFinishedTasks().size() < t2.getFinishedTasks().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getFinishedTasks().size() < t2->getFinishedTasks().size(); };
	};
	class CollaboratorComparatorNumProjects : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getProjects().size() < t2.getProjects().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getProjects().size() < t2->getProjects().size(); };
	};
	Collaborator() :ID(0), maxweeklyhours(0), workinghours(0), password("123"){};
	Collaborator(string name, int weeklyhours) : name(name), maxweeklyhours(weeklyhours), ID(++lastID), workinghours(0), password("123"){};
	Collaborator(string name, int weeklyhours, int setID) : name(name), maxweeklyhours(weeklyhours), workinghours(0), password("123"){ if (setID > lastID) lastID = setID; };
	Collaborator(int i)
	{
		stringstream s;
		s << "Collaborator " << i;
		*this = Collaborator(s.str(), (6 + rand() % 4) * 5);
	};
	bool verifyPassword(const string& password) const{ return this->password == password; };
	//static int numCollaborators(){ return Collaborator::lastID; };
	int getID() const { return this->ID; };
	string getName() const { return this->name; };
	int getWorkingHours() const { return  this->workinghours; };
	int getMaxWeeklyHours() const { return this->maxweeklyhours; };
	vector<Project*> getProjects() const { return this->projects; };
	vector<pair<Task*, unsigned int> > getTasks() const { return this->tasks; };
	vector<Task*> getFinishedTasks() const { return this->finishedtasks; };
	bool reassign(Task* t);
	virtual float getCost() const{ return 0; };
	virtual string getTitle() const{ return "Collaborator"; };
	void setID(int newID) { lastID = newID; };
	void setName(string newname){ this->name = newname; };
	void setWeeklyHours(int newhours) { this->maxweeklyhours = newhours; };
	bool addTask(Task* t1, unsigned int hours, bool addCollaborator=true);
	bool removeTask(Task* t, bool removeCollaborator = true);
	bool removeProject(Project* p, bool removeCollaborator = true);
	bool removeTrace();
	bool changeTaskHours(Task* t1, unsigned int hours);
	bool addProject(Project* p, bool addCollaborator = true);
	static Collaborator* newRandomCollaborator(int i);
	static Collaborator* newCollaboratorTitle(string title);
	void connect();
	bool operator==(const Collaborator& c2)const{ return this->ID == c2.ID; };
	friend ostream & operator<<(ostream& out, const Collaborator& c);
	friend istream & operator>>(istream& in, Collaborator& c);

};

class Programmer : public Collaborator
{
public:

	Programmer(string name, int dailyhours): Collaborator(name, dailyhours){};
	Programmer(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Programmer(int i): Collaborator(i){};
	Programmer() : Collaborator(){};
	float getCost() const { return PROGRAMMER_COST; };
	string getTitle() const{ return "Programmer"; };
private:

};
class Architect : public Collaborator
{
public:
	Architect(string name, int dailyhours): Collaborator(name, dailyhours){};
	Architect(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Architect(int i): Collaborator(i){};
	Architect(): Collaborator(){};
	float getCost() const { return ARCHITECT_COST; };
	string getTitle() const{ return "Architect"; };
private:

};
class Manager : public Collaborator
{
public:
	Manager(string name, int dailyhours): Collaborator(name, dailyhours){};
	Manager(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Manager(int i): Collaborator(i){};
	Manager() : Collaborator(){};
	float getCost() const { return MANAGER_COST; };
	string getTitle() const{ return "Manager"; };
private:

};
class Tester : public Collaborator
{
public:
	Tester(string name, int dailyhours): Collaborator(name, dailyhours){};
	Tester(string name, int dailyhours, int setID): Collaborator(name, dailyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Tester(int i): Collaborator(i){};
	Tester() : Collaborator(){};
	float getCost() const { return TESTER_COST; };
	string getTitle() const{ return "Tester"; };
private:

};


#endif
