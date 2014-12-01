#include "Collaborator.h"
#include "Task.h"


int Collaborator::lastID = 0;
Collaborator::Collaborator() :ID(0), maxweeklyhours(0), workinghours(0){}
Collaborator::Collaborator(string name, int maxweeklyhours) : name(name), maxweeklyhours(maxweeklyhours), ID(++lastID), workinghours(0){}
Collaborator::Collaborator(string name, int maxweeklyhours, int setID) : name(name), maxweeklyhours(maxweeklyhours), workinghours(0){ if (setID > lastID) lastID = setID; }

Collaborator::Collaborator(int i)
{
	stringstream s;
	s << "Collaborator " << i;
	*this = Collaborator(s.str(), (6 + rand() % 4) * 5);
	stringstream contact_stream;
	contact_stream << "Contact " << i;
	stringstream address_stream;
	address_stream << "Address " << i;
	this->contact = contact_stream.str();
	this->address = address_stream.str();
}

int Collaborator::getID() const { return this->ID; }
string Collaborator::getName() const { return this->name; }
int Collaborator::getWorkingHours() const { return  this->workinghours; }
int Collaborator::getMaxWeeklyHours() const { return this->maxweeklyhours; }
vector<Project*> Collaborator::getProjects() const { return this->projects; }
vector<pair<Task*, unsigned int> > Collaborator::getTasks() const { return this->tasks; }
vector<Task*> Collaborator::getFinishedTasks() const { return this->finishedtasks; }
double  Collaborator::getCost() const{ return 0; }
string  Collaborator::getTitle() const{ return "Collaborator"; }
void Collaborator::setName(string newname){ this->name = newname; }
void Collaborator::setWeeklyHours(int newhours) { this->maxweeklyhours = newhours; }
bool Collaborator::operator==(const Collaborator& c2)const{ return this->ID == c2.ID; }
void Collaborator::updateProjects() { projects = calculateProjects(); }

bool Collaborator::addTask(Task* t1, unsigned int hours, bool addCollaborator)
{
	if (t1 == NULL)
		throw CollaboratorExcept("Invalid Task being added to Collaborator");
	if (t1->isCompleted())
	{
		for (size_t i = 0; i < finishedtasks.size(); i++)
		{
			if (*finishedtasks.at(i) == *t1)
				return false;
		}
		finishedtasks.push_back(t1);
		projects = calculateProjects();
		return true;
	}
	for (size_t i = 0; i < this->tasks.size(); ++i)
	{
		if (*(tasks[i].first) == *t1)
		{
			return false;
		}
	}
	if ((this->getWorkingHours() + hours) > this->maxweeklyhours)
		return false;
	tasks.push_back(make_pair(t1, hours));
	updateProjects();
	if (addCollaborator)
		t1->addCollaborator(this, hours, false);
	workinghours += hours;
	return true;
}
bool Collaborator::removeTask(Task* t, bool removeCollaborator)
{
	if (t == NULL)
		throw CollaboratorExcept("Invalid task");
	for (size_t i = 0; i < tasks.size(); ++i)
	if (tasks.at(i).first == t)
	{
		workinghours -= tasks.at(i).second;
		tasks.erase(tasks.begin() + i);
		updateProjects();
		if (removeCollaborator)
			return t->removeCollaborator(this, false);
		return true;
	}
	for (size_t i = 0; i < finishedtasks.size(); i++)
	{
		if (finishedtasks.at(i) == t)
		{
			finishedtasks.erase(finishedtasks.begin() + i);
			updateProjects();
			if (removeCollaborator)
				return t->removeCollaborator(this, false);
			return true;
		}
	}
	return false;
}

bool Collaborator::changeTaskHours(Task* t1, unsigned int hours)
{
	for (size_t i = 0; i < this->tasks.size(); ++i)
	{
		if (*tasks[i].first == *t1)
		{
			if (workinghours - tasks[i].second + hours > maxweeklyhours)
				return false;
			else tasks[i].second = hours;
			workinghours = workinghours - tasks[i].second + hours;
		}
	}
	return false;
}
string Collaborator::toString() const
{
	return normalize(to_string(ID), name, 30);
}

void Collaborator::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		if ((int)projects.at(i) == 0)
			continue;
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
		if (ptr == NULL)
			throw CollaboratorExcept("Error in collaborator.txt");
		projects.at(i) = ptr;
	}
	for (size_t i = 0; i < tasks.size(); i++)
	{
		if ((int)tasks.at(i).first == 0)
			continue;
		Task* ptr = Application::getTaskPtr((int)tasks.at(i).first);
		if (ptr == NULL)
			throw CollaboratorExcept("Error in collaborator.txt");
		tasks.at(i).first = ptr;
	}
}

