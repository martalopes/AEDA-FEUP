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
	void writeFiles();
	void readFiles();
	void tick();
	vector<Project*> getProjects() const {return projects;};
	vector<Client*> getClients() const {return clients;};
	vector<Collaborator*> getCollaborators() const {return collaborators;};
	vector<Task*> getTasks() const {return tasks;};
	static Project* getProjectPtr(int ID);
	static Client* getClientPtr(int ID);
	static Collaborator* getCollaboratorPtr(int ID) ;
	static Task* getTaskPtr(int ID);
	static void addProject(Project* p);
	static void addClient(Client* c);
	static void addCollaborator(Collaborator* c);
	static void addTask(Task* t);
	~Application();
	void genApplication();
private:
	static vector<Project*> projects;
	static vector<Client*> clients;
	static vector<Collaborator*> collaborators;
	static vector<Task*> tasks;
};



#endif
