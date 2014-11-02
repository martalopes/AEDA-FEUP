#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <iostream>
#include <ctime>
#include <assert.h>

using namespace std;

void test()
{
	Application a;
	Client* c1 = new Client("Client 1");
	a.addClient(c1);
	Client* c2 = new Client("Client 2");
	a.addClient(c2);
	Programmer* w1 = new Programmer("Programmer 1", 40);
	a.addCollaborator(w1);
	Tester* w2 = new Tester("Tester 1", 35);
	a.addCollaborator(w2);
	Project* p1 = new Project("Project 1", "Description of Project 1", Date(1, 11,2014, 12, 12, 3) ,0);
	a.addProject(p1);
	Project* p2 = new Project("Project 2", "Description of Project 2", Date(1, 10, 2014, 12, 12, 3), 0);
	a.addProject(p2);
	c1->addProject(p1);
	c2->addProject(p2);
	Task* t1 = new Task("Task 1", "Description of Task 1", 10);
	Task* t2 = new Task("Task 2", "Description of Task 2", 20);
	Task* t3 = new Task("Task 3", "Description of Task 3", 30);
	Task* t4 = new Task("Task 4", "Description of Task 4", 40);
	a.addTask(t1);
	a.addTask(t2);
	a.addTask(t3);
	a.addTask(t4);
	p1->addTask(t1);
	p1->addTask(t2);
	p2->addTask(t3);
	p2->addTask(t4);
	t2->addDependency(t1);
	t4->addDependency(t3);
	assert(!t3->addDependency(t1));
	t1->addCollaborator(w1, 5);
	t1->addCollaborator(w2, 10);
	t2->addCollaborator(w1, 15);

	t3->addCollaborator(w2, 20);
	int x2 = 0;
}


int main()
{
	srand((unsigned int)time(NULL));
	test();
	//Application a;
	/*if (0)
	{
		a.genApplication();
		a.writeFiles();
		return 0;
	}*/
	//string cmd;
	//getline(cin,cmd);
	//if (cmd == "gen")
	//a.genApplication();
	//else if (cmd == "read")



	/*a.readFiles();
	a.createMenus();
	a.play();
	a.writeFiles();*/
	int x = 0;
	system("pause");
}
