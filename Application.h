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
#include <iostream>
#include <stdlib.h>


using namespace std;

class Application
{
public:
	bool menor(int i, int n)
	{
		return i < n;
	}
	Application()
	{
		vector<int> v;
		for(int i = 0; i < 1000; i++)
			ordered_push_back_ptr(v,rand()%1000, menor);
		for(int i = 0; i < v.size(); i++)
			cout << v[i]<< " ";
	};
	void tick()
	{
		for(int i = 0; i < projects.size(); ++i)
			projects.at(i)->tick();
	}
	vector<Project*> getProjects() const {return projects;};
	vector<Client*> getClients() const {return clients;};
	vector<Collaborator*> getCollaborators() const {return collaborators;};
	vector<Task*> getTasks() const {return tasks;};


private:
	template<class T,class C> void ordered_push_back_ptr(vector<T> v, T t, C less)
	{
		if (v.size() == 0) v.push_back(t);
		size_t i = 0;
		for( ; less(t, v.at(i)); ++i){}
		v.push_back(v.at(v.size()-1));
		for(size_t j = v.size()-2; j > i; ++j)
			v.at(j) = v.at(j-1);
		v.at(i)=t;
	}
	vector<Project*> projects;
	vector<Client*> clients;
	vector<Collaborator*> collaborators;
	vector<Task*> tasks;
};



#endif
