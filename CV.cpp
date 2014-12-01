#include "CV.h"

//ostream & operator<<(ostream& out, const Collaborator& c)
//{
//	out << c.getTitle() << endl;
//	out << c.ID << endl;
//	out << c.name << endl;
//	out << c.address << endl;
//	out << c.contact << endl;
//	out << c.maxweeklyhours << endl;
//	out << c.workinghours << endl;
//	out << c.projects.size() << endl;
//	for (size_t i = 0; i < c.projects.size(); i++)
//		out << c.projects.at(i)->getID() << endl;
//	out << c.tasks.size() << endl;
//	for (size_t i = 0; i < c.tasks.size(); i++)
//		out << c.tasks.at(i).first->getID() << " " << c.tasks.at(i).second << endl;
//	out << c.finishedtasks.size() << endl;
//	for (size_t i = 0; i < c.finishedtasks.size(); i++)
//		out << c.finishedtasks.at(i)->getID() << endl;
//	return out;
//}
//istream & operator>>(istream& in, Collaborator& c)
//{
//	in >> c.ID;
//	in.ignore();
//	if (c.ID > Collaborator::lastID)
//		Collaborator::lastID = c.ID;
//	getline(in, c.name);
//	getline(in, c.address);
//	getline(in, c.contact);
//	in >> c.maxweeklyhours;
//	in.ignore();
//	in >> c.workinghours;
//	in.ignore();
//	unsigned int numprojects = 0;
//	in >> numprojects;
//	in.ignore();
//	for (size_t i = 0; i < numprojects; i++)
//	{
//		unsigned long int projectid;
//		in >> projectid;
//		in.ignore();
//		c.projects.push_back((Project*)projectid);
//	}
//	unsigned int numtasks = 0;
//	in >> numtasks;
//	in.ignore();
//	for (size_t i = 0; i < numtasks; i++)
//	{
//		unsigned long int taskid = 0;
//		unsigned int hours = 0;
//		in >> taskid >> hours;
//		in.ignore();
//		c.tasks.push_back(make_pair((Task*)taskid, hours));
//	}
//	unsigned int numfinishedtasks = 0;
//	in >> numfinishedtasks;
//	in.ignore();
//	for (size_t i = 0; i < numfinishedtasks; i++)
//	{
//		unsigned long int taskid = 0;
//		in >> taskid;
//		in.ignore();
//		c.finishedtasks.push_back((Task*)taskid);
//	}
//	return in;
//}