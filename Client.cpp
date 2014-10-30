#include "Client.h"



void Client::addProject(Project* proj, bool setClient)
	{
		for(size_t i = 0; i< projects.size(); ++i)
			if(*projects.at(i) == *proj)
				throw ClientExcept("Project already exists");
		projects.push_back(proj);
		if (setClient)
			proj->setClient(this, false);
	};
ostream & operator<<(ostream& out, const Client& c)
{
	out << c.ID << endl;
	out << c.name << endl;
	out << c.projects.size() << endl;
	for (size_t i = 0; i < c.projects.size(); i++)
		out << c.projects.at(i)->getID() << endl;
	out << endl;
	return out;
}

istream & operator>>(istream& in, Client& c)
{
	in >> c.ID;
	in.ignore();
	getline(in,c.name);
	int numprojects = 0;
	in >> numprojects;
	for (size_t i = 0; i < numprojects; i++)
	{
		unsigned long int projectid = 0;
		in >> projectid;
		in.ignore();
		c.projects.push_back((Project*) projectid);
	}
	string s;
	in >> s;
	return in;
}
void Client::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
		if (ptr != NULL)
		projects.at(i) = ptr;
	}
}


int Client::lastID = 0;
