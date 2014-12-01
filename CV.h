#ifndef CV_H
#define CV_H

#include "Task.h"
#include "Collaborator.h"
#include "Client.h"
#include "Date.h"
#include "Application.h"
#include "Menu.h"

#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class CV
{
	int ID;
	Collaborator* candidate;
	bool previously_employed;
	size_t experience;
	size_t num_skills;
public:
	CV(Collaborator* c, bool p_e, size_t exp, size_t n);
	CV(Collaborator* c);
	friend ostream & operator<<(ostream& out, const CV& c);
	friend istream & operator>>(istream& in, CV& c);
};



#endif