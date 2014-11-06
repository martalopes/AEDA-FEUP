#include "Menu.h"
#include <iostream>
#include <ctime>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <algorithm>


const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int ENTER = 13;
const int SPACE = 32;
const int BACKSPACE = 8;
const int ESCAPE = 27;

///largura do ecra
const int WIDTH = 80;

///usado para guardar o numero de '\n' ate ao fim do ecra atual
int end_of_screen = 24;
///cor atual
int current_color = 7;
///@return uma string de tamanho n, com s1 no inicio e s2 no fim
string normalize(const string& s1, const string& s2, int n)
{
	string s_out = s1;
	s_out.resize(n);
	int j = s_out.length() - 1;
	for (int i = s2.length() - 1; i >= 0; i--)
	{
		s_out[j] = s2[i];
		j--;
	}
	return s_out;
}
void ClearScreen() /* http://www.cplusplus.com/articles/4z18T05o/ */
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}/* http://www.cplusplus.com/articles/4z18T05o/ */
///centra uma string
ostream& operator>>(ostream& out, string s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	int num = (WIDTH - s.length()) / 2;
	for (int i = num; i > 0; i--)
	{
		out << ' ';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current_color);
	out << s;
	return out;
}
///usado em vez de el de modo a contabilizar o numero de '\n' ate ao fim do ecra atual
ostream& el(ostream& out)
{
	end_of_screen--;
	return out << endl;
}
///move o cursor ate ao fim do ecra e restaura end_of_screen
void go_end_of_screen()
{
	while (end_of_screen > 0)
	{
		cout << el;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	end_of_screen = 24;
}
void changecolor(string color)
{
	if (color == "white")
		current_color = 7;
	else if (color == "black")
		current_color = 112;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current_color);
}
///mostra um menu generico e atualiza o estado
void genericmenu(int &state, Application &app, string name, string text, vector<string> options, vector<int> results)
{
	bool more = true;//falso termina a funcao
	bool change = false; //indica se e preciso voltar imprimir o ecra
	Cursor cursor1(results.size() - 1);
	while (more)
	{
		go_end_of_screen();
		ClearScreen();
		change = false;
		cout << el >> name << el << el >> text << el << el << el;
		if (options.size() < 5)
			cout << el;
		if (options.size() < 4)
			cout << el;
		if (options.size() < 3)
			cout << el << el;
		for (int i = 0; i < options.size(); i++)
		if (cursor1.getPosition() == i)
		{
			changecolor("black");
			cout >> "> " + options[i] << el << el << el;
			changecolor("white");
		}
		else cout >> options[i] << el << el << el;
		go_end_of_screen();
		cout >> app.getDate().printDate2() << "                                  ";
		while (!change)
		{
			char input = _getch();
			if (input == UP || input == LEFT)
				change = cursor1.dec();
			else if (input == DOWN || input == RIGHT)
				change = cursor1.inc();
			else if (input == ESCAPE || input == BACKSPACE)
			{
				change = true;
				more = false;
				state = results[results.size() - 1];
			}
			else if (input == ENTER || input == SPACE)
			{
				change = true;
				more = false;
				state = results[cursor1.getPosition()];
			}
		}
		ClearScreen();
	}
}
enum states
{
	EXIT = -1, ESCAPEMENU, MAINMENU1, CLIENTLOGINMENU, TASKMENU, COLPROJBYDATE, COLPROJBYTYPE, COLPROJBYNAME, VIEWPROJECTINFO, COLLABORATORLOGINMENU, PERSONALINFOMENU, COLLABORATORMENU, MANAGERLOGINMENU, ADMINLOGINMENU, CLIENTMENU, NEWPROJECTMENU, PROJECTLISTMENU, PROJECTINFO,
	ADMINMENU, ADMINCLIENTMENU, ADMINSELECTCLIENT, ADMINPROJECTMENU, ADMINTASKMENU, ADMINCOLLABORATORMENU, ADMINCREATECLIENT, ADMINCREATEPROJECT, ADMINSELECTPROJECT, ADMINCREATETASK, ADMINSELECTTASK, ADMINCREATECOLLABORATOR, ADMINSELECTCOLLABORATOR, ADMINEDITCLIENT, ADMINEDITPROJECT, ADMINEDITTASK, ADMINEDITCOLLABORATOR, TICK
};
static Client* currentclient = NULL;
static Project* currentproject = NULL;
static Task* currenttask = NULL;
static Collaborator* currentcollaborator = NULL;
void createprojectmenu(int& state, Application& app)
{
	string name;
	string type;
	string deadline;
	go_end_of_screen();
	ClearScreen();
	cout << el << el >> "Please enter Project name" << el << el << el;
	cout << "                   >  ";
	getline(cin, name);
	if (name == "")
	{
		state = ADMINPROJECTMENU; return;
	}
	cout << el << el;
	cout >> "Please enter Project type" << el << el << el;
	cout << "                   >  ";
	getline(cin, type);
	if (type == "")
	{
		state = ADMINPROJECTMENU; return;
	}
	cout << el << el;
	cout >> "Please enter the deadline of the project (dd/mm/yyyy)" << el << el << el;
	cout << "                   >  ";
	getline(cin, deadline);
	if (type == "")
	{
		state = ADMINPROJECTMENU; return;
	}
	Date d1;
	try{ d1 = Date(deadline); }
	catch (Date::DateExcept& e)
	{
		cout << el << el >> "Invalid Date";
		cin.get();
		return;
	}
	Project* p = new Project(name, type, d1, 0);
	try{ app.addProject(p); }
	catch (Application::ApplicationExcept& e)
	{
		cout << el << el >> e();
		go_end_of_screen();
		cin.get();
		delete p;
		return;
	}
	if (currentclient != NULL) p->setClient(currentclient);
	state = ADMINPROJECTMENU;
}
void createclientmenu(int& state, Application& app)
{
	string name;
	go_end_of_screen();
	ClearScreen();
	//system("CLS");
	cout << el << el >> "Please enter Client name" << el << el << el;
	cout << "                   >  ";
	getline(cin, name);
	if (name == "")
	{
		state = ADMINCLIENTMENU; return;
	}
	Client* p = new Client(name);
	cout << el << el;
	try{ app.addClient(p); }
	catch (Application::ApplicationExcept& e)
	{
		cout >> e();
		go_end_of_screen();
		cin.get();
		delete p;
		return;
	}
	state = ADMINCLIENTMENU;
}
void createTaskmenu(int& state, Application& app)
{
	string name;
	string type;
	string deadline;
	go_end_of_screen();
	ClearScreen();
	//system("CLS");
	cout << el << el >> "Please enter Task name" << el << el << el;
	cout << "                   >  ";
	getline(cin, name);
	if (name == "")
	{
		state = ADMINTASKMENU; return;
	}
	cout << el << el >> "Please enter Task description" << el << el << el;
	cout << "                   >  ";
	string description;
	getline(cin, description);
	if (description == "")
	{
		state = ADMINTASKMENU; return;
	}
	cout << el << el >> "Please enter Task effort" << el << el << el;
	cout << "                   >  ";
	string effort;
	getline(cin, effort);
	if (effort == "")
	{
		state = ADMINTASKMENU; return;
	}
	stringstream s;
	s << effort;
	int ieffort = 0;
	s >> ieffort;
	Task* p = new Task(name, description, ieffort);
	cout << el << el;
	try{ app.addTask(p); }
	catch (Application::ApplicationExcept& e)
	{
		cout >> e();
		go_end_of_screen();
		cin.get();
		delete p;
		return;
	}
	state = ADMINTASKMENU;
}
void createcollaboratormenu(int& state, Application& app)
{
	string name;
	string type;
	string deadline;
	go_end_of_screen();
	ClearScreen();
	cout << el << el >> "Please enter Collaborator name" << el << el << el;
	cout << "                   >  ";
	getline(cin, name);
	if (name == "")
	{
		state = ADMINCOLLABORATORMENU; return;
	}
	cout << el << el >> "Please enter Collaborator max weekly hours" << el << el << el;
	cout << "                   >  ";
	string maxweeklyhours;
	getline(cin, maxweeklyhours);
	if (maxweeklyhours == "")
	{
		state = ADMINCOLLABORATORMENU; return;
	}
	stringstream s;
	s << maxweeklyhours;
	int imaxweeklyhours = 0;
	s >> imaxweeklyhours;
	cout << el << el >> "Please enter Collaborator Title" << el << el << el;
	cout << "                   >  ";
	string title;
	getline(cin, title);
	if (title == "")
	{
		state = ADMINCOLLABORATORMENU; return;
	}
	Collaborator* c = NULL;
	if (title == "Manager")
		c = new Manager(name, imaxweeklyhours);
	else if (title == "Tester")
		c = new Tester(name, imaxweeklyhours);
	else if (title == "Architect")
		c = new Architect(name, imaxweeklyhours);
	else if (title == "Programmer")
		c = new Programmer(name, imaxweeklyhours);
	else return;
	cout << el << el;
	try{ app.addCollaborator(c); }
	catch (Application::ApplicationExcept& e)
	{
		cout >> e();
		go_end_of_screen();
		cin.get();
		delete c;
		return;
	}
	state = ADMINCOLLABORATORMENU;
}
vector<Project::ProjectComparator*> getProjectComparators()
{
	vector<Project::ProjectComparator*> out;
	Project::ProjectComparator* p1 = new Project::ProjectComparatorAlphabetic();
	Project::ProjectComparator* p2 = new Project::ProjectComparatorCost();
	Project::ProjectComparator* p3 = new Project::ProjectComparatorID();
	Project::ProjectComparator* p4 = new Project::ProjectComparatorNumTasks();
	Project::ProjectComparator* p5 = new Project::ProjectComparatorNumCollaborators();
	Project::ProjectComparator* p6 = new Project::ProjectComparatorType();
	Project::ProjectComparator* p7 = new Project::ProjectComparatorDeadline();
	Project::ProjectComparator* p8 = new Project::ProjectComparatorTimeToFinish();
	out.push_back(p1);
	out.push_back(p2);
	out.push_back(p3);
	out.push_back(p4);
	out.push_back(p5);
	out.push_back(p6);
	out.push_back(p7);
	out.push_back(p8);
	return out;
}
vector<Task::TaskComparator*> getTaskComparators()
{
	vector<Task::TaskComparator*> out;
	Task::TaskComparator* p1 = new Task::TaskComparatorAlphabetic();
	Task::TaskComparator* p2 = new Task::TaskComparatorEffort();
	Task::TaskComparator* p3 = new Task::TaskComparatorID();
	Task::TaskComparator* p4 = new Task::TaskComparatorTimeToCompletion();
	Task::TaskComparator* p5 = new Task::TaskComparatorEstimatedTime();
	Task::TaskComparator* p6 = new Task::TaskComparatorNumDependants();
	Task::TaskComparator* p7 = new Task::TaskComparatorNumDependencies();

	out.push_back(p1);
	out.push_back(p2);
	out.push_back(p3);
	out.push_back(p4);
	out.push_back(p5);
	out.push_back(p6);
	out.push_back(p7);
	return out;
}
vector<Client::ClientComparator*> getClientComparators()
{
	vector<Client::ClientComparator*> out;
	Client::ClientComparator* p1 = new Client::ClientComparatorAlphabetic();
	Client::ClientComparator* p2 = new Client::ClientComparatorNumProjects();
	Client::ClientComparator* p3 = new Client::ClientComparatorID();
	Client::ClientComparator* p4 = new Client::ClientComparatorTotal();
	out.push_back(p1);
	out.push_back(p2);
	out.push_back(p3);
	out.push_back(p4);
	return out;
}
vector<Collaborator::CollaboratorComparator*> getCollaboratorComparators()
{
	vector<Collaborator::CollaboratorComparator*> out;
	Collaborator::CollaboratorComparator* p1 = new Collaborator::CollaboratorComparatorAlphabetic();
	Collaborator::CollaboratorComparator* p2 = new Collaborator::CollaboratorComparatorCost();
	Collaborator::CollaboratorComparator* p3 = new Collaborator::CollaboratorComparatorID();
	Collaborator::CollaboratorComparator* p4 = new Collaborator::CollaboratorComparatorWorkinghours();
	Collaborator::CollaboratorComparator* p5 = new Collaborator::CollaboratorComparatorMaxWeeklyHours();
	Collaborator::CollaboratorComparator* p6 = new Collaborator::CollaboratorComparatorNumTasks();
	Collaborator::CollaboratorComparator* p7 = new Collaborator::CollaboratorComparatorExperience();
	Collaborator::CollaboratorComparator* p8 = new Collaborator::CollaboratorComparatorNumProjects();
	out.push_back(p1);
	out.push_back(p2);
	out.push_back(p3);
	out.push_back(p4);
	out.push_back(p5);
	out.push_back(p6);
	out.push_back(p7);
	out.push_back(p8);
	return out;
}
template<class T>
vector<vector<string>> prep_list(vector<T*> v_in)
{
	vector<vector<string>> v_out;
	int size = 7;
	vector<string> v;
	for (int i = 0; i < v_in.size(); i++)
	{
		if (v.size() == size)
		{
			v_out.push_back(v);
			v.clear();
		}
		string s = v_in.at(i)->toString();
		v.push_back(s);
	}
	if (v.size() != 0)
		v_out.push_back(v);
	return v_out;
}
void clientprojectlist(int& state, Application& app)
{
	bool more = true;
	int page = 1;
	Cursor cursor1;
	bool changeinoptions = true;
	vector <Project::ProjectComparator*> comps = getProjectComparators();
	vector <string> comps_abv = { "Alph", "Cost", "ID", "NumTasks", "NumCol", "Type", "Deadline", "Time" };
	int comp = 0;
	vector<Project*> projects = currentclient->getProjects();
	vector <vector <string>> v;
	vector<string> options;
	while (more)
	{
		bool change = false;
		string auxmessage = "Client/List Projects";
		string message = "Please select a Project (TAB to switch filter)";
		cout << el >> auxmessage << el << el >> message << el << el;
		if (changeinoptions)
		{
			insertionSort(projects, *(comps.at(comp)));
			v = prep_list(projects);
			if (v.size() == 0)
				options.clear();
			else options = v[page - 1];
			options = v[page - 1];
			cursor1.changeMax(options.size());
			options.push_back("Back");
		}
		cout << "         ";
		for (int i = 0; i < comps.size(); i++)
		{
			if (comp == i)
			{
				changecolor("black");
				cout << comps_abv[i];
				changecolor("white");
				cout << "     ";
			}
			else cout << comps_abv[i] + "   ";
		}
		cout << el << el;
		for (int i = 0; i < options.size(); i++)
		{
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				cout >> "> " + options[i] << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el;
		}
		for (; end_of_screen>1;)
		{
			cout << el;
		}
		cout >> "Page " + to_string(page) + "/" + to_string(v.size());
		go_end_of_screen();
		while (!change)
		{
			char input = _getch();
			if (input == UP)
			{
				change = cursor1.dec();
				changeinoptions = false;
			}
			else if (input == DOWN)
			{
				change = cursor1.inc();
				changeinoptions = false;
			}
			else if (input == LEFT)
			{
				if (page > 1)
				{
					page--;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == RIGHT)
			{
				if (page < v.size())
				{
					page++;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == '\t')
			{
				comp = (comp + 1) % comps.size();
				page = 1;
				change = true;
				changeinoptions = true;
			}
			else if (input == ESCAPE)
			{
				change = true;
				more = false;
				state = CLIENTMENU;
			}
			else if (input == ENTER || input == SPACE)
			{
				if (cursor1.getPosition() == options.size() - 1)
				{
					change = true;
					more = false;
					state = CLIENTMENU;
				}
				else
				{
					currentproject = projects.at((page - 1) * 7 + cursor1.getPosition());
					state = PROJECTINFO;
					change = true;
					more = false;
				}
			}
		}
		ClearScreen();
	}
	for (size_t i = 0; i < comps.size(); i++)
	{
		delete comps.at(i);
	}
}
void fullprojectlist(int& state, Application& app)
{
	bool more = true;
	int page = 1;
	Cursor cursor1;
	bool changeinoptions = true;
	vector <Project::ProjectComparator*> comps = getProjectComparators();
	vector <string> comps_abv;
	for (size_t i = 0; i < comps.size(); i++)
	{
		comps_abv.push_back(comps.at(i)->getAbbreviation());
	}
	int comp = 0;
	vector<Project*> projects = app.getProjects();
	vector <vector <string>> v;
	vector<string> options;
	while (more)
	{
		bool change = false;
		string auxmessage = "List Projects";
		string message = "Please select a Project (TAB to switch filter)";
		cout << el >> auxmessage << el << el >> message << el << el;
		if (changeinoptions)
		{
			insertionSort(projects, *(comps.at(comp)));
			v = prep_list(projects);
			if (v.size() == 0)
				options.clear();
			else options = v[page - 1];
			//options = v[page - 1];
			cursor1.changeMax(options.size());
			options.push_back("Back");
		}
		cout << "      ";
		for (int i = 0; i < comps.size(); i++)
		{
			if (comp == i)
			{
				changecolor("black");
				cout << comps_abv[i];
				changecolor("white");
				cout << "     ";
			}
			else cout << comps_abv[i] + "   ";
		}
		cout << el << el;
		for (int i = 0; i < options.size(); i++)
		{
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				cout >> "> " + options[i] << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el;
		}
		for (; end_of_screen>1;)
		{
			cout << el;
		}
		cout >> "Page " + to_string(page) + "/" + to_string(v.size());
		go_end_of_screen();
		while (!change)
		{
			char input = _getch();
			if (input == UP)
			{
				change = cursor1.dec();
				changeinoptions = false;
			}
			else if (input == DOWN)
			{
				change = cursor1.inc();
				changeinoptions = false;
			}
			else if (input == LEFT)
			{
				if (page > 1)
				{
					page--;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == RIGHT)
			{
				if (page < v.size())
				{
					page++;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == '\t')
			{
				comp = (comp + 1) % comps.size();
				page = 1;
				change = true;
				changeinoptions = true;
			}
			else if (input == ESCAPE)
			{
				change = true;
				more = false;
				state = ADMINPROJECTMENU;
			}
			else if (input == ENTER || input == SPACE)
			{
				if (cursor1.getPosition() == options.size() - 1)
				{
					change = true;
					more = false;
					state = ADMINPROJECTMENU;
				}
				else
				{
					currentproject = projects.at((page - 1) * 7 + cursor1.getPosition());
					state = ADMINEDITPROJECT;
					change = true;
					more = false;
				}
			}
		}
		ClearScreen();
	}
	for (size_t i = 0; i < comps.size(); i++)
	{
		delete comps.at(i);
	}
}
void fullclientlist(int& state, Application& app)
{
	bool more = true;
	int page = 1;
	Cursor cursor1;
	bool changeinoptions = true;
	vector <Client::ClientComparator*> comps = getClientComparators();
	vector <string> comps_abv;
	for (size_t i = 0; i < comps.size(); i++)
	{
		comps_abv.push_back(comps.at(i)->getAbbreviation());
	}
	int comp = 0;
	vector<Client*> clients = app.getClients();
	vector <vector <string>> v;
	vector<string> options;
	while (more)
	{
		bool change = false;
		string auxmessage = "List Clients";
		string message = "Please select a Client (TAB to switch filter)";
		cout << el >> auxmessage << el << el >> message << el << el;
		if (changeinoptions)
		{
			insertionSort(clients, *(comps.at(comp)));
			v = prep_list(clients);
			if (v.size() == 0)
				options.clear();
			else options = v[page - 1];
			//options = v[page - 1];
			cursor1.changeMax(options.size());
			options.push_back("Back");
		}
		cout << "                         ";
		for (int i = 0; i < comps.size(); i++)
		{
			if (comp == i)
			{
				changecolor("black");
				cout << comps_abv[i];
				changecolor("white");
				cout << "     ";
			}
			else cout << comps_abv[i] + "   ";
		}
		cout << el << el;
		for (int i = 0; i < options.size(); i++)
		{
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				cout >> "> " + options[i] << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el;
		}
		for (; end_of_screen>1;)
		{
			cout << el;
		}
		cout >> "Page " + to_string(page) + "/" + to_string(v.size());
		go_end_of_screen();
		while (!change)
		{
			char input = _getch();
			if (input == UP)
			{
				change = cursor1.dec();
				changeinoptions = false;
			}
			else if (input == DOWN)
			{
				change = cursor1.inc();
				changeinoptions = false;
			}
			else if (input == LEFT)
			{
				if (page > 1)
				{
					page--;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == RIGHT)
			{
				if (page < v.size())
				{
					page++;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == '\t')
			{
				comp = (comp + 1) % comps.size();
				page = 1;
				change = true;
				changeinoptions = true;
			}
			else if (input == ESCAPE)
			{
				change = true;
				more = false;
				state = ADMINCLIENTMENU;
			}
			else if (input == ENTER || input == SPACE)
			{
				if (cursor1.getPosition() == options.size() - 1)
				{
					change = true;
					more = false;
					state = ADMINCLIENTMENU;
				}
				else
				{
					currentclient = clients.at((page - 1) * 7 + cursor1.getPosition());
					state = ADMINEDITCLIENT;
					change = true;
					more = false;
				}
			}
		}
		ClearScreen();
	}
	for (size_t i = 0; i < comps.size(); i++)
	{
		delete comps.at(i);
	}
}
void fullcollaboratorlist(int& state, Application& app)
{
	bool more = true;
	int page = 1;
	Cursor cursor1;
	bool changeinoptions = true;
	vector <Collaborator::CollaboratorComparator*> comps = getCollaboratorComparators();
	vector <string> comps_abv;
	for (size_t i = 0; i < comps.size(); i++)
	{
		comps_abv.push_back(comps.at(i)->getAbbreviation());
	}
	int comp = 0;
	vector<Collaborator*> collaborators = app.getCollaborators();
	vector <vector <string>> v;
	vector<string> options;
	while (more)
	{
		bool change = false;
		string auxmessage = "List collaborators";
		string message = "Please select a Client (TAB to switch filter)";
		cout << el >> auxmessage << el << el >> message << el << el;
		if (changeinoptions)
		{
			insertionSort(collaborators, *(comps.at(comp)));
			v = prep_list(collaborators);
			if (v.size() == 0)
				options.clear();
			else options = v[page - 1];
			//options = v[page - 1];
			cursor1.changeMax(options.size());
			options.push_back("Back");
		}
		cout << "       ";
		for (int i = 0; i < comps.size(); i++)
		{
			if (comp == i)
			{
				changecolor("black");
				cout << comps_abv[i];
				changecolor("white");
				cout << "     ";
			}
			else cout << comps_abv[i] + "   ";
		}
		cout << el << el;
		for (int i = 0; i < options.size(); i++)
		{
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				cout >> "> " + options[i] << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el;
		}
		for (; end_of_screen>1;)
		{
			cout << el;
		}
		cout >> "Page " + to_string(page) + "/" + to_string(v.size());
		go_end_of_screen();
		while (!change)
		{
			char input = _getch();
			if (input == UP)
			{
				change = cursor1.dec();
				changeinoptions = false;
			}
			else if (input == DOWN)
			{
				change = cursor1.inc();
				changeinoptions = false;
			}
			else if (input == LEFT)
			{
				if (page > 1)
				{
					page--;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == RIGHT)
			{
				if (page < v.size())
				{
					page++;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == '\t')
			{
				comp = (comp + 1) % comps.size();
				page = 1;
				change = true;
				changeinoptions = true;
			}
			else if (input == ESCAPE)
			{
				change = true;
				more = false;
				state = ADMINCOLLABORATORMENU;
			}
			else if (input == ENTER || input == SPACE)
			{
				if (cursor1.getPosition() == options.size() - 1)
				{
					change = true;
					more = false;
					state = ADMINCOLLABORATORMENU;
				}
				else
				{
					currentcollaborator = collaborators.at((page - 1) * 7 + cursor1.getPosition());
					state = ADMINEDITCOLLABORATOR;
					change = true;
					more = false;
				}
			}
		}
		ClearScreen();
	}
	for (size_t i = 0; i < comps.size(); i++)
	{
		delete comps.at(i);
	}
}
void fulltasklist(int& state, Application& app)
{
	bool more = true;
	int page = 1;
	Cursor cursor1;
	bool changeinoptions = true;
	vector <Task::TaskComparator*> comps = getTaskComparators();
	vector <string> comps_abv;
	for (size_t i = 0; i < comps.size(); i++)
	{
		comps_abv.push_back(comps.at(i)->getAbbreviation());
	}
	int comp = 0;
	vector<Task*> tasks = app.getTasks();
	vector <vector <string>> v;
	vector<string> options;
	while (more)
	{
		bool change = false;
		string auxmessage = "List Tasks";
		string message = "Please select a Client (TAB to switch filter)";
		cout << el >> auxmessage << el << el >> message << el << el;
		if (changeinoptions)
		{
			insertionSort(tasks, *(comps.at(comp)));
			v = prep_list(tasks);
			if (v.size() == 0)
				options.clear();
			else options = v[page - 1];
			//options = v[page - 1];
			cursor1.changeMax(options.size());
			options.push_back("Back");
		}
		cout << "       ";
		for (int i = 0; i < comps.size(); i++)
		{
			if (comp == i)
			{
				changecolor("black");
				cout << comps_abv[i];
				changecolor("white");
				cout << "  ";
			}
			else cout << comps_abv[i] + "  ";
		}
		cout << el << el;
		for (int i = 0; i < options.size(); i++)
		{
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				cout >> "> " + options[i] << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el;
		}
		for (; end_of_screen>1;)
		{
			cout << el;
		}
		cout >> "Page " + to_string(page) + "/" + to_string(v.size());
		go_end_of_screen();
		while (!change)
		{
			char input = _getch();
			if (input == UP)
			{
				change = cursor1.dec();
				changeinoptions = false;
			}
			else if (input == DOWN)
			{
				change = cursor1.inc();
				changeinoptions = false;
			}
			else if (input == LEFT)
			{
				if (page > 1)
				{
					page--;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == RIGHT)
			{
				if (page < v.size())
				{
					page++;
					change = true;
					changeinoptions = true;
				}
				else
				{
					change = false;
					changeinoptions = false;
				}
			}
			else if (input == '\t')
			{
				comp = (comp + 1) % comps.size();
				page = 1;
				change = true;
				changeinoptions = true;
			}
			else if (input == ESCAPE)
			{
				change = true;
				more = false;
				state = ADMINTASKMENU;
			}
			else if (input == ENTER || input == SPACE)
			{
				if (cursor1.getPosition() == options.size() - 1)
				{
					change = true;
					more = false;
					state = ADMINTASKMENU;
				}
				else
				{
					currenttask = tasks.at((page - 1) * 7 + cursor1.getPosition());
					state = ADMINEDITTASK;
					change = true;
					more = false;
				}
			}
		}
		ClearScreen();
	}
	for (size_t i = 0; i < comps.size(); i++)
	{
		delete comps.at(i);
	}
}
vector<string> parse_line(string line, bool&ok, bool&end)
{
	vector<string> out;
	if (line == "")
	{
		end = true;
		return out;
	}
	string temp;
	for (int i = 0; i < line.length(); i++)
	{
		if (iswspace(line.at(i)) && temp != "")
		{
			out.push_back(temp);
			temp.clear();
		}
		if (!iswspace(line.at(i))) temp += line.at(i);
	}
	if (temp != "")
		out.push_back(temp);
	return out;
}
void projectcommand(int& state)
{
	string line;
	getline(cin, line);
	bool ok = true;
	bool end = false;
	vector<string> tokens = parse_line(line, ok, end);
	if (end)
	{
		state = ADMINSELECTPROJECT;
		//cin.get();
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "delete")
	{
		try { Application::removeProject(currentproject); }
		catch (Application::ApplicationExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
		currentproject = NULL;
		state = ADMINSELECTPROJECT;
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "setName")
	if (tokens.size() > 1)
	{
		string name = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			name += ' ' + tokens.at(i);
		currentproject->setName(name);
	}
	if (tokens.at(0) == "setType")
	if (tokens.size() > 1)
	{
		string type = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			type += ' ' + tokens.at(i);
		currentproject->setType(type);
	}
	if (tokens.at(0) == "addTask")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currentproject->addTask(Application::getTaskPtr(ID)))
			{
				cout << el >> "Task could not be added";
				cin.get();
			}
		}
		catch (Project::ProjectExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeTask")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;

		try{
			if (!currentproject->removeTask(Application::getTaskPtr(ID)))
			{
				cout << el >> "Task could not be removed";
				cin.get();
			}
		}
		catch (Project::ProjectExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "setDeadline")
	if (tokens.size() > 1)
	{
		Date d;
		try{ d = Date(tokens.at(1)); }
		catch (Date::DateExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
		try{
			currentproject->setDeadline(d);
		}
		catch (Project::ProjectExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "setClient")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currentproject->setClient(Application::getClientPtr(ID)))
			{
				cout << el >> "Project already has a Client";
				cin.get();
			}
		}
		catch (Project::ProjectExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeClient")
	{
		try{
			if (!currentproject->removeClient())
			{
				cout << el >> "Project has no client";
				cin.get();
			}
		}
		catch (Project::ProjectExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	/*for (size_t i = 0; i < tokens.size(); i++)
	{
	cout << tokens[i] << " ";
	}*/

}
void projectinfo(int &state, Application& app)
{
	ClearScreen();
	cout << el << el >> normalize("ID of Project: ", to_string(currentproject->getID()), 50) << el;
	cout >> normalize("Project Name: ", currentproject->getName(), 50) << el;
	cout >> normalize("Project Type: ", currentproject->getType(), 50) << el;
	if (currentproject->getClient() == NULL)
		cout >> normalize("Client:", "none", 50) << el;
	else cout >> normalize("Client:", currentproject->getClient()->getName(), 50) << el;
	cout >> normalize("Cost:", to_string(currentproject->getCost()) + '$', 50) << el;
	cout >> normalize("Deadline:", currentproject->getDeadline().printDate2(), 50) << el;
	string s;
	if (currentproject->isCompleted())
		s = "Completed";
	else if (currentproject->isPastDeadline(app.getDate()))
		s = "Late";
	else s = "On time";
	cout >> normalize("Status:", s, 50) << el;
	if (!currentproject->isCompleted())
	{
		double timetoconclusion = currentproject->weeksToFinish();
		if (abs(timetoconclusion - (-1)) < .1)
			cout >> normalize("Time of conclusion", "None", 50) << el;
		else cout >> normalize("Time of conclusion", currentproject->projectedFinishDate(app.getDate()).printDate2(), 50) << el;
	}
	cout << el >> normalize("Collaborators:", "Tasks:", 40) << el << el;
	for (size_t i = 0; i < max(currentproject->getCollaborators().size(), currentproject->getTasks().size()); i++)
	{
		cout >> normalize((i < currentproject->getCollaborators().size()) ? "- " + currentproject->getCollaborators().at(i)->getName() : "", (i < currentproject->getTasks().size()) ? currentproject->getTasks().at(i)->getName() + " -" : "", 50) << el;
	}
	cout << el << el;
	cout << "                   >  ";
	projectcommand(state);
	ClearScreen();
	//state = ADMINSELECTPROJECT;
}
void clientcommand(int& state)
{
	string line;
	getline(cin, line);
	bool ok = true;
	bool end = false;
	vector<string> tokens = parse_line(line, ok, end);
	if (end)
	{
		state = ADMINSELECTCLIENT;
		//cin.get();
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "delete")
	{
		try { Application::removeClient(currentclient); }
		catch (Application::ApplicationExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
		currentclient = NULL;
		state = ADMINSELECTCLIENT;
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "setName")
	if (tokens.size() > 1)
	{
		string name = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			name += ' ' + tokens.at(i);
		currentclient->setName(name);
	}
	if (tokens.at(0) == "addProject")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currentclient->addProject(Application::getProjectPtr(ID)))
			{
				cout << el >> "Project could not be added because it already has a client";
				cin.get();
			}
		}
		catch (Client::ClientExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeProject")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currentclient->removeProject(Application::getProjectPtr(ID)))
			{
				cout << el >> "Project could not be removed because it does not belong to the client";
				cin.get();
			}
		}
		catch (Client::ClientExcept& e)
		{
			cout << el >> e();
			cin.get();
		}

	}
	/*for (size_t i = 0; i < tokens.size(); i++)
	{
	cout << tokens[i] << " ";
	}*/

}
void clientinfo(int &state, Application& app)
{
	ClearScreen();
	cout << el << el >> normalize("ID of Client: ", to_string(currentclient->getID()), 50) << el;
	cout >> normalize("Client Name: ", currentclient->getName(), 50) << el;
	cout >> normalize("Total: ", to_string(currentclient->getTotal()) + '$', 50) << el;
	cout >> "Projects:" << el << el;
	if (currentclient->getProjects().size() == 0)
		cout >> "None" << el;
	for (size_t i = 0; i < currentclient->getProjects().size(); i++)
	{
		cout >> normalize(to_string(currentclient->getProjects().at(i)->getID()) + " - ", currentclient->getProjects().at(i)->getName(), 50) << el;
	}
	cout << el << el;
	cout << "                   >  ";
	clientcommand(state);
	ClearScreen();
	//state = ADMINSELECTCLIENT;
}
void collaboratorcommand(int& state)
{
	string line;
	getline(cin, line);
	bool ok = true;
	bool end = false;
	vector<string> tokens = parse_line(line, ok, end);
	if (end)
	{
		state = ADMINSELECTCOLLABORATOR;
		//cin.get();
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "delete")
	{
		try { Application::removeCollaborator(currentcollaborator); }
		catch (Application::ApplicationExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
		currentcollaborator = NULL;
		state = ADMINSELECTCOLLABORATOR;
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "setName")
	if (tokens.size() > 1)
	{
		string name = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			name += ' ' + tokens.at(i);
		currentcollaborator->setName(name);
	}
	if (tokens.at(0) == "setWeeklyHours")
	if (tokens.size() > 1)
	{
		stringstream s;
		int hours = 0;
		s << tokens.at(1);
		s >> hours;
		if (hours > 0)
			currentcollaborator->setWeeklyHours(hours);
		else {
			cout << el >> "Invalid hours";
			cin.get();
		}
	}
	if (tokens.at(0) == "addTask")
	if (tokens.size() > 2)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		stringstream s2;
		int hours = 0;
		s2 << tokens.at(2);
		s2 >> hours;
		if (hours > 0){
			try{
				if (!currentcollaborator->addTask(Application::getTaskPtr(ID), hours))
				{
					cout << el >> "Task could not be added";
					cin.get();
				}
			}
			catch (Collaborator::CollaboratorExcept& e)
			{
				cout << el >> e();
				cin.get();
			}
		}
		else{
			cout << el >> "Invalid hours";
			cin.get();
		}
	}
	if (tokens.at(0) == "removeTask")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;

		try{
			if (!currentcollaborator->removeTask(Application::getTaskPtr(ID)))
			{
				cout << el >> "Task could not be removed";
				cin.get();
			}
		}
		catch (Collaborator::CollaboratorExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	/*for (size_t i = 0; i < tokens.size(); i++)
	{
	cout << tokens[i] << " ";
	}*/

}
void collaboratorinfo(int &state, Application& app)
{
	ClearScreen();
	cout << el << el >> normalize("ID of Collaborator: ", to_string(currentcollaborator->getID()), 50) << el;
	cout >> normalize("Collaborator Name: ", currentcollaborator->getName(), 50) << el;
	cout >> normalize("Collaborator Title: ", currentcollaborator->getTitle(), 50) << el;
	cout >> normalize("Collaborator Cost: ", to_string(currentcollaborator->getCost()), 50) << el;
	cout >> normalize("Collaborator Weekly Hours: ", to_string(currentcollaborator->getMaxWeeklyHours()), 50) << el;
	cout >> normalize("Collaborator Working Hours: ", to_string(currentcollaborator->getWorkingHours()), 50) << el;
	cout >> "Projects:" << el;
	if (currentcollaborator->getProjects().size() == 0)
		cout >> "none" << el;
	for (size_t i = 0; i < currentcollaborator->getProjects().size(); i++)
	{
		cout >> currentcollaborator->getProjects().at(i)->getName() << el;
	}
	cout << el;
	cout >> normalize("Active Tasks:", "Hours", 50) << el;
	if (currentcollaborator->getTasks().size() == 0)
		cout >> "none" << el;
	for (size_t i = 0; i < currentcollaborator->getTasks().size(); i++)
	{
		cout >> normalize(currentcollaborator->getTasks().at(i).first->getName(), to_string(currentcollaborator->getTasks().at(i).second), 50) << el;
	}
	cout << el;
	cout >> "Finished Tasks:" << el;
	if (currentcollaborator->getFinishedTasks().size() == 0)
		cout >> "none" << el;
	for (size_t i = 0; i < currentcollaborator->getFinishedTasks().size(); i++)
	{
		cout >> currentcollaborator->getFinishedTasks().at(i)->getName() << el;
	}
	cout << el << el;
	cout << "                   >  ";
	collaboratorcommand(state);
	ClearScreen();
	//state = ADMINSELECTCOLLABORATOR;
}
void taskcommand(int& state)
{
	string line;
	getline(cin, line);
	bool ok = true;
	bool end = false;
	vector<string> tokens = parse_line(line, ok, end);
	if (end)
	{
		state = ADMINSELECTTASK;
		//cin.get();
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "delete")
	{
		try { Application::removeTask(currenttask); }
		catch (Collaborator::CollaboratorExcept& e)
		{
			cout >> e() << el;
			cin.get();
		}
		currenttask = NULL;
		state = ADMINSELECTTASK;
		go_end_of_screen();
		return;
	}
	if (tokens.at(0) == "setName")
	if (tokens.size() > 1)
	{
		string name = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			name += ' ' + tokens.at(i);
		currenttask->setName(name);
	}
	if (tokens.at(0) == "setDescription")
	if (tokens.size() > 1)
	{
		string description = tokens.at(1);
		for (size_t i = 2; i < tokens.size(); i++)
			description += ' ' + tokens.at(i);
		currenttask->setDescription(description);
	}
	if (tokens.at(0) == "addCollaborator")
	if (tokens.size() > 2)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		stringstream s2;
		int hours = 0;
		s2 << tokens.at(2);
		s2 >> hours;
		if (hours > 0){
			try{
				if (!currenttask->addCollaborator(Application::getCollaboratorPtr(ID), hours))
				{
					cout << el >> "Collaborator could not be added";
					cin.get();
				}
			}
			catch (Task::TaskExcept& e)
			{
				cout << el >> e();
				cin.get();
			}
		}
		else{
			cout << el >> "Invalid hours";
			cin.get();
		}
	}
	if (tokens.at(0) == "removeCollaborator")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;

		try{
			if (!currenttask->removeCollaborator(Application::getCollaboratorPtr(ID)))
			{
				cout << el >> "Collaborator could not be removed";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "addDependency")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currenttask->addDependency(Application::getTaskPtr(ID)))
			{
				cout << el >> "Dependency could not be added";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeDependency")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;

		try{
			if (!currenttask->removeDependency(Application::getTaskPtr(ID)))
			{
				cout << el >> "Dependency could not be removed";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "addDependant")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currenttask->addDependant(Application::getTaskPtr(ID)))
			{
				cout << el >> "Dependant could not be added";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeDependant")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;

		try{
			if (!currenttask->removeDependency(Application::getTaskPtr(ID)))
			{
				cout << el >> "Dependant could not be removed";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "setEffort")
	if (tokens.size() > 1)
	{
		stringstream s;
		int effort = 0;
		s << tokens.at(1);
		s >> effort;
		if (effort >= 0)
			currenttask->setEffort(effort);
	}
	if (tokens.at(0) == "setProject")
	if (tokens.size() > 1)
	{
		stringstream s;
		int ID = 0;
		s << tokens.at(1);
		s >> ID;
		try{
			if (!currenttask->setProject(Application::getProjectPtr(ID)))
			{
				cout << el >> "Task already has a Project";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	if (tokens.at(0) == "removeProject")
	{
		try{
			if (!currenttask->removeProject())
			{
				cout << el >> "Task has no Project";
				cin.get();
			}
		}
		catch (Task::TaskExcept& e)
		{
			cout << el >> e();
			cin.get();
		}
	}
	/*for (size_t i = 0; i < tokens.size(); i++)
	{
	cout << tokens[i] << " ";
	}*/

}
void taskinfo(int& state, Application& app)
{
	ClearScreen();
	cout << el << el >> normalize("ID of Task: ", to_string(currenttask->getID()), 50) << el;
	cout >> normalize("Task Name: ", currenttask->getName(), 50) << el;
	cout >> normalize("Task Description: ", currenttask->getDescription(), 50) << el;
	cout >> normalize("Remaining effort: ", to_string(currenttask->getEffort()) + " hours", 50) << el;
	if (currenttask->getProject() != NULL)
		cout >> normalize("Project: ", currenttask->getProject()->getName(), 50) << el;
	else cout >> normalize("Project: ", "None", 50) << el;
	double timetocompletion = currenttask->calculateTimeToCompletion();
	if (abs(timetocompletion - (-1)) < .1)
		cout >> normalize("Est time of completion:", "None", 50) << el;
	else if (currenttask->isCompleted())
		cout >> normalize("Est time of completion:", "Done", 50) << el;
	else cout >> normalize("Est time of completion:", currenttask->getDateOfCompletion(app.getDate()).printDate2(), 50) << el;
	cout << el >> normalize("Collaborators:", "hours:", 40) << el << el;
	for (size_t i = 0; i < currenttask->getCollaborators().size(); i++)
	{
		cout >> normalize(currenttask->getCollaborators().at(i).first->getName(), to_string(currenttask->getCollaborators().at(i).second), 50) << el;
	}
	cout << el;
	cout >> "Dependencies:" << el << el;
	if (currenttask->getDependencies().size() == 0)
		cout >> "none" << el;
	for (size_t i = 0; i < currenttask->getDependencies().size(); i++)
	{
		cout >> currenttask->getDependencies().at(i)->getName() << el;
	}
	cout << el;
	cout >> "Dependants:" << el << el;
	if (currenttask->getDependants().size() == 0)
		cout >> "none" << el;
	for (size_t i = 0; i < currenttask->getDependants().size(); i++)
	{
		cout >> currenttask->getDependants().at(i)->getName() << el;
	}
	cout << el << el;
	cout << "                   >  ";
	taskcommand(state);
	ClearScreen();
	//state = ADMINSELECTTASK;
}
void tickmenu(int& state, Application& app)
{
		bool more = true;//falso termina a funcao
		bool change = false; //indica se e preciso voltar imprimir o ecra
		vector<int> results = { TICK, ADMINMENU };
		vector<string> options = { "Tick", "Back" };
		Cursor cursor1(results.size() - 1);
		while (more)
		{
			go_end_of_screen();
			ClearScreen();
			change = false;
			cout << el  << el << el >> "Sim" << el << el;
			cout >> app.getDate().printDate2() + " -> " + (app.getDate() + Date::toSeconds(7, 0, 0, 0, 0, 0)).printDate2();
			if (options.size() < 5)
				cout << el;
			if (options.size() < 4)
				cout << el;
			if (options.size() < 3)
				cout << el << el;
			cout << el << el;
			for (int i = 0; i < options.size(); i++)
			if (cursor1.getPosition() == i)
			{
				changecolor("black");
				if(i==0) cout >> ">> " + options[i]+ " <<" << el << el << el;
				else cout >> "> " + options[i] << el << el << el;
				changecolor("white");
			}
			else cout >> options[i] << el << el << el;
			go_end_of_screen();
			cout >> app.getDate().printDate2() << "                                  ";
			while (!change)
			{
				char input = _getch();
				if (input == UP || input == LEFT)
					change = cursor1.dec();
				else if (input == DOWN || input == RIGHT)
					change = cursor1.inc();
				else if (input == ESCAPE || input == BACKSPACE)
				{
					change = true;
					more = false;
					state = results[results.size() - 1];
				}
				else if (input == ENTER || input == SPACE)
				{
					change = true;
					more = false;
					if (results[cursor1.getPosition()] == TICK)
						app.tick();
					else state = results[cursor1.getPosition()];
				}
			}
			ClearScreen();
		}
}
void menus(int& state, Application& app)
{
	while (state != EXIT)
	{
		switch (state)
		{
		case ESCAPEMENU:
			genericmenu(state, app, "", "Are you sure you want to Exit this Application?", { "No", "Yes" }, { ADMINMENU, EXIT });
			break;
		case MAINMENU1:
			state = ADMINMENU;
			break;
		case ADMINMENU:
			currentclient = NULL;
			currentproject = NULL;
			currenttask = NULL;
			currentcollaborator = NULL;
			genericmenu(state, app, "Admin", "Please select an Option:", { "Sim", "Clients", "Projects", "Tasks", "Collaborators", "Quit" }, { TICK, ADMINCLIENTMENU, ADMINPROJECTMENU, ADMINTASKMENU, ADMINCOLLABORATORMENU, ESCAPEMENU });
			break;
		case TICK:
			tickmenu(state, app);
			break;
		case ADMINCLIENTMENU:
			genericmenu(state, app, "Admin", "Clients", { "New", "Existing", "Back" }, { ADMINCREATECLIENT, ADMINSELECTCLIENT, ADMINMENU });
			break;
		case ADMINPROJECTMENU:
			genericmenu(state, app, "Admin", "Projects", { "New", "Existing", "Back" }, { ADMINCREATEPROJECT, ADMINSELECTPROJECT, ADMINMENU });
			break;
		case ADMINTASKMENU:
			genericmenu(state, app, "Admin", "Tasks", { "New", "Existing", "Back" }, { ADMINCREATETASK, ADMINSELECTTASK, ADMINMENU });
			break;
		case ADMINCOLLABORATORMENU:
			genericmenu(state, app, "Admin", "Collaborators", { "New", "Existing", "Back" }, { ADMINCREATECOLLABORATOR, ADMINSELECTCOLLABORATOR, ADMINMENU });
			break;
		case ADMINSELECTCLIENT:
			fullclientlist(state, app);
			break;
		case ADMINSELECTPROJECT:
			fullprojectlist(state, app);
			break;
		case ADMINSELECTTASK:
			fulltasklist(state, app);
			break;
		case ADMINSELECTCOLLABORATOR:
			fullcollaboratorlist(state, app);
			break;
		case ADMINCREATECLIENT:
			createclientmenu(state, app);
			break;
		case ADMINCREATECOLLABORATOR:
			createcollaboratormenu(state, app);
			break;
		case ADMINCREATEPROJECT:
			createprojectmenu(state, app);
			break;
		case ADMINCREATETASK:
			createTaskmenu(state, app);
			break;
		case ADMINEDITPROJECT:
			projectinfo(state, app);
			break;
		case ADMINEDITCOLLABORATOR:
			collaboratorinfo(state, app);
			break;
		case ADMINEDITCLIENT:
			clientinfo(state, app);
			break;
		case ADMINEDITTASK:
			taskinfo(state, app);
			break;
		default:
			state = EXIT;
			break;
		}
	}
}
