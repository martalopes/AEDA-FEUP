#include "CV.h"
int CV::lastID = 0;
CV::CV() : ID(0), previously_employed(false), experience(0), num_skills(0){}
CV::CV(string name, string contact, string address, string title, bool previously_employed, size_t experience, size_t num_skills): name(name), contact(contact), address(address), title(title), previously_employed(previously_employed), experience(experience), num_skills(num_skills), ID(++lastID){};
CV::CV(int i)
{
	string nam = "Name " + to_string(i);
	string tit;
	string cont = "Contact " + to_string(i);
	string addr = "Address " + to_string(i);
	bool p_e = false;
	size_t exp;
	size_t n_s;
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		tit = "Programmer";
		break;
	case 1:
		tit = "Architect";
		break;
	case 2:
		tit = "Manager";
		break;
	case 3:
		tit = "Tester";
		break;
	default:
		break;
	}
	if (rand() % 20 == 0)
		p_e = true;
	exp = rand() % 20;
	n_s = rand() % 10 + 1;
	*this = CV(nam, cont, addr, tit, p_e, exp, n_s);
}
string CV::getTitle() const
{
	return this->title;
}
string CV::getName() const
{
	return this->name;
}
string CV::getContact() const
{
	return this->contact;
}
string CV::getAddress() const
{
	return this->address;
}
bool CV::getPreviouslyEmployed() const
{
	return this->previously_employed;
}
size_t CV::getExperience() const
{
	return this->experience;
}
size_t CV::getNumSkills() const
{
	return this->num_skills;
}
void CV::setTitle(string newTitle)
{
	this->title = newTitle;
}
void CV::setName(string newName)
{
	this->name = newName;
}
void CV::setContact(string newContact)
{
	this->contact = newContact;
}
void CV::setAddress(string newAddress)
{
	this->address = newAddress;
}
void CV::setPreviouslyEmployed(bool newPE)
{
	this->previously_employed = newPE;
}
void CV::setExperience(size_t newExp)
{
	this->experience = newExp;
}
void CV::setNumSkills(size_t newNumSkills)
{
	this->num_skills = newNumSkills;
}

Collaborator* CV::toCollaborator(int maxWeeklyHours) const
{
	if (title == "Programmer")
		return new Programmer(name, contact, address, maxWeeklyHours);
	else if (title == "Architect")
		return new Architect(name, contact, address, maxWeeklyHours);
	else if (title == "Manager")
		return new Manager(name, contact, address, maxWeeklyHours);
	else if (title == "Tester")
		return new Tester(name, contact, address, maxWeeklyHours);
	else return NULL;
}


ostream & operator<<(ostream& out, const CV& c)
{
	out << c.ID << endl;
	out << c.title << endl;
	out << c.name << endl;
	out << c.address << endl;
	out << c.contact << endl;
	out << c.previously_employed << endl;
	out << c.experience << endl;
	out << c.num_skills << endl;
	return out;
}
istream & operator>>(istream& in, CV& c)
{
	in >> c.ID;
	in.ignore();
	if (c.ID > CV::lastID)
		CV::lastID = c.ID;
	getline(in, c.title);
	getline(in, c.name);
	getline(in, c.address);
	getline(in, c.contact);
	in >> c.previously_employed;
	in.ignore();
	in >> c.experience;
	in.ignore();
	in >> c.num_skills;
	in.ignore();
	return in;
}
string CV::toString() const
{
	return normalize(to_string(ID), name, 30);
}
bool CV::operator==(const CV& c2) const
{
	return this->ID == c2.ID;
}
int CV::getValue() const
{
	return previously_employed * 1000 + experience * 5 + num_skills * 3;
}