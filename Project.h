#ifndef PROJECT_H
#define PROJECT_H


#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"
#include "Application.h"
#include "Menu.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
Project Class:
Cada projecto vai ser composto/identificado:
por nome,
por um tipo,
para facilitar a identificação do projecto será atribuido um ID a cada um,
tem um prazo associado,
é composto por tarefas,
colaboradores, pois cada projecto vai ser implementado por colaboradores diferentes.
tem um cliente associado.
*/

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
	double cost;
	Date deadline;
	vector<Task*> tasks; //vector de tarefas;
	vector<Collaborator*> collaborators; //vector de colaboradores;
public:
	 
	
	Project() : ID(0), client(NULL), cost(0) {};
	Project(string name, string type, Date deadline, double cost ) : deadline(deadline), name(name), type(type), ID(++lastID), cost(cost), client(NULL){};
	Project(string name, string type, Date deadline, double cost, int setID) : name(name), type(type), ID(++lastID), deadline(deadline), cost(cost),client(NULL){ if (setID > lastID) lastID = setID; };
	Project(int i);
	string toString() const;
	int getID() const		{ return this->ID; };
	static int getLastID()  { return lastID; };
	string getName() const	{ return this->name; };
	string getType() const  { return this->type; };
	Client* getClient()const{ return this->client; };
	double getCost() const	{ return this->cost; };
	Date getDeadline()const { return deadline; };
	void setDeadline(const Date& d){ deadline = d; };
	bool isPastDeadline(const Date& currentdate);
	double weeksToFinish() const;
	Date projectedFinishDate(const Date& currentdate) const;
	vector<Task*> getTasks() const { return this->tasks; };
	vector<Collaborator*> getCollaborators() const { return this->collaborators; };
	void setID(int ID) { this->ID = ID; };
	static void setLastID(int lID) { lastID = lID; };
	bool setClient(Client* c, bool addProject = true);
	void setName(string newname){ name = newname; };
	void setType(string newtype){ type = newtype; };
	bool addCollaborator(Collaborator* c, bool addProject = true); //função que adiciona colaboradores
	bool addTask(Task * t, bool setProject = true);//função que adiciona tarefas
	bool tick(); //calculo do custo do projecto;
	bool isCompleted(); //indica acerca da conclusao do projecto
	void connect();
	bool removeTask(Task* t, bool removeProject = true);
	bool removeTrace();
	bool removeClient(bool removeProject = true);
	bool removeCollaborator(Collaborator* c, bool removeProject = true);
	bool operator==(const Project& p2) const { return (this->ID) == (p2.ID); };
	friend ostream & operator<<(ostream& out, const Project& p);
	friend istream & operator>>(istream& in, Project& p);
	void updateCollaborators(){ collaborators = calculateCollaborators(); };
private:
		vector<Collaborator*> calculateCollaborators()const;
public:
		//class de excepção associada a Projectos
		class ProjectExcept
		{
			string description;
		public:
			ProjectExcept(string description) :description(description){};
			string operator()(){ return description; };
		};
		//interface de comparacao
		class ProjectComparator
		{
		public:
			virtual bool operator()(const Project& t1, const Project& t2) = 0;
			virtual bool operator()(const Project* t1, const Project* t2) = 0;
			virtual string getAbbreviation() const = 0;
		};
		//class de comparação que servirá para ordenar os projectos de forma alfabetica
		class ProjectComparatorAlphabetic : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.name < t2.name; };
			bool operator()(const Project* t1, const Project* t2) { return t1->name < t2->name; };
			string getAbbreviation() const{ return "Alph"; };
		};
		//class de comparação que servirá para ordenar os projectos em função do custo
		class ProjectComparatorCost : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.cost < t2.cost; };
			bool operator()(const Project* t1, const Project* t2) { return t1->cost < t2->cost; };
			string getAbbreviation() const{ return "Cost"; };
		};
		//class de comparação que servirá para ordenar os projectos por ID
		class ProjectComparatorID : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.getID() < t2.getID(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->getID() < t2->getID(); };
			string getAbbreviation() const{ return "ID"; };
		};
		//class de comparação que servirá para ordenar os projectos por numero de tarefas
		class ProjectComparatorNumTasks : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.getTasks().size() < t2.getTasks().size(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->getTasks().size() < t2->getTasks().size(); };
			string getAbbreviation() const{ return "N Tasks"; };
		};
		//class de comparação que servirá para ordenar os projectos por numero de colaboradores
		class ProjectComparatorNumCollaborators : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.getCollaborators().size() < t2.getCollaborators().size(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->getCollaborators().size() < t2->getCollaborators().size(); };
			string getAbbreviation() const{ return "N. Col"; };
		};
		//class de comparação que servirá para ordenar os projectos por tipo
		class ProjectComparatorType : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.getType() < t2.getType(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->getType() < t2->getType(); };
			string getAbbreviation() const{ return "Type"; };
		};
		//class de comparação que servirá para ordenar os projectos por prazo
		class ProjectComparatorDeadline : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.getDeadline() < t2.getDeadline(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->getDeadline() < t2->getDeadline(); };
			string getAbbreviation() const{ return "Deadline"; };
		};
		//class de comparação que servirá para ordenar os projectos por data estimada de terminacao do projecto
		class ProjectComparatorTimeToFinish : public ProjectComparator
		{
		public:
			bool operator()(const Project& t1, const Project& t2) { return t1.weeksToFinish() < t2.weeksToFinish(); };
			bool operator()(const Project* t1, const Project* t2) { return t1->weeksToFinish() < t2->weeksToFinish(); };
			string getAbbreviation() const{ return "Est finish"; };
		};
};
#endif
