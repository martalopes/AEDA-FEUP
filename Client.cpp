#include "Client.h"

int Client::lastID = 0;

Client::Client() :ID(0), fiscal(0){}
Client::Client(string name) :name(name), ID(++lastID),fiscal(0){}
Client::Client(int fiscal, string name) : name(name), ID(++lastID), fiscal(fiscal){}
Client::Client(string name, int setID) :name(name), ID(setID), fiscal(0) { if (setID > lastID) lastID = setID; }
Client::Client(int i)
{
	stringstream s1, s2;
	s1 << "Name " << i;
	*this = Client(rand() % 1000000, s1.str());
}
string Client::getName() const { return this->name; }
vector<Project*> Client::getProjects() const { return this->projects; }
int Client::getID()const { return ID; }
void Client::setName(string name) { this->name = name; }
bool Client::operator==(const Client& c2) const { return this->ID == c2.ID; }
Client::ClientExcept::ClientExcept(string description) :description(description){}
string  Client::ClientExcept::operator()(){ return description; }
bool Client::addProject(Project* proj, bool setClient)
	{
	if (proj == NULL)
		throw Client::ClientExcept("Invalid Project being added to Client");
	if (proj->getClient() != NULL)
		if(!(*proj->getClient() == *this))
		return false;
		for(size_t i = 0; i< projects.size(); ++i)
			if(*projects.at(i) == *proj)
				throw ClientExcept("Project already exists");
		projects.push_back(proj);
		if (setClient)
			proj->setClient(this, false);
		return true;
	};
bool Client::removeProject(Project* p, bool removeClient)
{
	if (p == NULL)
		throw ClientExcept("Invalid project");
	for (size_t i = 0; i < projects.size(); i++)
	{
		if (*projects.at(i) == *p)
		{
			projects.erase(projects.begin() + i);
			if (removeClient)
				return p->removeClient(false);
			return true;
		}
	}
	return false;
}
void Client::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		if ((int)projects.at(i) == 0)
			continue;
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
		if (ptr == NULL)
			throw ClientExcept("Error in clients.txt");
		projects.at(i) = ptr;
	}
}
ostream & operator<<(ostream& out, const Client& c)
{
	out << c.ID << endl;
	out << c.name << endl;
	out << c.projects.size() << endl;
	for (size_t i = 0; i < c.projects.size(); i++)
		out << c.projects.at(i)->getID() << endl;
	return out;
}
istream & operator>>(istream& in, Client& c)
{
	in >> c.ID;
	in.ignore();
	if (c.ID > Client::lastID)
		Client::lastID = c.ID;
	getline(in, c.name);
	unsigned int numprojects = 0;
	in >> numprojects;
	in.ignore();
	for (size_t i = 0; i < numprojects; i++)
	{
		unsigned long int projectid = 0;
		in >> projectid;
		in.ignore();
		c.projects.push_back((Project*)projectid);
	}
	return in;
}
double Client::getTotal() const 
{ 
	double sum = 0; 
	for (size_t i = 0; i < projects.size(); i++) 
		sum += projects.at(i)->getCost(); 
	return sum;
}
int Client::getFiscal()const
{
	return this->fiscal;
}
void Client::setFiscal(int newfiscal)
{
	this->fiscal = newfiscal;
}
string Client::toString() const
{
	return normalize(to_string(ID), name, 30);
};
bool Client::ClientComparatorID ::operator()(const Client& c1, const Client& c2){ return c1.getID() < c2.getID(); }
bool Client::ClientComparatorID ::operator()(const Client* c1, const Client* c2){ return c1->getID() < c2->getID(); }
string Client::ClientComparatorID::getAbbreviation() const { return "ID"; }
bool  Client::ClientComparatorAlphabetic ::operator()(const Client& c1, const Client& c2){ return c1.getName() < c2.getName(); }
bool Client::ClientComparatorAlphabetic ::operator()(const Client* c1, const Client* c2){ return c1->getName() < c2->getName(); }
string Client::ClientComparatorAlphabetic::getAbbreviation() const { return "Alph"; }
bool Client::ClientComparatorNumProjects ::operator()(const Client& c1, const Client& c2){ return c1.getProjects().size() < c2.getProjects().size(); }
bool Client::ClientComparatorNumProjects ::operator()(const Client* c1, const Client* c2){ return c1->getProjects().size() < c2->getProjects().size(); }
string Client::ClientComparatorNumProjects::getAbbreviation() const { return "N Proj"; }
bool Client::ClientComparatorTotal ::operator()(const Client& c1, const Client& c2){ return c1.getTotal() < c2.getTotal(); }
bool Client::ClientComparatorTotal ::operator()(const Client* c1, const Client* c2){ return c1->getTotal() < c2->getTotal(); }
string Client::ClientComparatorTotal::getAbbreviation() const { return "Total"; }
bool Client::operator < (const Client& c2) const
{
	double total1 = 0; 
	double total2 = 0;
	int numprojects1 = 0;
	int numprojects2 = 0;
	for (size_t i = 0; i < this->getProjects().size(); i++)
	{
		if (this->getProjects().at(i)->isCompleted())
		{
			numprojects1++;
			total1 += this->getProjects().at(i)->getCost();
		}
	}
	for (size_t i = 0; i < c2.getProjects().size(); i++)
	{
		if (c2.getProjects().at(i)->isCompleted())
		{
			numprojects2++;
			total2 += c2.getProjects().at(i)->getCost();
		}
	}
	if (total1 == total2 && numprojects1 == numprojects2)
		return this->ID < c2.ID;
	if (total1 == total2)
		return numprojects1 > numprojects2;
	else return total1 > total2;
	return false;
}