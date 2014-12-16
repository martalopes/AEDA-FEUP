#include "Application.h"


vector<Project*> Application::projects;
BST<SmartPtr<Client>> Application::clients(SmartPtr<Client>((Client*)NULL));
vector<Collaborator*> Application::collaborators;
vector<Task*> Application::tasks;
Colhash Application::former_collaborators;
CV_queue Application::cvs;
Date Application::d;
Application* Application::instance = NULL;

static vector<Client*> tempclients;

Application::ApplicationExcept::ApplicationExcept(string description) : description(description){};
string Application::ApplicationExcept::operator()(){ return description; };

bool CollaboratorEqual::operator()(Collaborator* const c1, Collaborator* const c2) const
{
	return  *c1 == *c2;
}
size_t CollaboratorHash::operator()(Collaborator* const c) const
{
	return (size_t)c->getID();
}

bool CVcomparator::operator()(const CV* c1, const CV*c2)
{
	return c1->getValue() < c2->getValue();
}
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

	BSTItrIn<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		it.retrieve().deletePtr();
		it.advance();
	}

	for (size_t i = 0; i < collaborators.size(); i++)
		delete collaborators.at(i);
	for (size_t i = 0; i < tasks.size(); i++)
		delete tasks.at(i);
	projects.clear();
	clients.makeEmpty();
	collaborators.clear();
	tasks.clear();
}
vector<Project*> Application::getProjects()  { return projects; };
//vector<Client*> Application::getClients(BSTItr<SmartPtr<Client>> * it) 
//{
//	vector<Client*> out;
//	while (!it->isAtEnd())
//	{
//		out.push_back(it->retrieve().getPointer());
//		it->advance();
//	}
//	it->reset(clients);
//	return out;
//};

vector<Client*> Application::getClients_InOrder()
{
	vector<Client*> out;
	BSTItrIn<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		out.push_back(it.retrieve().getPointer());
		it.advance();
	}
	return out;
}
vector<Client*> Application::getClients_PreOrder()
{
	vector<Client*> out;
	BSTItrPre<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		out.push_back(it.retrieve().getPointer());
		it.advance();
	}
	return out;
}
vector<Client*> Application::getClients_PostOrder()
{
	vector<Client*> out;
	BSTItrPost<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		out.push_back(it.retrieve().getPointer());
		it.advance();
	}
	return out;
}
vector<Client*> Application::getClients_Level()
{
	vector<Client*> out;
	BSTItrLevel<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		out.push_back(it.retrieve().getPointer());
		it.advance();
	}
	return out;
}
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
	return binary_searchID(projects, ID);
};
Client* Application::getClientPtr(int ID)
{
	if (tempclients.size() == 0)
	{
		BSTItrIn<SmartPtr<Client>> it(clients);
		while (!it.isAtEnd())
		{
			if (it.retrieve()->getID() == ID)
				return it.retrieve().getPointer();
			it.advance();
		}
		return NULL;
	}
	else
	{
		 return binary_searchID(tempclients, ID);
	}
};
Collaborator* Application::getCollaboratorPtr(int ID)
{
	Collaborator* out = binary_searchID(collaborators, ID);
	if (out != NULL)
		return out;
	auto it = former_collaborators.begin();
	for (; it != former_collaborators.end(); ++it)
	{
		if ((**it).getID() == ID)
			return *it;
	}
	return NULL;
};
Task* Application::getTaskPtr(int ID)
{
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
	if (!clients.find(SmartPtr<Client>(c)).isNull())
		throw ApplicationExcept("Client already exists");
	else clients.insert(SmartPtr<Client>(c));
};
void Application::addCollaborator(Collaborator* c)
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (*collaborators.at(i) == *c)
		throw ApplicationExcept("Collaborator already exists");
	collaborators.push_back(c);
}

void Application::setFormer(Collaborator* c)
{
	auto it = former_collaborators.begin();
	for (; it != former_collaborators.end(); ++it)
	{
		if (*c == **it)
		{
			throw ApplicationExcept("Collaborator is already in former list");
		}
	}
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (*collaborators.at(i) == *c)
	{
		collaborators.erase(collaborators.begin() + i);
		c->leave();
		former_collaborators.insert(c);
		return;
	}
	throw ApplicationExcept("Collaborator does not exist");
}



void Application::addCV(CV* c)
{
	cvs.push(c);
}

void Application::hire(CV * c, int weeklyHours)
{
	addCollaborator(c->toCollaborator(weeklyHours));
	removeCV(c);
}

void Application::removeCV(CV* c)
{
	CV_queue temp;
	bool found = false;
	while (!cvs.empty())
	{
		if (!(cvs.top() == c))
			temp.push(cvs.top());
		else found = true;
		cvs.pop();
	}
	while (!temp.empty())
	{
		cvs.push(temp.top());
		temp.pop();
	}
	if (found)
		delete c;
}

