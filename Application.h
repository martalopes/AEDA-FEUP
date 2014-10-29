#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>

#define NUM_PROJECTS 10
#define NUM_CLIENTS 5
#define NUM_COLLABORATOR 50
#define NUM_TASKS 100

using namespace std;

enum ASSOC_TYPE = {};


class Application
{
	friend class Client;
	friend class Task;
	friend class Collaborator;
	friend class Project;
public:
	class ApplicationExcept
		{
			string description;
		public:
			ApplicationExcept(string description) :description(description){};
			string operator()(){ return description; };
		};
	Application(){};
	void writeFiles()
	{
		ofstream fout;
		fout.open("projects.txt");
		fout << projects.size() << endl;
		for (size_t i = 0; i < projects.size(); i++)
		{
			fout << *projects.at(i);
		}
		fout.close();
		fout.open("clients.txt");
		fout << clients.size() << endl;
		for (size_t i = 0; i < clients.size(); i++)
		{
			fout << *clients.at(i);
		}
		fout.close();
		fout.open("collaborators.txt");
		fout << collaborators.size() << endl;
		for (size_t i = 0; i < collaborators.size(); i++)
		{
			fout << *collaborators.at(i);
		}
		fout.close();
		fout.open("tasks.txt");
		fout << tasks.size() << endl;
		for (size_t i = 0; i < tasks.size(); i++)
		{
			fout << *tasks.at(i);
		}
		fout.close();
	}
	void readFiles()
	{
		ifstream fin;
		fin.open("projects.txt");
		int numprojects= 0;
		fin >> numprojects;
		fin.ignore();
		for (size_t i = 0; i < numprojects; i++)
		{
			Project* p = new Project();
			fin >> *p;
		}
		fin.close();
		fin.open("clients.txt");
		int numclients = 0;
		fin >> numclients;
		fin.ignore();
		for (size_t i = 0; i < numclients; i++)
		{
			Client* c = new Client();
			fin >> *c;
		}
		fin.close();
		fin.open("collaborators.txt");
		int numcollaborators=0;
		fin >> numcollaborators;
		fin.ignore();
		for (size_t i = 0; i < numcollaborators; i++)
		{
			Collaborator* c = new Collaborator();
			fin >> *c;
		}
		fin.close();
		fin.open("tasks.txt");
		int numtasks = 0;
		fin >> numtasks;
		fin.ignore();
		for (size_t i = 0; i < numtasks; i++)
		{
			Task* t = new Task();
			fin >> *t;
		}
		fin.close();
	}
	void tick()
	{
		for(int i = 0; i < projects.size(); ++i)
			projects.at(i)->tick();
	}
	vector<Project*> getProjects() const {return projects;};
	vector<Client*> getClients() const {return clients;};
	vector<Collaborator*> getCollaborators() const {return collaborators;};
	vector<Task*> getTasks() const {return tasks;};
	Project* getProjectPtr(int ID) const /////////////////////******
	{
		for(size_t i = 0; i < projects.size() ; ++i)
			if(projects.at(i)->getID() == ID)
				return projects.at(i);
		return NULL;
	};
	Client* getClientPtr(int ID) const /////////////////////******
		{
			for(size_t i = 0; i < clients.size() ; ++i)
				if(clients.at(i)->getID() == ID)
					return clients.at(i);
			return NULL;
		};
	Collaborator* getCollaboratorPtr(int ID) const /////////////////////******
		{
			for(size_t i = 0; i < collaborators.size() ; ++i)
				if(collaborators.at(i)->getID() == ID)
					return collaborators.at(i);
			return NULL;
		};
	Task* getTaskPtr(int ID) const /////////////////////******
		{
			for(size_t i = 0; i < tasks.size() ; ++i)
				if(tasks.at(i)->getID() == ID)
					return tasks.at(i);
			return NULL;
		};
	Application& addProject(Project* p)
	{
		for(size_t i = 0; i < projects.size(); ++i)
			if(*projects.at(i) == *p)
				throw ApplicationExcept("Project already exists");
		projects.push_back(p);
		return *this;
	};
	Application& addClient(Client* c)
		{
			for(size_t i = 0; i < projects.size(); ++i)
				if(*clients.at(i) == *c)
					throw ApplicationExcept("Client already exists");
			clients.push_back(c);
			return *this;
		};
	Application& addCollaborator(Collaborator* c);
	Application& addTask(Task* t)
		{
			for(size_t i = 0; i < collaborators.size(); ++i)
				if(*tasks.at(i) == *t)
					throw ApplicationExcept("Task already exists");
			tasks.push_back(t);
			return *this;
		};
	~Application()
	{
		for(size_t i = 0; i < projects.size(); i++)
			delete projects.at(i);
		for(size_t i = 0; i < clients.size(); i++)
					delete clients.at(i);
		for(size_t i = 0; i < collaborators.size(); i++)
					delete collaborators.at(i);
		for(size_t i = 0; i < tasks.size(); i++)
					delete tasks.at(i);
	}
	void genApplication()
	{
		int numprojects = NUM_PROJECTS;
		int numclients = NUM_CLIENTS;
		int numcollaborators = NUM_COLLABORATOR;
		int numtasks = NUM_TASKS;
		for (int i = 1; i <= numprojects; i++)
		{
			Project* p = new Project(i);
			projects.push_back(p);
		}
		for (int i = 1; i <= numcollaborators; i++)
		{
			Collaborator* c = new Collaborator(i);
			collaborators.push_back(c);
		}
		for (int i = 1; i <= numclients; i++)
		{
			Client* c = new Client(i);
			clients.push_back(c);
		}
		for (int i = 1; i <= numtasks; i++)
		{
			Task* t = new Task(i);
			tasks.push_back(t);
		}
		for (size_t i = 0; i < projects.size(); i++)
		{
			projects.at(i)->setClient(clients.at(rand() % clients.size())); //assign each project a client
		}
		for (size_t i = 0; i < tasks.size(); i++)
		{
			tasks.at(i)->setProject(projects.at(rand() % projects.size())); //assign each task to a project
		}
		for (size_t i = 0; i < projects.size(); i++)
		{
			for (size_t j = 0; j < projects.at(i)->getTasks().size(); j++)
				for (size_t k = j+1; k < projects.at(i)->getTasks().size(); k++)
				if ((rand() % 3) == 0)
					projects.at(i)->getTasks().at(j)->addDependant(projects.at(i)->getTasks().at(k));
		}
		for (size_t i = 0; i < collaborators.size(); i++)
		{
			for (size_t j = 0; j < tasks.size(); j++)
			if (rand() % 10 == 0)
			{
				//if (tasks.at(i)->isReady())
					collaborators.at(i)->addTask(tasks.at(j), rand() % 5 + 1);
			}
		}
		int i = 0;
	};
private:
	vector<Project*> projects;
	vector<Client*> clients;
	vector<Collaborator*> collaborators;
	vector<Task*> tasks;
	//static vector<pair<int, int> > dependants;
	static vector<pair<void *, vector<int>>> cenas;
};



#endif
