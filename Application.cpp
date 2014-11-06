#include "Application.h"


vector<Project*> Application::projects;
vector<Client*> Application::clients;
vector<Collaborator*> Application::collaborators;
vector<Task*> Application::tasks;
Date Application::d;
Application* Application::instance = NULL;

Application::ApplicationExcept::ApplicationExcept(string description) : description(description){};
string Application::ApplicationExcept::operator()(){ return description; };

Application* Application::Instance()
{
	if (instance == NULL)
		instance = new Application();
	return instance;
}
Application::Application()
{}
Application::~Application()
{
	clear();
}
void Application::clear()
{
	for (size_t i = 0; i < projects.size(); i++)
		delete projects.at(i);
	for (size_t i = 0; i < clients.size(); i++)
		delete clients.at(i);
	for (size_t i = 0; i < collaborators.size(); i++)
		delete collaborators.at(i);
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks.at(i);
	projects.clear();
	clients.clear();
	collaborators.clear();
	tasks.clear();
}
vector<Project*> Application::getProjects()  { return projects; };
vector<Client*> Application::getClients()  { return clients; };
///adaptacao de binary_search
template<class T>
T* binary_searchID(vector<T*> v, int ID)
{
	int left = 0, right = v.size() - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (v[middle]->getID() < ID)
			left = middle + 1;
		else if (ID < v[middle]->getID())
			right = middle - 1;
		else
			return v[middle]; // encontrou
	}
	return NULL; // nao encontrou
}


Project* Application::getProjectPtr(int ID)
{
	/*for (size_t i = 0; i < projects.size(); ++i)
	if (projects.at(i)->getID() == ID)
		return projects.at(i);
	return NULL;*/
	return binary_searchID(projects, ID);
};
Client* Application::getClientPtr(int ID)
{
	/*for (size_t i = 0; i < clients.size(); ++i)
	if (clients.at(i)->getID() == ID)
		return clients.at(i);
	return NULL;*/
	return binary_searchID(clients, ID);
};
Collaborator* Application::getCollaboratorPtr(int ID)
{
	//for (size_t i = 0; i < collaborators.size(); ++i)
	//if (collaborators.at(i)->getID() == ID)
	//	return collaborators.at(i);
	//return NULL;
	return binary_searchID(collaborators, ID);
};
Task* Application::getTaskPtr(int ID)
{
	/*for (size_t i = 0; i < tasks.size(); ++i)
	if (tasks.at(i)->getID() == ID)
		return tasks.at(i);
	return NULL;*/
	return binary_searchID(tasks, ID);
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
	for (size_t i = 0; i < clients.size(); ++i)
	if (*clients.at(i) == *c)
		throw ApplicationExcept("Client already exists");
	clients.push_back(c);
};
void Application::addCollaborator(Collaborator* c)
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (*collaborators.at(i) == *c)
		throw ApplicationExcept("Collaborator already exists");
	collaborators.push_back(c);
}
void Application::addTask(Task* t)
{
	for (size_t i = 0; i < tasks.size(); ++i)
	if (*tasks.at(i) == *t)
		throw ApplicationExcept("Task already exists");
	tasks.push_back(t);
};

bool Application::removeTask(Task* t)
{
	if (t == NULL)
		throw ApplicationExcept("Invalid Task");
	size_t pos = 0;
	for (; pos < tasks.size(); pos++)
	{
		if (t == tasks.at(pos))
			break;
	}
	if (pos == tasks.size())
		throw ApplicationExcept("Task being removed does not exist");
	try
	{
		t->removeTrace();
	}
	catch (Task::TaskExcept& e)
	{
		cerr << e();
	}
	tasks.erase(tasks.begin() + pos);
	delete t;
	return true;
}
bool Application::removeProject(Project* p)
{
	if (p == NULL)
		throw ApplicationExcept("Invalid Project being removed from Application");
	size_t j = 0;
	for (; j < projects.size(); j++)
	{
		if (*p == *projects.at(j))
			break;
	}
	if (j == projects.size())
		throw ApplicationExcept("Project being removed does not exist");
	p->removeTrace();
	for (size_t i = 0; i < tasks.size(); i++)
	{
		if (*tasks.at(i)->getProject() == *p)
		{
			delete tasks.at(i);
			tasks.erase(tasks.begin() + i);
			i--;
		}
	}
	for (size_t i = 0; i < projects.size(); i++)
	{
		if (*p == *projects.at(i))
		{
			projects.erase(projects.begin() + i);
			delete p;
			i--;
		}
	}
	return true;
}
bool Application::removeClient(Client* c)
{
	if (c == NULL)
		throw ApplicationExcept("Invalid client being removed from Application");
	size_t j = 0;
	for (; j < clients.size(); j++)
	{
		if (*c == *clients.at(j))
			break;
	}
	if (j == clients.size())
		throw ApplicationExcept("Client being removed does not exist");
	for (size_t i = 0; i < c->getProjects().size(); i++)
		removeProject(c->getProjects().at(i));
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (*c == *clients.at(i))
		{
			clients.erase(clients.begin() + i);
			delete c;
			i--;
			return true;
		}
	}
	return false;
}

