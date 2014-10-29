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
int Client::lastID = 0;