bool Collaborator::removeTrace()
{
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i).first->removeCollaborator(this, false);
	}
	return true;
}

void Collaborator::leave()
{
	vector<Project*> pr;
	pr = calculateProjects();
	for (size_t i = 0; i < tasks.size(); i++)
	{
		tasks.at(i).first->removeCollaborator(this);
	}
	this->projects = pr;
}

void Collaborator::reinstate()
{
	this->projects = calculateProjects();
}
//bool CollaboratorEqual::operator()(Collaborator* const c1, Collaborator* const c2) const
//{
//	return  *c1 == *c2;
//}
//size_t CollaboratorHash::operator()(Collaborator* const c) const
//{
//	return (size_t)c->getID();
//}
ostream & operator<<(ostream& out, const Collaborator& c)
{
	out << c.getTitle() << endl;
	out << c.ID << endl;
	out << c.name << endl;
	out << c.address << endl;
	out << c.contact << endl;
	out << c.maxweeklyhours << endl;
	out << c.workinghours << endl;
	out << c.projects.size() << endl;
	for (size_t i = 0; i < c.projects.size(); i++)
		out << c.projects.at(i)->getID() << endl;
	out << c.tasks.size() << endl;
	for (size_t i = 0; i < c.tasks.size(); i++)
		out << c.tasks.at(i).first->getID() << " " << c.tasks.at(i).second << endl;
	out << c.finishedtasks.size() << endl;
	for (size_t i = 0; i < c.finishedtasks.size(); i++)
		out << c.finishedtasks.at(i)->getID() << endl;
	return out;
}
istream & operator>>(istream& in, Collaborator& c)
{
	in >> c.ID;
	in.ignore();
	if (c.ID > Collaborator::lastID)
		Collaborator::lastID = c.ID;
	getline(in, c.name);
	getline(in, c.address);
	getline(in, c.contact);
	in >> c.maxweeklyhours;
	in.ignore();
	in >> c.workinghours;
	in.ignore();
	unsigned int numprojects = 0;
	in >> numprojects;
	in.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		unsigned long int projectid;
		in >> projectid;
		in.ignore();
		c.projects.push_back((Project*)projectid);
	}
	unsigned int numtasks = 0;
	in >> numtasks;
	in.ignore();
	for (size_t i = 0; i < numtasks; i++)
	{
		unsigned long int taskid = 0;
		unsigned int hours = 0;
		in >> taskid >> hours;
		in.ignore();
		c.tasks.push_back(make_pair((Task*)taskid, hours));
	}
	unsigned int numfinishedtasks = 0;
	in >> numfinishedtasks;
	in.ignore();
	for (size_t i = 0; i < numfinishedtasks; i++)
	{
		unsigned long int taskid = 0;
		in >> taskid;
		in.ignore();
		c.finishedtasks.push_back((Task*)taskid);
	}
	return in;
}

bool Collaborator::reassign(Task* t)
{
	if (!removeTask(t, false))
		return false;
	finishedtasks.push_back(t);
}

Collaborator* Collaborator::newRandomCollaborator(int i)
{
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		return new Programmer(i);
		break;
	case 1:
		return new Architect(i);
		break;
	case 2:
		return new Manager(i);
		break;
	case 3:
		return new Tester(i);
		break;
	default:
		return NULL;
		break;
	}
}

Collaborator* Collaborator::newCollaboratorTitle(string title)
{
	if ("Programmer" == title)
		return new Programmer();
	if ("Architect" == title)
		return new Architect();
	if ("Manager" == title)
		return new Manager();
	if ("Tester" == title)
		return new Tester();
	return NULL;
}
vector<Project*> Collaborator::calculateProjects()const
{
	vector<Project*> out;
	for (size_t i = 0; i < tasks.size(); i++)
	{
		if (tasks.at(i).first->getProject() != NULL)
		if (find(out.begin(), out.end(), tasks.at(i).first->getProject()) == out.end())
			out.push_back(tasks.at(i).first->getProject());
	}
	for (size_t i = 0; i < finishedtasks.size(); i++)
	{
		if (finishedtasks.at(i)->getProject() != NULL)
		if (find(out.begin(), out.end(), finishedtasks.at(i)->getProject()) == out.end())
			out.push_back(finishedtasks.at(i)->getProject());
	}
	return out;
}
Collaborator::CollaboratorExcept::CollaboratorExcept(string description) :description(description){}
string  Collaborator::CollaboratorExcept::operator()(){ return description; }