bool Application::removeCollaborator(Collaborator* c)
{
	if (c == NULL)
		throw ApplicationExcept("Invalid collaborator being removed from application");
	size_t i = 0;
	for (; i < collaborators.size(); i++)
	{
		if (*c == *collaborators.at(i))
			break;
	}
	if (i == collaborators.size())
		throw ApplicationExcept("Collaborator being removed does not exist");
	c->removeTrace();
	collaborators.erase(collaborators.begin() + i);
	delete c;
	return true;
}

void Application::writeProjects(ofstream& fout)
{
	fout.open("projects.txt");
	fout << projects.size() << endl;
	for (size_t i = 0; i < projects.size(); i++)
	{
		fout << *projects.at(i);
	}
	fout.close();
}
void Application::writeClients(ofstream& fout)
{
	fout.open("clients.txt");
	fout << clients.size() << endl;
	for (size_t i = 0; i < clients.size(); i++)
	{
		fout << *clients.at(i);
	}
	fout.close();
}
void Application::writeCollaborators(ofstream& fout)
{
	fout.open("collaborators.txt");
	fout << collaborators.size() << endl;
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		fout << *collaborators.at(i);
	}
	fout.close();
}
void Application::writeTasks(ofstream& fout)
{
	fout.open("tasks.txt");
	fout << tasks.size() << endl;
	for (size_t i = 0; i < tasks.size(); i++)
	{
		fout << *tasks.at(i);
	}
	fout.close();
}
void Application::writeFiles()
{
	ofstream fout;
	writeProjects(fout);
	writeClients(fout);
	writeCollaborators(fout);
	writeTasks(fout);
	writeApp(fout);
	fout.close();
}
void Application::readProjects(ifstream& fin)
{
	fin.open("projects.txt");
	if (!fin)
		throw ApplicationExcept("projects.txt does not exist");
	unsigned int numprojects = 0;
	fin >> numprojects;
	fin.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		Project* p = new Project();
		fin >> *p;
		projects.push_back(p);
	}
	fin.close();
}
void Application::readClients(ifstream& fin)
{
	fin.open("clients.txt");
	if (!fin)
		throw ApplicationExcept("clients.txt does not exist");
	unsigned int numclients = 0;
	fin >> numclients;
	fin.ignore();
	for (size_t i = 0; i < numclients; i++)
	{
		Client* c = new Client();
		fin >> *c;
		clients.push_back(c);
	}
	fin.close();
}
void Application::readCollaborators(ifstream& fin)
{
	fin.open("collaborators.txt");
	if (!fin)
		throw ApplicationExcept("collaborators.txt does not exist");
	unsigned int numcollaborators = 0;
	fin >> numcollaborators;
	fin.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		string title;
		getline(fin, title);
		Collaborator* c = Collaborator::newCollaboratorTitle(title);
		fin >> *c;
		collaborators.push_back(c);
	}
	fin.close();
}
void Application::readTasks(ifstream& fin)
{
	fin.open("tasks.txt");
	if (!fin)
		throw ApplicationExcept("tasks.txt does not exist");
	unsigned int numtasks = 0;
	fin >> numtasks;
	fin.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		Task* t = new Task();
		fin >> *t;
		tasks.push_back(t);
	}
	fin.close();
}

void Application::readApp(ifstream& fin)
{
	fin.open("application.txt");
	if (!fin)
		throw ApplicationExcept("application.txt does not exist");
	string date;
	getline(fin, date);
	d = Date(date);
	fin.close();
}
void Application::writeApp(ofstream& fout)
{
	fout.open("application.txt");
	fout << d.printDate2() << endl;
	fout.close();
}
void Application::connect()
{
	try{

		for (size_t i = 0; i < projects.size(); i++)
		{
			projects.at(i)->connect();
		}
	}
	catch (Project::ProjectExcept& e)
	{
		throw ApplicationExcept(e());
	}
	try{

		for (size_t i = 0; i < clients.size(); i++)
		{
			clients.at(i)->connect();
		}
	}
	catch (Client::ClientExcept& e)
	{
		throw ApplicationExcept(e());
	}
	try{

		for (size_t i = 0; i < collaborators.size(); i++)
		{
			collaborators.at(i)->connect();
		}
	}
	catch (Collaborator::CollaboratorExcept& e)
	{
		throw ApplicationExcept(e());
	}
	try
	{
		for (size_t i = 0; i < tasks.size(); i++)
		{
			tasks.at(i)->connect();
		}
	}
	catch (Task::TaskExcept& e)
	{
		throw ApplicationExcept(e());
	}
}
void Application::readFiles()
{
	clear();
	ifstream fin;
	readProjects(fin);
	readClients(fin);
	readCollaborators(fin);
	readTasks(fin);
	readApp(fin);
	connect();
}
void Application::tick()
{
	d += Date::toSeconds(7, 0, 0, 0, 0, 0);//avancar uma semana
	for (size_t i = 0; i < projects.size(); ++i)
		projects.at(i)->tick();
}
void Application::genApplication(){
	clear();
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
		Collaborator* c = Collaborator::newRandomCollaborator(i);
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


vector<Collaborator*> Application::getCollaborators()
{
	return collaborators;
}
vector<Task*> Application::getTasks()
{
	return tasks;
}
Date Application::getDate() { return d; }