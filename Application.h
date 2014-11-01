#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"
#include "Menu.h"

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
	Application(){};  
	~Application();
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


	bool removeProject(Project* p);
	bool removeClient(Client* c);
	bool removeTask(Task* t);
	bool removeCollaborator(Collaborator* c);


					/*escrita*/

	void writeFiles(); //função que escreve nos ficheiros 
	void writeProjects(ofstream& fout)const;
	void writeClients(ofstream& fout)const;
	void writeCollaborators(ofstream& fout)const;
	void writeTasks(ofstream& fout)const;

					/*leitura*/

	void readFiles(); //função que lê dos ficheiros
	void readProjects(ifstream& fin);
	void readClients(ifstream& fin);
	void readCollaborators(ifstream& fin);
	void readTasks(ifstream& fin);
	void connect();
	void play();
	void createMenus();


	void tick(); //guarda no vector de projectos o custo de cada projecto
	void genApplication(); //função geradora de Applications 
private:
	static vector<Project*> projects;
	static vector<Client*> clients;
	static vector<Collaborator*> collaborators;
	static vector<Task*> tasks;
	Menu* menu;
	vector<Menu*> menus;
};



#endif