bool Collaborator::CollaboratorComparatorAlphabetic ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.name < t2.name; }
bool Collaborator::CollaboratorComparatorAlphabetic ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->name < t2->name; }
string Collaborator::CollaboratorComparatorAlphabetic::getAbbreviation() const{ return "Alph"; }

bool Collaborator::CollaboratorComparatorCost ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.workinghours < t2.workinghours; }
bool Collaborator::CollaboratorComparatorCost ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->workinghours < t2->workinghours; }
string Collaborator::CollaboratorComparatorCost::getAbbreviation() const{ return "Cost"; }

bool Collaborator::CollaboratorComparatorID :: operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getID() < t2.getID(); }
bool Collaborator::CollaboratorComparatorID :: operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getID() < t2->getID(); }
string Collaborator::CollaboratorComparatorID::getAbbreviation() const{ return "ID"; }

bool  Collaborator::CollaboratorComparatorWorkinghours ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getWorkingHours() < t2.getWorkingHours(); }
bool Collaborator::CollaboratorComparatorWorkinghours ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getWorkingHours() < t2->getWorkingHours(); }
string Collaborator::CollaboratorComparatorWorkinghours::getAbbreviation() const{ return "Wrk Hrs"; }

bool  Collaborator::CollaboratorComparatorMaxWeeklyHours ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getMaxWeeklyHours() < t2.getMaxWeeklyHours(); }
bool Collaborator::CollaboratorComparatorMaxWeeklyHours ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getMaxWeeklyHours() < t2->getMaxWeeklyHours(); }
string Collaborator::CollaboratorComparatorMaxWeeklyHours::getAbbreviation() const{ return "Week Hrs"; }

bool Collaborator::CollaboratorComparatorNumTasks ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getTasks().size() < t2.getTasks().size(); }
bool Collaborator::CollaboratorComparatorNumTasks ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getTasks().size() < t2->getTasks().size(); }
string Collaborator::CollaboratorComparatorNumTasks::getAbbreviation() const{ return "N. Tasks"; }

bool Collaborator::CollaboratorComparatorExperience ::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getFinishedTasks().size() < t2.getFinishedTasks().size(); }
bool Collaborator::CollaboratorComparatorExperience ::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getFinishedTasks().size() < t2->getFinishedTasks().size(); }
string Collaborator::CollaboratorComparatorExperience::getAbbreviation() const{ return "Exp"; }

bool Collaborator::CollaboratorComparatorNumProjects::operator()(const Collaborator& t1, const Collaborator& t2) { return t1.getProjects().size() < t2.getProjects().size(); }
bool Collaborator::CollaboratorComparatorNumProjects::operator()(const Collaborator* t1, const Collaborator* t2) { return t1->getProjects().size() < t2->getProjects().size(); }
string Collaborator::CollaboratorComparatorNumProjects::getAbbreviation() const{ return "N. Proj"; }

Programmer::Programmer(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){}
Programmer::Programmer(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; }
Programmer::Programmer(int i) : Collaborator(i){}
Programmer::Programmer() : Collaborator(){}
double Programmer::getCost() const { return PROGRAMMER_COST; }
string Programmer::getTitle() const{ return "Programmer"; }


Architect::Architect(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){}
Architect::Architect(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; }
Architect::Architect(int i) : Collaborator(i){}
Architect::Architect() : Collaborator(){}
double Architect::getCost() const { return ARCHITECT_COST; }
string Architect::getTitle() const{ return "Architect"; }

Manager::Manager(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){}
Manager::Manager(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; }
Manager::Manager(int i) : Collaborator(i){}
Manager::Manager() : Collaborator(){}
double Manager::getCost() const { return MANAGER_COST; }
string Manager::getTitle() const{ return "Manager"; }

Tester::Tester(string name, int maxweeklyhours) : Collaborator(name, maxweeklyhours){}
Tester::Tester(string name, int maxweeklyhours, int setID) : Collaborator(name, maxweeklyhours, setID){ if (setID > Collaborator::lastID) Collaborator::lastID = setID; }
Tester::Tester(int i) : Collaborator(i){}
Tester::Tester() : Collaborator(){}
double Tester::getCost() const { return TESTER_COST; }
string Tester::getTitle() const{ return "Tester"; }