#ifndef APPLICATION_H
#define APPLICATION_H


#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"

#include <string>
#include <utility>
#include <vector>


using namespace std;

class Application
{
public:

private:
	vector<Project*> projects;
	vector<Client*> clients;
	vector<Collaborator*> collaborators;
	vector<Task*> tasks;


};

#endif