#ifndef COLLABORATOR_H
#define COLLABORATOR_H



#include "Client.h"
#include "Project.h"
#include "Date.h"
#include "Application.h"

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
public:
	
	Collaborator();
	Collaborator(string name, int maxweeklyhours);
	Collaborator(string name, int maxweeklyhours, int setID);
	Collaborator(int i);

	int getID() const;
	string getName() const;
	int getWorkingHours() const;
	int getMaxWeeklyHours() const;
	vector<Project*> getProjects() const;
	vector<pair<Task*, unsigned int> > getTasks() const;
	vector<Task*> getFinishedTasks() const;
	bool reassign(Task* t);
	virtual double getCost()const;
	virtual string getTitle()const;
	string toString() const;
	void setID(int newID);
	void setName(string newname);
	void setWeeklyHours(int newhours);
	bool addTask(Task* t1, unsigned int hours, bool addCollaborator=true);
	bool removeTask(Task* t, bool removeCollaborator = true);
	bool removeProject(Project* p, bool removeCollaborator = true);
	bool removeTrace();
	bool changeTaskHours(Task* t1, unsigned int hours);
	bool addProject(Project* p, bool addCollaborator = true);
	static Collaborator* newRandomCollaborator(int i);
	static Collaborator* newCollaboratorTitle(string title);
	void connect();
	bool operator==(const Collaborator& c2)const;
	friend ostream & operator<<(ostream& out, const Collaborator& c);
	friend istream & operator>>(istream& in, Collaborator& c);
	void updateProjects();
	
	class CollaboratorExcept
	{
		string description;
	public:
		CollaboratorExcept(string description);
		string operator()();
	};
	class CollaboratorComparator
	{
	public:
		virtual bool operator()(const Collaborator& t1, const Collaborator& t2) = 0;
		virtual bool operator()(const Collaborator* t1, const Collaborator* t2) = 0;
		virtual string getAbbreviation() const = 0;
	};
	class CollaboratorComparatorAlphabetic : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) ;
		bool operator()(const Collaborator* t1, const Collaborator* t2) ;
		string getAbbreviation() const;
	};
	class CollaboratorComparatorCost : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.workinghours < t2.workinghours; };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->workinghours < t2->workinghours; };
		string getAbbreviation() const{ return "Cost"; };
	};
	class CollaboratorComparatorID : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getID() < t2.getID(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getID() < t2->getID(); };
		string getAbbreviation() const{ return "ID"; };
	};
	class CollaboratorComparatorWorkinghours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getWorkingHours() < t2.getWorkingHours(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getWorkingHours() < t2->getWorkingHours(); };
		string getAbbreviation() const{ return "Wrk Hrs"; };
	};
	class CollaboratorComparatorMaxWeeklyHours : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getMaxWeeklyHours() < t2.getMaxWeeklyHours(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getMaxWeeklyHours() < t2->getMaxWeeklyHours(); };
		string getAbbreviation() const{ return "Week Hrs"; };
	};
	class CollaboratorComparatorNumTasks : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getTasks().size() < t2.getTasks().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getTasks().size() < t2->getTasks().size(); };
		string getAbbreviation() const{ return "N. Tasks"; };
	};
	class CollaboratorComparatorExperience : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getFinishedTasks().size() < t2.getFinishedTasks().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getFinishedTasks().size() < t2->getFinishedTasks().size(); };
		string getAbbreviation() const{ return "Exp"; };
	};
	class CollaboratorComparatorNumProjects : public CollaboratorComparator
	{
	public:
		bool operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getProjects().size() < t2.getProjects().size(); };
		bool operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getProjects().size() < t2->getProjects().size(); };
		string getAbbreviation() const{ return "N. Proj"; };
	};
	private:
		vector<Project*> calculateProjects()const;

};

class Programmer : public Collaborator
{
public:

	Programmer(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){};
	Programmer(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Programmer(int i): Collaborator(i){};
	Programmer() : Collaborator(){};
	float getCost() const { return PROGRAMMER_COST; };
	string getTitle() const{ return "Programmer"; };
private:

};
class Architect : public Collaborator
{
public:
	Architect(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){};
	Architect(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Architect(int i): Collaborator(i){};
	Architect(): Collaborator(){};
	float getCost() const { return ARCHITECT_COST; };
	string getTitle() const{ return "Architect"; };
private:

};
class Manager : public Collaborator
{
public:
	Manager(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){};
	Manager(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Manager(int i): Collaborator(i){};
	Manager() : Collaborator(){};
	float getCost() const { return MANAGER_COST; };
	string getTitle() const{ return "Manager"; };
private:

};
class Tester : public Collaborator
{
public:
	Tester(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){};
	Tester(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; };
	Tester(int i): Collaborator(i){};
	Tester() : Collaborator(){};
	float getCost() const { return TESTER_COST; };
	string getTitle() const{ return "Tester"; };
private:

};


#endif
