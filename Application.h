#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"
#include "Menu.h"
#include "Utils.h"

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

class Menu;

class Application
{
	friend class Client;
	friend class Task;
	friend class Collaborator;
	friend class Project;
public:
	//class de excepção associada a Aplicações 
	class ApplicationExcept
	{
		string description;
	public:
		ApplicationExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	Application();
	~Application();
	static vector<Project*> getProjects()  { return projects; };
	static vector<Client*> getClients()  { return clients; };
	static vector<Collaborator*> getCollaborators()  { return collaborators; };
	static vector<Task*> getTasks()  { return tasks; };
	static Project* getProjectPtr(int ID);
	static Client* getClientPtr(int ID);
	static Collaborator* getCollaboratorPtr(int ID);
	static Task* getTaskPtr(int ID);
	static void addProject(Project* p);
	static void addClient(Client* c);
	static void addCollaborator(Collaborator* c);
	static void addTask(Task* t);


	static bool removeProject(Project* p);
	static bool removeClient(Client* c);
	static bool removeTask(Task* t);
	static bool removeCollaborator(Collaborator* c);


	/*escrita*/

	static void writeFiles(); //função que escreve nos ficheiros 
	static void writeProjects(ofstream& fout);
	static void writeClients(ofstream& fout);
	static void writeCollaborators(ofstream& fout);
	static void writeTasks(ofstream& fout);

	/*leitura*/

	static void readFiles(); //função que lê dos ficheiros
	static void readProjects(ifstream& fin);
	static void readClients(ifstream& fin);
	static void readCollaborators(ifstream& fin);
	static void readTasks(ifstream& fin);
	static void connect();

	static void tick(); //guarda no vector de projectos o custo de cada projecto
	static void genApplication(); //função geradora de Applications
	static Date getDate() { return d; };
private:
	static vector<Project*> projects;
	static vector<Client*> clients;
	static vector<Collaborator*> collaborators;
	static vector<Task*> tasks;
	static Date d;
};



#endif
