#include "Project.h"
#include "Task.h"
#include "Collaborator.h"

int Project::lastID = 0;
Project::Project() : ID(0), client(NULL), cost(0) {};
Project::Project(string name, string type, Date deadline, double cost) : deadline(deadline), name(name), type(type), ID(++lastID), cost(cost), client(NULL){};
Project::Project(string name, string type, Date deadline, double cost, int setID) : name(name), type(type), ID(++lastID), deadline(deadline), cost(cost), client(NULL){ if (setID > lastID) lastID = setID; };

Project::Project(int i)
{
	stringstream s1, s2;
	s1 << "Project " << i;
	s2 << "Type " << i;
	*this = Project(s1.str(), s2.str(), Date() + Date::toSeconds(0, 6 + rand() % 10, 0, 0, 0, 0), 10000 + (rand() % 5000 - 2500));
}
string Project::toString() const 
{ return normalize(to_string(ID), name, 30); };
bool Project::setClient(Client* c, bool addProject)
{
	if (c == NULL) throw ProjectExcept("Invalid client");
	if (client != NULL)
		return false;
	else client = c;
	if (addProject)
		c->addProject(this, false);
	return true;
}
bool Project::addTask(Task * t, bool setProject)
{
	if (t == NULL)
		throw Project::ProjectExcept("Invalid Task being added to Project");
	if (t->getProject() != NULL)
	if (!(*t->getProject() == *this))
		return false;
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		if (*tasks.at(i) == *t)
		{
			return false;
		}
	}
	tasks.push_back(t);
	collaborators = calculateCollaborators();
	if (setProject)
		return t->setProject(this, false);
	return true;
}
bool Project::tick()
{
	if (isCompleted())
		return false;
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		if (rand() % 20 == 0)
			tasks.at(i)->delay();
		if (rand() % 20 == 0)
			tasks.at(i)->speedup();
		double value = tasks.at(i)->tick();
		if (value >= 0)
			cost += value;
	}
	return true;
}
bool Project::isCompleted()
{
	for (size_t i = 0; i < tasks.size(); ++i)
	if (!(tasks.at(i)->isCompleted()))
		return false;
	return true;
}
void Project::connect()
{
	if ((int)client != 0)
	{
		client = Application::getClientPtr((int)client);
		if (client == NULL)
			throw ProjectExcept("Error in projects.txt");
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		if ((int)tasks.at(i) == 0)
			continue;
		Task* ptr = Application::getTaskPtr((int)tasks.at(i));
		if (ptr == NULL)
			throw ProjectExcept("Error in projects.txt");
		tasks.at(i) = ptr;
	}
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		if ((int)collaborators.at(i) == 0)
			continue;
		Collaborator* ptr = Application::getCollaboratorPtr((int)collaborators.at(i));
		if (ptr==NULL)
			throw ProjectExcept("Error in projects.txt");
		collaborators.at(i) = ptr;
	}

}

ostream & operator<<(ostream& out, const Project& p)
{
	out << p.ID << endl;
	out << p.name << endl;
	out << p.type << endl;
	if (p.client != NULL)
		out << p.client->getID() << endl;
	else out << 0 << endl;
	out << p.cost << endl;
	out << p.deadline.getTotalSeconds() << endl;
	out << p.tasks.size() << endl;
	for (size_t i = 0; i < p.tasks.size(); i++)
		out << p.tasks.at(i)->getID() << endl;
	out << p.collaborators.size() << endl;
	for (size_t i = 0; i < p.collaborators.size(); i++)
		out << p.collaborators.at(i)->getID() << endl;
	return out;
}
istream & operator>>(istream& in, Project& p)
{
	in >> p.ID;
	in.ignore();
	if (p.ID > Project::lastID)
		Project::lastID = p.ID;
	getline(in, p.name);
	getline(in, p.type);
	long unsigned int clientid;
	in >> clientid;
	in.ignore();
	p.client = (Client*)clientid;
	in >> p.cost;
	in.ignore();

	time_t totalseconds;
	in >> totalseconds;
	in.ignore();
	p.deadline = Date(totalseconds);

	unsigned int numtasks;
	in >> numtasks;
	in.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		long unsigned int taskid;
		in >> taskid;
		in.ignore();
		p.tasks.push_back((Task*)taskid);
	}
	unsigned int numcollaborators;
	in >> numcollaborators;
	in.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		long unsigned int collaboratorid;
		in >> collaboratorid;
		in.ignore();
		p.collaborators.push_back((Collaborator*)collaboratorid);
	}
	return in;
}

bool Project::removeTask(Task* t, bool removeProject)
{
	if (t == NULL)
		throw ProjectExcept("Invalid Task being removed");
	if (!t->isIsolated())
		return false;//se tiver associada a outras tarefas, nao pode ser removida
	for (size_t i = 0; i < tasks.size(); i++)
	if (*tasks.at(i) == *t)
	{
		tasks.erase(tasks.begin() + i);
		updateCollaborators();
		if (removeProject)
			t->removeProject(false);
		return true;
	}
	throw(ProjectExcept("Task does not exist"));
}
bool Project::removeClient(bool removeProject)
{
	if (client == NULL)
		return false;
	if (removeProject)
		client->removeProject(this, false);
	client = NULL;
	return true;
}

bool Project::removeTrace()
{
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i)->removeTraceOutsideProject();
	}
	if (client != NULL)
	client->removeProject(this, false);
	return true;
}