void Application::unsetFormer(Collaborator* c)
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (*collaborators.at(i) == *c)
	{
		throw ApplicationExcept("Collaborator is currently employed");
	}
	auto it = former_collaborators.find(c);
	if (it == former_collaborators.end())
		throw ApplicationExcept("Collaborator does not exist");
	former_collaborators.erase(c);
	c->reinstate();
	collaborators.push_back(c);
	sort(collaborators.begin(), collaborators.end(), Collaborator::CollaboratorComparatorID());
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
	projects.erase(projects.begin() + j);
	delete p;
	return true;
}
bool Application::removeClient(Client* c)
{
	if (c == NULL)
		throw ApplicationExcept("Invalid client being removed from Application");
	if (clients.find(SmartPtr<Client>(c)).isNull())
		throw ApplicationExcept("Client being removed does not exist");
	for (size_t i = 0; i < c->getProjects().size(); i++)
	{
		removeProject(c->getProjects().at(i));
		i--;
	}
	clients.remove(SmartPtr<Client>(c));
	delete c;
	return true;
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
 bool Application::removeFormerCollaborator(Collaborator* c)
{
	 if (c == NULL)
		 throw ApplicationExcept("Invalid former collaborator being removed from application");
	 if (former_collaborators.find(c) == former_collaborators.end())
	 {
		 throw ApplicationExcept("Invalid collaborator is not in former collaborator list");
	 }
	 else former_collaborators.erase(c);
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
	int numclients=0;
	BSTItrIn<SmartPtr<Client>> it1(clients);
	while (!it1.isAtEnd())
	{
		numclients++;
		it1.advance();
	}
	fout << numclients << endl;
	BSTItrIn<SmartPtr<Client>> it(clients);
	while (!it.isAtEnd())
	{
		fout << *it.retrieve();
		it.advance();
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
void Application::writeFormerCollaborators(ofstream& fout)
{
	fout.open("formercollaborators.txt");
	fout << former_collaborators.size() << endl;
	auto it = former_collaborators.begin();
	for (; it != former_collaborators.begin(); ++it)
	{
		fout << **it;
	}
	fout.close();
}
void Application::writeCVs(ofstream& fout)
{
	fout.open("cvs.txt");
	vector<CV*> c = getCVs();
	fout << c.size()<< endl;
	for (size_t i = 0; i < c.size(); i++)
	{
		fout << *c.at(i);
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
	writeFormerCollaborators(fout);
	writeCVs(fout);
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
	//for (size_t i = 0; i < numclients; i++)
	//{
	//	Client* c = new Client();
	//	fin >> *c;
	//	clients.insert(SmartPtr<Client>(c));
	//}
	for (size_t i = 0; i < numclients; i++)
	{
		Client* c = new Client();
		fin >> *c;
		tempclients.push_back(c);
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
void Application::readFormerCollaborators(ifstream& fin)
{
	fin.open("formercollaborators.txt");
	if (!fin)
		throw ApplicationExcept("formercollaborators.txt does not exist");
	unsigned int numcollaborators = 0;
	fin >> numcollaborators;
	fin.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		string title;
		getline(fin, title);
		Collaborator* c = Collaborator::newCollaboratorTitle(title);
		fin >> *c;
		former_collaborators.insert(c);
	}
	fin.close();
}
void Application::readCVs(ifstream& fin)
{
	fin.open("cvs.txt");
	if (!fin)
		throw ApplicationExcept("cvs.txt does not exist");
	unsigned int numcvs = 0;
	fin >> numcvs;
	fin.ignore();
	for (size_t i = 0; i < numcvs; i++)
	{
		CV* c = new CV();
		fin >> *c;
		cvs.push(c);
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
		//BSTItrIn<SmartPtr<Client>> it(clients);
		//while (!it.isAtEnd())
		//{
		//	it.retrieve()->connect();
		//	it.advance();
		//}
		for (size_t i = 0; i < tempclients.size(); i++)
		{
			tempclients.at(i)->connect();
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
	try{
		auto it = former_collaborators.begin();
		for (; it!= former_collaborators.end(); ++it)
		{
			Collaborator* c = *it;
			former_collaborators.erase(it);
			c->connect();
			former_collaborators.insert(c);
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
void Application::fillBST()
{
	for (size_t i = 0; i < tempclients.size(); i++)
		clients.insert(SmartPtr<Client>(tempclients.at(i)));
	tempclients.clear();
}
void Application::updateClientOrder()
{
	vector<Client*> v = getClients_Level();
	clients.makeEmpty();
	for (size_t i = 0; i < v.size(); i++)
		clients.insert(SmartPtr<Client>(v.at(i)));
}

void Application::readFiles()
{
	clear();
	ifstream fin;
	readProjects(fin);
	readCollaborators(fin);
	readFormerCollaborators(fin);
	readCVs(fin);
	readClients(fin);
	readTasks(fin);
	readApp(fin);
	connect();
	fillBST();
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
		clients.insert(SmartPtr<Client>(c));
	}
	for (int i = 1; i <= numtasks; i++)
	{
		Task* t = new Task(i);
		tasks.push_back(t);
	}
	vector<Client*> clients_vector = getClients_InOrder();
	for (size_t i = 0; i < projects.size(); i++)
	{
		projects.at(i)->setClient(clients_vector.at(rand() % clients_vector.size())); //assign each project a client
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
			collaborators.at(i)->addTask(tasks.at(j), rand() % 5 + 1);
		}
	}
	int i = 0;
}


vector<Collaborator*> Application::getCollaborators()
{
	return collaborators;
}

vector<Collaborator*> Application::getFormerCollaborators()
{
	auto it = former_collaborators.begin();
	vector<Collaborator*> out;
	for (; it != former_collaborators.end(); ++it)
	{
		out.push_back(*it);
	}
	return out;
}
vector<CV*> Application::getCVs()
{
	CV_queue temp = cvs;
	vector<CV*> out;
	while (!temp.empty())
	{
		out.push_back(temp.top());
		temp.pop();
	}
	return out;
}
void Application::updateCVorder()
{
	CV_queue temp;
	while (!cvs.empty())
	{
		temp.push(cvs.top());
		cvs.pop();
	}
	while (!temp.empty())
	{
		cvs.push(temp.top());
		temp.pop();
	}
}
vector<Task*> Application::getTasks()
{
	return tasks;
}
Date Application::getDate() { return d; }