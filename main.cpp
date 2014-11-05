#include "Project.h"
#include "Client.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"

#include <iostream>
#include <ctime>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <algorithm>

using namespace std;

#define ASSERT_EQUAL_DELTA(arg1, arg2, delta) assert(abs(arg1-arg2) < delta)
#define ASSERT_EQUAL(arg1,arg2) assert(arg1==arg2)

//void test()
//{
//	Application a;
//	Client* c1 = new Client("Client 1");
//	a.addClient(c1);
//	Client* c2 = new Client("Client 2");
//	a.addClient(c2);
//	Programmer* w1 = new Programmer("Programmer 1", 40);
//	a.addCollaborator(w1);
//	Tester* w2 = new Tester("Tester 1", 35);
//	a.addCollaborator(w2);
//	Project* p1 = new Project("Project 1", "Description of Project 1", Date(1, 11,2014, 12, 12, 3) ,0);
//	a.addProject(p1);
//	Project* p2 = new Project("Project 2", "Description of Project 2", Date(1, 10, 2014, 12, 12, 3), 0);
//	a.addProject(p2);
//	c1->addProject(p1);
//	c2->addProject(p2);
//	Task* t1 = new Task("Task 1", "Description of Task 1", 100);
//	Task* t2 = new Task("Task 2", "Description of Task 2", 200);
//	Task* t3 = new Task("Task 3", "Description of Task 3", 300);
//	Task* t4 = new Task("Task 4", "Description of Task 4", 400);
//	a.addTask(t1);
//	a.addTask(t2);
//	a.addTask(t3);
//	a.addTask(t4);
//	p1->addTask(t1);
//	p1->addTask(t2);
//	p2->addTask(t3);
//	p2->addTask(t4);
//	t2->addDependency(t1);
//	t4->addDependency(t3);
//	assert(!t3->addDependency(t1));
//	t1->addCollaborator(w1, 5);
//	t1->addCollaborator(w2, 10);
//	t2->addCollaborator(w1, 15);
//
//	t3->addCollaborator(w2, 20);
//	//cout << t2->calculateTimeToCompletion();
//	int x2 = 0;
//}
//
//void test2()
//{
//	Application a;
//	Client* c1 = new Client("Client 1");
//	a.addClient(c1);
//	Client* c2 = new Client("Client 2");
//	a.addClient(c2);
//	Programmer* w1 = new Programmer("Programmer 1", 1000);
//	a.addCollaborator(w1);
//	Tester* w2 = new Tester("Tester 1", 1000);
//	a.addCollaborator(w2);
//	Manager* w3 = new Manager("Manager 1", 1000);
//	a.addCollaborator(w3);
//	Architect* w4 = new Architect("Architect 1", 1000);
//	a.addCollaborator(w4);
//
//	Project* p1 = new Project("Project 1", "Description of Project 1", Date(1, 11, 2014, 12, 12, 3), 0);
//	a.addProject(p1);
//	Project* p2 = new Project("Project 2", "Description of Project 2", Date(1, 10, 2014, 12, 12, 3), 0);
//	a.addProject(p2);
//	c1->addProject(p1);
//	c2->addProject(p2);
//	Task* t1 = new Task("Task 1", "Description of Task 1", 26);
//	Task* t2 = new Task("Task 2", "Description of Task 2", 55);
//	Task* t3 = new Task("Task 3", "Description of Task 3", 148);
//	Task* t4 = new Task("Task 4", "Description of Task 4", 156);
//	Task* t5 = new Task("Task 5", "Description of Task 5", 91);
//	Task* t6 = new Task("Task 6", "Description of Task 6", 171);
//	a.addTask(t1);
//	a.addTask(t2);
//	a.addTask(t3);
//	a.addTask(t4);
//	a.addTask(t5);
//	a.addTask(t6);
//	p1->addTask(t1);
//	p1->addTask(t2);
//	p1->addTask(t3);
//	p1->addTask(t4);
//	p1->addTask(t5);
//	p1->addTask(t6);
//	t1->addCollaborator(w1, 6);
//	t1->addCollaborator(w2, 8);
//
//	t2->addCollaborator(w1, 7);
//
//	t3->addCollaborator(w2, 15);
//	t3->addCollaborator(w4, 17);
//
//	t4->addCollaborator(w1, 10);
//
//	t5->addCollaborator(w2, 13);
//
//	t6->addCollaborator(w1, 3);
//	t6->addCollaborator(w3, 20);
//	t6->addCollaborator(w2, 7);
//
//	t1->addDependant(t4);
//	t2->addDependant(t4);
//	t3->addDependant(t4);
//
//	t2->addDependant(t5);
//	t3->addDependant(t5);
//
//	t5->addDependant(t4);
//
//	t4->addDependant(t6);
//	t5->addDependant(t6);
//
//	ASSERT_EQUAL(p1->getClient()->getID(), c1->getID());
//
//	ASSERT_EQUAL(t1->getDependants().size(), 1);
//	ASSERT_EQUAL(t2->getDependants().size(), 2);
//	ASSERT_EQUAL(t3->getDependants().size(), 2);
//	ASSERT_EQUAL(t4->getDependants().size(), 1);
//	ASSERT_EQUAL(t5->getDependants().size(), 2);
//	ASSERT_EQUAL(t6->getDependants().size(), 0);
//
//	ASSERT_EQUAL(t1->getDependencies().size(), 0);
//	ASSERT_EQUAL(t2->getDependencies().size(), 0);
//	ASSERT_EQUAL(t3->getDependencies().size(), 0);
//	ASSERT_EQUAL(t4->getDependencies().size(), 4);
//	ASSERT_EQUAL(t5->getDependencies().size(), 2);
//	ASSERT_EQUAL(t6->getDependencies().size(), 2);
//
//	ASSERT_EQUAL(w1->getTasks().size(), 4);
//	ASSERT_EQUAL(w2->getTasks().size(), 4);
//	ASSERT_EQUAL(w3->getTasks().size(), 1);
//	ASSERT_EQUAL(w4->getTasks().size(), 1);
//
//	ASSERT_EQUAL(t1->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t2->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t3->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t4->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t5->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t6->getCollaborators().size(), 3);
//
//	ASSERT_EQUAL_DELTA(t1->calculateEstimatedTime(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateEstimatedTime(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateEstimatedTime(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t4->calculateEstimatedTime(), 15.6, .1);
//	ASSERT_EQUAL_DELTA(t5->calculateEstimatedTime(), 7, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateEstimatedTime(), 5.7, .1);
//
//	ASSERT_EQUAL_DELTA(t1->calculateTimeToCompletion(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateTimeToCompletion(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateTimeToCompletion(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t4->calculateTimeToCompletion(), 30.452, .1);
//	ASSERT_EQUAL_DELTA(t5->calculateTimeToCompletion(), 14.852, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateTimeToCompletion(), 36.152, .1);
//	ASSERT_EQUAL((Date() + t6->calculateTimeToCompletion() * 24 * 7 * 3600).getTotalSeconds(), p1->projectedFinishDate(Date()).getTotalSeconds());
//	
//	ASSERT_EQUAL(p1->getTasks().size(),6);
//	ASSERT_EQUAL(p1->getCollaborators().size(), 4);
//	
//	try { a.removeTask(t5); }
//	catch (...)
//	{
//		ASSERT_EQUAL(1, 0);
//	}
//	ASSERT_EQUAL(p1->getTasks().size(), 5);
//	try { a.removeTask(t5); }
//	catch (Application::ApplicationExcept& e)
//	{
//		ASSERT_EQUAL(e(), "Task being removed does not exist");
//	}
//	ASSERT_EQUAL(a.getTasks().size(), 5);
//
//	ASSERT_EQUAL(p1->getTasks().size(), 5);
//
//	ASSERT_EQUAL(w1->getTasks().size(), 4);
//	ASSERT_EQUAL(w2->getTasks().size(), 3);
//	ASSERT_EQUAL(w3->getTasks().size(), 1);
//	ASSERT_EQUAL(w4->getTasks().size(), 1);
//
//	ASSERT_EQUAL(t1->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t2->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t3->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t4->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t6->getCollaborators().size(), 3);
//
//	ASSERT_EQUAL(t1->getDependants().size(), 1);
//	ASSERT_EQUAL(t2->getDependants().size(), 2);
//	ASSERT_EQUAL(t3->getDependants().size(), 2);
//	ASSERT_EQUAL(t4->getDependants().size(), 1);
//	ASSERT_EQUAL(t6->getDependants().size(), 0);
//
//	ASSERT_EQUAL(t1->getDependencies().size(), 0);
//	ASSERT_EQUAL(t2->getDependencies().size(), 0);
//	ASSERT_EQUAL(t3->getDependencies().size(), 0);
//	ASSERT_EQUAL(t4->getDependencies().size(), 3);
//	ASSERT_EQUAL(t6->getDependencies().size(), 3);
//
//	ASSERT_EQUAL_DELTA(t1->calculateEstimatedTime(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateEstimatedTime(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateEstimatedTime(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t4->calculateEstimatedTime(), 15.6, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateEstimatedTime(), 5.7, .1);
//
//	ASSERT_EQUAL_DELTA(t1->calculateTimeToCompletion(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateTimeToCompletion(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateTimeToCompletion(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t4->calculateTimeToCompletion(), 23.452, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateTimeToCompletion(), 29.152, .1);
//	ASSERT_EQUAL((Date() + t6->calculateTimeToCompletion() * 24 * 7 * 3600).getTotalSeconds(), p1->projectedFinishDate(Date()).getTotalSeconds());
//	
//	try { a.removeTask(t4); }
//	catch (...)
//	{
//		ASSERT_EQUAL(1, 0);
//	}
//	try { a.removeTask(t4); }
//	catch (Application::ApplicationExcept& e)
//	{
//		ASSERT_EQUAL(e(), "Task being removed does not exist");
//	}
//	ASSERT_EQUAL(a.getTasks().size(), 4);
//
//	ASSERT_EQUAL(p1->getTasks().size(), 4);
//
//	ASSERT_EQUAL(w1->getTasks().size(), 3);
//	ASSERT_EQUAL(w2->getTasks().size(), 3);
//	ASSERT_EQUAL(w3->getTasks().size(), 1);
//	ASSERT_EQUAL(w4->getTasks().size(), 1);
//
//	ASSERT_EQUAL(t1->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t2->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t3->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t6->getCollaborators().size(), 3);
//
//	ASSERT_EQUAL(t1->getDependants().size(), 1);
//	ASSERT_EQUAL(t2->getDependants().size(), 1);
//	ASSERT_EQUAL(t3->getDependants().size(), 1);
//	ASSERT_EQUAL(t6->getDependants().size(), 0);
//
//	ASSERT_EQUAL(t1->getDependencies().size(), 0);
//	ASSERT_EQUAL(t2->getDependencies().size(), 0);
//	ASSERT_EQUAL(t3->getDependencies().size(), 0);
//	ASSERT_EQUAL(t6->getDependencies().size(), 3);
//
//	ASSERT_EQUAL_DELTA(t1->calculateEstimatedTime(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateEstimatedTime(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateEstimatedTime(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateEstimatedTime(), 5.7, .1);
//
//	ASSERT_EQUAL_DELTA(t1->calculateTimeToCompletion(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateTimeToCompletion(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateTimeToCompletion(), 4.625, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateTimeToCompletion(), 13.552, .1);
//	ASSERT_EQUAL((Date() + t6->calculateTimeToCompletion() * 24 * 7 * 3600).getTotalSeconds(), p1->projectedFinishDate(Date()).getTotalSeconds());
//
//	try { a.removeCollaborator(w4); }
//	catch (...)
//	{
//		ASSERT_EQUAL(1, 0);
//	}
//	try { a.removeCollaborator(w4); }
//	catch (Application::ApplicationExcept& e)
//	{
//		ASSERT_EQUAL(e(), "Collaborator being removed does not exist");
//	}
//
//	try { a.removeCollaborator(w3); }
//	catch (...)
//	{
//		ASSERT_EQUAL(1, 0);
//	}
//	try { a.removeCollaborator(w3); }
//	catch (Application::ApplicationExcept& e)
//	{
//		ASSERT_EQUAL(e(), "Collaborator being removed does not exist");
//	}
//
//	ASSERT_EQUAL(a.getCollaborators().size(), 2);
//
//	ASSERT_EQUAL(p1->getTasks().size(), 4);
//
//	ASSERT_EQUAL(w1->getTasks().size(), 3);
//	ASSERT_EQUAL(w2->getTasks().size(), 3);
//
//	ASSERT_EQUAL(t1->getCollaborators().size(), 2);
//	ASSERT_EQUAL(t2->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t3->getCollaborators().size(), 1);
//	ASSERT_EQUAL(t6->getCollaborators().size(), 2);
//
//	ASSERT_EQUAL(t1->getDependants().size(), 1);
//	ASSERT_EQUAL(t2->getDependants().size(), 1);
//	ASSERT_EQUAL(t3->getDependants().size(), 1);
//	ASSERT_EQUAL(t6->getDependants().size(), 0);
//
//	ASSERT_EQUAL(t1->getDependencies().size(), 0);
//	ASSERT_EQUAL(t2->getDependencies().size(), 0);
//	ASSERT_EQUAL(t3->getDependencies().size(), 0);
//	ASSERT_EQUAL(t6->getDependencies().size(), 3);
//
//	ASSERT_EQUAL_DELTA(t1->calculateEstimatedTime(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateEstimatedTime(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateEstimatedTime(), 9.867, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateEstimatedTime(), 17.1, .1);
//
//	ASSERT_EQUAL_DELTA(t1->calculateTimeToCompletion(), 1.85714, .1);
//	ASSERT_EQUAL_DELTA(t2->calculateTimeToCompletion(), 7.852, .1);
//	ASSERT_EQUAL_DELTA(t3->calculateTimeToCompletion(), 9.867, .1);
//	ASSERT_EQUAL_DELTA(t6->calculateTimeToCompletion(), (9.867 + 17.1), .1);
//	ASSERT_EQUAL((Date() + t6->calculateTimeToCompletion() * 24 * 7 * 3600).getTotalSeconds(), p1->projectedFinishDate(Date()).getTotalSeconds());
//
//	try { a.removeProject(p1); }
//	catch (...)
//	{
//		ASSERT_EQUAL(1, 0);
//	}
//	try { a.removeProject(p1); }
//	catch (Application::ApplicationExcept& e)
//	{
//		ASSERT_EQUAL(e(), "Project being removed does not exist");
//	}
//	ASSERT_EQUAL(a.getProjects().size(), 1);
//	ASSERT_EQUAL(a.getTasks().size(), 0);
//	ASSERT_EQUAL(w1->getProjects().size(), 0);
//	ASSERT_EQUAL(w2->getProjects().size(), 0);
//	ASSERT_EQUAL(w1->getTasks().size(), 0);
//	ASSERT_EQUAL(w2->getTasks().size(), 0);
//}
//void test3()
//{
//	Application a;
//	Client* c1 = new Client("Client 1");
//	a.addClient(c1);
//	Client* c2 = new Client("Client 2");
//	a.addClient(c2);
//	Programmer* w1 = new Programmer("Programmer 1", 1000);
//	a.addCollaborator(w1);
//	Tester* w2 = new Tester("Tester 1", 1000);
//	a.addCollaborator(w2);
//	Manager* w3 = new Manager("Manager 1", 1000);
//	a.addCollaborator(w3);
//	Architect* w4 = new Architect("Architect 1", 1000);
//	a.addCollaborator(w4);
//
//	Project* p1 = new Project("Project 1", "Description of Project 1", Date(1, 11, 2014, 12, 12, 3), 0);
//	a.addProject(p1);
//	Project* p2 = new Project("Project 2", "Description of Project 2", Date(1, 10, 2014, 12, 12, 3), 0);
//	a.addProject(p2);
//	c1->addProject(p1);
//	c2->addProject(p2);
//	Task* t1 = new Task("Task 1", "Description of Task 1", 26);
//	Task* t2 = new Task("Task 2", "Description of Task 2", 55);
//	Task* t3 = new Task("Task 3", "Description of Task 3", 148);
//	Task* t4 = new Task("Task 4", "Description of Task 4", 156);
//	Task* t5 = new Task("Task 5", "Description of Task 5", 91);
//	Task* t6 = new Task("Task 6", "Description of Task 6", 171);
//	a.addTask(t1);
//	a.addTask(t2);
//	a.addTask(t3);
//	a.addTask(t4);
//	a.addTask(t5);
//	a.addTask(t6);
//	p1->addTask(t1);
//	p1->addTask(t2);
//	p1->addTask(t3);
//	p1->addTask(t4);
//	p1->addTask(t5);
//	p1->addTask(t6);
//	t1->addCollaborator(w1, 6);
//	t1->addCollaborator(w2, 8);
//
//	t2->addCollaborator(w1, 7);
//
//	t3->addCollaborator(w2, 15);
//	t3->addCollaborator(w4, 17);
//
//	t4->addCollaborator(w1, 10);
//
//	t5->addCollaborator(w2, 13);
//
//	t6->addCollaborator(w1, 3);
//	t6->addCollaborator(w3, 20);
//	t6->addCollaborator(w2, 7);
//
//	t1->addDependant(t4);
//	t2->addDependant(t4);
//	t3->addDependant(t4);
//
//	t2->addDependant(t5);
//	t3->addDependant(t5);
//
//	t5->addDependant(t4);
//
//	t4->addDependant(t6);
//	t5->addDependant(t6);
//	vector<Task*> v_tasks = a.getTasks();
//	for (size_t i = 0; i < v_tasks.size(); i++)
//	{
//		cout << v_tasks.at(i)->getID() << " ";
//	}
//	cout << endl;
//	sort(v_tasks.begin(), v_tasks.end(), Task::TaskComparatorEffort());
//	for (size_t i = 0; i < v_tasks.size(); i++)
//	{
//		cout << v_tasks.at(i)->getID() << " ";
//	}
//
//
//}


int main()
{
	srand((unsigned int)time(NULL));
	Application* app = Application::Instance();
	/*app.genApplication();
	app.writeFiles();
	return 0;*/
	try{
		Application::readFiles();
	}
	catch (Application::ApplicationExcept& e)
	{
		cerr << e()<< endl;
		cin.get();
		delete app;
		return 1;
	}
	int state = 1;
	menus(state, *app);
	try{
		Application::writeFiles();
	}
	catch (Application::ApplicationExcept& e)
	{
		cerr << e()<<endl;
		cin.get();
		delete app;
		return 1;
	}
	delete app;
	return 0;
}
