#include "Application.h"


vector<Project*> Application::projects;
vector<Client*> Application::clients;
vector<Collaborator*> Application::collaborators;
vector<Task*> Application::tasks;

void Application::addCollaborator(Collaborator* c)
{
	for(size_t i = 0; i < collaborators.size(); ++i)
		if(*collaborators.at(i) == *c)
			throw ApplicationExcept("Collaborator already exists");
	collaborators.push_back(c);
}
void Application::writeFiles()
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
void Application::readFiles()
{
	ifstream fin;
	fin.open("projects.txt");
	int numprojects = 0;
	fin >> numprojects;
	fin.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		Project* p = new Project();
		fin >> *p;
		projects.push_back(p);
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
		clients.push_back(c);
	}
	fin.close();
	fin.open("collaborators.txt");
	int numcollaborators = 0;
	fin >> numcollaborators;
	fin.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		Collaborator* c = new Collaborator();
		fin >> *c;
		collaborators.push_back(c);
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
		tasks.push_back(t);
	}
	fin.close();
	for (size_t i = 0; i < projects.size(); i++)
	{
		projects.at(i)->connect();
	}
	for (size_t i = 0; i < clients.size(); i++)
	{
		clients.at(i)->connect();
	}
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		collaborators.at(i)->connect();
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i)->connect();
	}
}

void Application::tick()
{
	for (int i = 0; i < projects.size(); ++i)
		projects.at(i)->tick();
}
void Application::genApplication(){
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
		for (size_t k = j + 1; k < projects.at(i)->getTasks().size(); k++)
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
}

Project*  Application::getProjectPtr(int ID) /////////////////////******
{
	for (size_t i = 0; i < projects.size(); ++i)
	if (projects.at(i)->getID() == ID)
		return projects.at(i);
	return NULL;
};
 Client*  Application::getClientPtr(int ID)/////////////////////******
{
	for (size_t i = 0; i < clients.size(); ++i)
	if (clients.at(i)->getID() == ID)
		return clients.at(i);
	return NULL;
};
 Collaborator*  Application::getCollaboratorPtr(int ID) /////////////////////******
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (collaborators.at(i)->getID() == ID)
		return collaborators.at(i);
	return NULL;
};
 Task*  Application::getTaskPtr(int ID)/////////////////////******
{
	for (size_t i = 0; i < tasks.size(); ++i)
	if (tasks.at(i)->getID() == ID)
		return tasks.at(i);
	return NULL;
};
 void Application::addProject(Project* p)
{
	for (size_t i = 0; i < projects.size(); ++i)
	if (*projects.at(i) == *p)
		throw ApplicationExcept("Project already exists");
	projects.push_back(p);
};
void Application::addClient(Client* c)
{
	for (size_t i = 0; i < projects.size(); ++i)
	if (*clients.at(i) == *c)
		throw ApplicationExcept("Client already exists");
	clients.push_back(c);
};

 void Application::addTask(Task* t)
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (*tasks.at(i) == *t)
		throw ApplicationExcept("Task already exists");
	tasks.push_back(t);
};
Application::~Application()
{
	for (size_t i = 0; i < projects.size(); i++)
		delete projects.at(i);
	for (size_t i = 0; i < clients.size(); i++)
		delete clients.at(i);
	for (size_t i = 0; i < collaborators.size(); i++)
		delete collaborators.at(i);
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks.at(i);
}