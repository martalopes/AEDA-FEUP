#include "Client.h"

int Client::lastID = 0;


bool Client::addProject(Project* proj, bool setClient)
	{
	if (proj == NULL)
		throw Client::ClientExcept("Invalid Project being added to Client");
	if (proj->getClient() != NULL)
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
	out << c.password << endl;
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
	getline(in, c.password);
	return in;
}
double Client::getTotal() const 
{ 
	double sum = 0; 
	for (size_t i = 0; i < projects.size(); i++) 
		sum += projects.at(i)->getCost(); 
	return sum;
}
string Client::toString() const
{
	return normalize(to_string(ID), name, 30);
};