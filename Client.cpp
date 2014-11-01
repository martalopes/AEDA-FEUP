#include "Client.h"

int Client::lastID = 0;


void Client::addProject(Project* proj, bool setClient)
	{
		for(size_t i = 0; i< projects.size(); ++i)
			if(*projects.at(i) == *proj)
				throw ClientExcept("Project already exists");
		projects.push_back(proj);
		if (setClient)
			proj->setClient(this, false);
	};
void Client::connect()
{
	for (size_t i = 0; i < projects.size(); i++)
	{
		Project * ptr = Application::getProjectPtr((int)projects.at(i));
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
