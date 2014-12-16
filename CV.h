#ifndef CV_H
#define CV_H

#include "Collaborator.h"
#include "Menu.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Collaborator;

class CV
{
	static int lastID;
	int ID;
	string title;
	string name;
	string contact;
	string address;
	bool previously_employed;
	size_t experience;
	size_t num_skills;
public:
	CV();
	CV(string name, string contact, string address, string title, bool previously_employed, size_t experience, size_t num_skills);
	CV(int i);
	int getID()const;
	string getTitle() const;
	string getName() const;
	string getContact() const;
	string getAddress() const;
	bool getPreviouslyEmployed() const;
	size_t getExperience() const;
	size_t getNumSkills() const;

	string toString() const;

	void setTitle(string newTitle);
	void setName(string newName);
	void setContact(string newContact);
	void setAddress(string newAddress);
	void setPreviouslyEmployed(bool newPE);
	void setExperience(size_t newExp);
	void setNumSkills(size_t newNumSkills);

	Collaborator* toCollaborator(int maxWorkingHours)const;

	friend ostream & operator<<(ostream& out, const CV& c);
	friend istream & operator>>(istream& in, CV& c);
	bool operator< (const CV& c2) const;
	bool operator==(const CV& c2) const;

	int getValue() const;
};




#endif