double Project::weeksToFinish() const
{
	if (tasks.size() == 0)
		return 0;
	double max = tasks.at(0)->calculateTimeToCompletion();
	if (abs(max - (-1)) < 0.001)
		return -1;
	for (size_t i = 1; i < tasks.size(); i++)
	{
		double value = tasks.at(i)->calculateTimeToCompletion();
		if (abs(value - (-1)) < 0.001)
			return -1;
		if (value > max)
			max = value;
	}
	return max;
}
bool Project::isPastDeadline(const Date& currentdate)
{
	if (this->isCompleted())
		return false;
	return (deadline < currentdate);
}
Date Project::projectedFinishDate(const Date& currentdate) const
{
	double weeks = weeksToFinish();
	if (abs(weeks - (-1)) < 0.001)
		return Date(0);
	else return currentdate + (int)(weeks * 7 * 24 * 3600);
}
vector<Collaborator*> Project::calculateCollaborators()const
{
	vector<Collaborator*> out;
	for (size_t i = 0; i < tasks.size(); i++)
	{
		for (size_t j = 0; j < tasks.at(i)->getCollaborators().size(); j++)
		if (tasks.at(i)->getCollaborators().at(j).first != NULL)
		if (find(out.begin(), out.end(), tasks.at(i)->getCollaborators().at(j).first) == out.end())
			out.push_back(tasks.at(i)->getCollaborators().at(j).first);
	}
	return out;
}

int  Project::getID() const		{ return this->ID; }
int  Project::getLastID()  { return lastID; }
string  Project::getName() const	{ return this->name; }
string  Project::getType() const  { return this->type; }
Client*  Project::getClient()const{ return this->client; }
double  Project::getCost() const	{ return this->cost; }
Date  Project::getDeadline()const { return deadline; }
void  Project::setDeadline(const Date& d){ deadline = d; }
vector<Task*> Project::getTasks() const { return this->tasks; }
vector<Collaborator*> Project::getCollaborators() const { return this->collaborators; }
void Project::setID(int ID) { this->ID = ID; }
void Project::setLastID(int lID) { lastID = lID;}
void Project::setName(string newname){ name = newname; }
void Project::setType(string newtype){ type = newtype; }
bool Project::operator==(const Project& p2) const { return (this->ID) == (p2.ID); }
void Project::updateCollaborators(){ collaborators = calculateCollaborators(); }
Project::ProjectExcept::ProjectExcept(string description) :description(description){}
string Project::ProjectExcept::operator()(){ return description; }


bool Project::ProjectComparatorAlphabetic ::operator()(const Project& t1, const Project& t2) { return t1.name < t2.name; }
bool Project::ProjectComparatorAlphabetic ::operator()(const Project* t1, const Project* t2) { return t1->name < t2->name; }
string Project::ProjectComparatorAlphabetic::getAbbreviation() const{ return "Alph"; }

bool Project::ProjectComparatorCost ::operator()(const Project& t1, const Project& t2) { return t1.cost < t2.cost; }
bool Project::ProjectComparatorCost ::operator()(const Project* t1, const Project* t2) { return t1->cost < t2->cost; }
string Project::ProjectComparatorCost::getAbbreviation() const{ return "Cost"; }

bool Project::ProjectComparatorID ::operator()(const Project& t1, const Project& t2) { return t1.getID() < t2.getID(); }
bool Project::ProjectComparatorID ::operator()(const Project* t1, const Project* t2) { return t1->getID() < t2->getID(); }
string Project::ProjectComparatorID::getAbbreviation() const{ return "ID"; }

bool Project::ProjectComparatorNumTasks ::operator()(const Project& t1, const Project& t2) { return t1.getTasks().size() < t2.getTasks().size(); }
bool Project::ProjectComparatorNumTasks ::operator()(const Project* t1, const Project* t2) { return t1->getTasks().size() < t2->getTasks().size(); }
string Project::ProjectComparatorNumTasks::getAbbreviation() const{ return "N Tasks"; }

bool Project::ProjectComparatorNumCollaborators ::operator()(const Project& t1, const Project& t2) { return t1.getCollaborators().size() < t2.getCollaborators().size(); }
bool Project::ProjectComparatorNumCollaborators ::operator()(const Project* t1, const Project* t2) { return t1->getCollaborators().size() < t2->getCollaborators().size(); }
string  Project::ProjectComparatorNumCollaborators::getAbbreviation() const{ return "N. Col"; }

bool Project::ProjectComparatorType::operator()(const Project& t1, const Project& t2) { return t1.getType() < t2.getType(); }
bool Project::ProjectComparatorType::operator()(const Project* t1, const Project* t2) { return t1->getType() < t2->getType(); }
string  Project::ProjectComparatorType::getAbbreviation() const{ return "Type"; }

bool Project::ProjectComparatorDeadline :: operator()(const Project& t1, const Project& t2) { return t1.getDeadline() < t2.getDeadline(); }
bool Project::ProjectComparatorDeadline ::operator()(const Project* t1, const Project* t2) { return t1->getDeadline() < t2->getDeadline(); }
string Project::ProjectComparatorDeadline::getAbbreviation() const{ return "Deadline"; }

bool Project::ProjectComparatorTimeToFinish ::operator()(const Project& t1, const Project& t2) { return t1.weeksToFinish() < t2.weeksToFinish(); }
bool Project::ProjectComparatorTimeToFinish ::operator()(const Project* t1, const Project* t2) { return t1->weeksToFinish() < t2->weeksToFinish(); }
string Project::ProjectComparatorTimeToFinish::getAbbreviation() const{ return "Est finish"; }

