#include "Task.h"



int Task::lastID = 0;

bool Task::setProject(Project* p, bool addTask)
{
	if (p == NULL)
		throw TaskExcept("Invalid Project");
	if (project != NULL)
		return false;
	if (addTask)
		p->addTask(this, false);
	project = p;
	project->updateCollaborators();
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		collaborators.at(i).first->updateProjects();
	}
	return true;
}
bool Task::addDependency(Task* t, bool addDependant)
{
	if (t == NULL)
		throw TaskExcept("No Task being added to Task:", ID);
	if (*this == *t)
		throw TaskExcept("Task being added to itself as dependency");
	if (!(project == t->project) || project == NULL || t->project == NULL)
		return false;
	for (size_t i = 0; i < dependencies.size(); ++i)
	if (*dependencies.at(i) == *t)
		return false;
	dependencies.push_back(t);
	if (addDependant)
		t->addDependant(this, false);
	return true;
}
bool Task::addDependant(Task* t, bool addDependency)
{
	if (t == NULL)
		throw TaskExcept("No Task being added to Task:", ID);
	if (*this == *t)
		throw TaskExcept("Task being added to itself as dependant");
	if (!(project == t->project) || project == NULL || t->project == NULL)
		return false;				//tarefas nao pertencem ao mesmo projecto
	for (size_t i = 0; i < dependants.size(); ++i)
	if (*dependants.at(i) == *t)
		return false;
	dependants.push_back(t);
	if (addDependency)
		t->addDependency(this, false);
	return true;
}
bool Task::addCollaborator(Collaborator* c1, unsigned int hours, bool addTask)
{
	if (c1 == NULL)
		throw Task::TaskExcept("Invalid Collaborator being added to Task");
	for (size_t i = 0; i < this->collaborators.size(); ++i)
	{
		if (*collaborators[i].first == *c1)
		{
			return false;
		}
	}
	collaborators.push_back(make_pair(c1, hours));
	if (project != NULL)
		project->updateCollaborators();
	if (addTask)
		return c1->addTask(this, hours, false);
	return true;
}
bool Task::removeCollaborator(Collaborator* c, bool removeTask)
{
	if (c == NULL)
		throw TaskExcept("Invalid Collaborator");
	for (size_t i = 0; i < collaborators.size(); ++i)
	if (collaborators.at(i).first == c)
	{
		collaborators.erase(collaborators.begin() + i);
		if (project != NULL)
			project->updateCollaborators();
		if (removeTask)
			return c->removeTask(this, false);
		return true;
	}
	return false;
}
double  Task::calculateEstimatedTime() const //tempo que demora a tarefa a ser completada, sem ter em conta dependencias
{
	if (isCompleted())
		return 0; //se tarefa esta comcluida retornar 0
	int sum = 0;
	for (size_t i = 0; i < collaborators.size(); i++)
		sum += collaborators.at(i).second; //soma das horas que a tarefa e trabalhada por semana
	if (sum == 0)
		return -1;//tempo e 'infinito'
	else return double(effort) / sum;
};
double Task::calculateTimeToCompletion() const //tempo que a tarefa vai demorar a ser completada, tendo em conta que as tarefas das quais depende terao de ser completadas primeiro
{
	double sum = this->calculateEstimatedTime();
	if (abs(sum - (-1)) < 0.001)
		return -1;
	if (dependencies.size() == 0)
		return sum; // se a tarefa nao tem dependencias o tempo corresponde apenas ao tempo da propria tarefa
	double max = dependencies.at(0)->calculateTimeToCompletion();
	if (abs(max - (-1)) < 0.001)
		return -1;
	for (size_t i = 1; i < dependencies.size(); i++)
	{
		double value = dependencies.at(i)->calculateTimeToCompletion();
		if (abs(value - (-1)) < 0.001)
			return -1;
		if (value > max)
			max = value;
	}
	sum += max; //se tiver dependencias o tempo que demora a completar sera o tempo da propria tarefa mais o maximo de todas as tarefas das quais depende
	return sum;
};
bool Task::isReady() const
{
	for (size_t i = 0; i < dependencies.size(); ++i)
	if (!dependencies.at(i)->isCompleted()) //uma tarefa pode ser realizada se todas as tarefas das quais depende estiverem completas
		return false;
	return true;
}
double Task::tick()			//semana de trabalho
{
	if (!isReady())
		return -1;
	double sum = 0;
	for (size_t i = 0; i < collaborators.size(); ++i)
	{
		sum += collaborators.at(i).second * collaborators.at(i).first->getCost();
		effort -= collaborators.at(i).second; //retira ao esforco necessario para completar a tarefa as horas que trabalha cada colaborador
		if (isCompleted()) // tarefa terminada
		{
			complete();//reassign collaborators
			break;
		}
	}
	return sum;		//retorna o custo total da semana
}
void Task::complete()
{
	effort = 0;
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		collaborators.at(i).first->reassign(this);//retirar esta tarefa das tarefas ativas para cada colaborador que nela trabalha e adiciona la ao conjunto de tarefas terminadas
	}
	collaborators.clear();
}
void Task::connect()
{
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		Collaborator * ptr = Application::getCollaboratorPtr((int)collaborators.at(i).first);
			collaborators.at(i).first = ptr;
	}
	for (size_t i = 0; i < dependencies.size(); i++)
	{
		Task * ptr = Application::getTaskPtr((int)dependencies.at(i));
			dependencies.at(i) = ptr;
	}
	for (size_t i = 0; i < dependants.size(); i++)
	{
		Task * ptr = Application::getTaskPtr((int)dependants.at(i));
			dependants.at(i) = ptr;
	}
	if ((int)project != 0)
	{
		Project * ptr = Application::getProjectPtr((int)project);
		if (ptr == NULL)
			throw TaskExcept("Error in tasks.txt");
		project = ptr;
	}
}

bool Task::operator==(Task& t2)
{
	return this->getID() == t2.getID();
}
ostream & operator<<(ostream& out, const Task& t)
{
	out << t.ID << endl;
	out << t.name << endl;
	out << t.description << endl;
	out << t.effort << endl;
	out << t.collaborators.size() << endl;
	for (size_t i = 0; i < t.collaborators.size(); i++)
		out << t.collaborators.at(i).first->getID() << " " << t.collaborators.at(i).second << endl;

	out << t.dependencies.size() << endl;
	for (size_t i = 0; i < t.dependencies.size(); i++)
		out << t.dependencies.at(i)->getID() << endl;
	
	out << t.dependants.size() << endl;
	for (size_t i = 0; i < t.dependants.size(); i++)
		out << t.dependants.at(i)->getID() << endl;
	if (t.project != NULL)
	out << t.project->getID() << endl;
	else out << 0 << endl;
	return out;
}
istream & operator>>(istream& in, Task& t)
{
	in >> t.ID;
	in.ignore();
	if (t.ID > Task::lastID)
		Task::lastID = t.ID;
	getline(in,t.name);
	getline(in,t.description);
	in >> t.effort;
	in.ignore();
	unsigned int numcollaborators = 0;
	in >> numcollaborators;
	in.ignore();
	for (size_t i = 0; i < numcollaborators; i++)
	{
		unsigned long int collaboratorid=0;
		unsigned int numhours;
		in >> collaboratorid;
		in.ignore();
		in >> numhours;
		in.ignore();
		t.collaborators.push_back(make_pair((Collaborator*) collaboratorid, numhours));
	}
	unsigned int numdependencies = 0;
	in >> numdependencies;
	in.ignore();
	for (size_t i = 0; i < numdependencies; i++)
	{
		unsigned long int dependencyid = 0;
		in >> dependencyid;
		in.ignore();
		t.dependencies.push_back((Task*) dependencyid);
	}
	unsigned int numdependants = 0;
	in >> numdependants;
	in.ignore();
	for (size_t i = 0; i < numdependants; i++)
	{
		unsigned long int dependantid = 0;
		in >> dependantid;
		in.ignore();
		t.dependants.push_back((Task*)dependantid);
	}
	unsigned long int projectid;
	in >> projectid;
	in.ignore();
	t.project = (Project*)projectid;
	return in;
}
bool Task::removeProject(bool removeTask)
{
	if (project == NULL)
		return false;
	if (!isIsolated())
		return false;
	if (removeTask)
	{
		project->removeTask(this, false);
		project->updateCollaborators();
	}
	project = NULL;
	for (size_t i = 0; i < collaborators.size(); i++)
	{
		collaborators.at(i).first->updateProjects();
	}
	return true;
}
string Task::toString() const
{
	return normalize(to_string(ID), name, 30);
}
bool Task::removeTrace()//remover todas as referencias de outros objectos a tarefa
{
	if (project != NULL)
	project->removeTask(this, false); // remover referencia do projecto a tarefa
	for (size_t i = 0; i < collaborators.size(); ++i)
	{
		collaborators.at(i).first->removeTask(this, false);// remover tarefa de todos os colaboradores
	}
	for (size_t i = 0; i < dependencies.size(); i++)
	{
		dependencies.at(i)->removeDependant(this, false); // remover tarefa de todos as tarefas das quais depende
		for (size_t j = 0; j < dependants.size(); j++)
			dependencies.at(i)->addDependant(dependants.at(j), false); 
	}
	for (size_t i = 0; i < dependants.size(); i++)
	{
		dependants.at(i)->removeDependency(this, false);
		for (size_t j = 0; j < dependencies.size(); j++)
			dependants.at(i)->addDependency(dependencies.at(j), false);//tarefas que dependem da tarefa atual passam a depender das tarefas das quais dependem a tarefa actual
	}
	return true;
}

bool Task::removeTraceOutsideProject()
{
	for (size_t i = 0; i < collaborators.size(); ++i)
	{
		collaborators.at(i).first->removeTask(this, false);// remover tarefa de todos os colaboradores
	}
	return true;
}

bool Task::removeDependency(Task* t, bool removeDependant)
{
	size_t i = 0;
	for (; i < dependencies.size(); i++)
	{
		if (*dependencies.at(i) == *t)
			break;
	}
	if (i == dependencies.size())
		throw TaskExcept("Dependency does not exist");
	dependencies.erase(dependencies.begin() + i);
	if (removeDependant)
		return t->removeDependant(this, false);
	return false;
}

bool Task::removeDependant(Task* t, bool removeDependency)
{
	size_t i = 0;
	for (; i < dependants.size(); i++)
	{
		if (*dependants.at(i) == *t)
			break;
	}
	if (i == dependants.size())
		throw TaskExcept("Dependant does not exist");
	dependants.erase(dependants.begin() + i);
	if (removeDependency)
		return t->removeDependency(this, false);
	return true;
}


Task::Task() : ID(0), effort(0), project(NULL){}
Task::Task(string name, string description, unsigned int effort) : name(name), description(description), effort(effort), ID(++lastID), project(NULL){}
Task::Task(string name, string description, unsigned int effort, int setID) : name(name), description(description), effort(effort), ID(setID), project(NULL){ if (setID > lastID) lastID = setID; }
Task::Task(int i)
{
	stringstream s1, s2;
	s1 << "Task " << i;
	s2 << "Description " << i;
	*this = Task(s1.str(), s2.str(), 1 + rand() % 100);
}

string Task::getName() const { return this->name; }
int Task::getID() const { return this->ID; }
Project* Task::getProject()const{ return this->project; }
vector<Task*> Task::getDependants() const{ return dependants; }
vector<Task*> Task::getDependencies() const{ return dependencies; }
vector<pair<Collaborator*, unsigned int> > Task::getCollaborators() const{ return collaborators; }
string Task::getDescription()const{ return description; }
void Task::setDescription(string s){ description = s; }
void Task::setName(string nm){ name = nm; }
void Task::setEffort(unsigned int ef){ if (ef == 0) complete(); else effort = ef; }
int Task::getEffort()const { return this->effort; }
Date Task::getDateOfCompletion(const Date& d)const{ return d + 7 * 24 * 3600 * calculateTimeToCompletion(); }
bool Task ::isCompleted() const
{
	return (effort <= 0);
}

bool Task::delay(int i){ if (isCompleted()) return false; effort += i; return true; }
bool Task::delay()
{
	if (isCompleted())
		return false;
	effort += rand() % 19 + 1;
}

bool Task::speedup()
{
	if (isCompleted())
		return false;
	if (getEffort() <= 20)
		return false;
	effort -= rand() % 19 + 1;
}
bool Task::isIsolated()const{ return (dependants.size() == 0) && (dependencies.size() == 0); }

Task::TaskExcept::TaskExcept(string description, int ID ) :description(description) { if (ID != -1) { stringstream s; s << ID; description += s.str(); } }
string Task::TaskExcept::operator()(){ return description; }

bool Task::TaskComparatorAlphabetic ::operator()(const Task& t1, const Task& t2) { return t1.name < t2.name; }
bool Task::TaskComparatorAlphabetic ::operator()(const Task* t1, const Task* t2) { return t1->name < t2->name; }
string Task::TaskComparatorAlphabetic::getAbbreviation() const{ return "Alph"; }


bool Task::TaskComparatorID::operator()(const Task& t1, const Task& t2) { return t1.getID() < t2.getID(); };
bool Task::TaskComparatorID::operator()(const Task* t1, const Task* t2) { return t1->getID() < t2->getID(); };
string Task::TaskComparatorID::getAbbreviation() const{ return "ID"; };

bool Task::TaskComparatorEffort ::operator()(const Task& t1, const Task& t2) { return t1.getEffort() < t2.getEffort(); };
bool Task::TaskComparatorEffort ::operator()(const Task* t1, const Task* t2) { return t1->getEffort() < t2->getEffort(); };
string Task::TaskComparatorEffort::getAbbreviation() const{ return "Effort"; };

bool Task::TaskComparatorEstimatedTime ::operator()(const Task& t1, const Task& t2) { return t1.calculateEstimatedTime() < t2.calculateEstimatedTime(); };
bool Task::TaskComparatorEstimatedTime ::operator()(const Task* t1, const Task* t2) { return t1->calculateEstimatedTime() < t2->calculateEstimatedTime(); };
string Task::TaskComparatorEstimatedTime::getAbbreviation() const{ return "Est Time"; };

bool Task::TaskComparatorTimeToCompletion ::operator()(const Task& t1, const Task& t2) { return t1.calculateTimeToCompletion() < t2.calculateTimeToCompletion(); };
bool Task::TaskComparatorTimeToCompletion ::operator()(const Task* t1, const Task* t2) { return t1->calculateTimeToCompletion() < t2->calculateTimeToCompletion(); };
string Task::TaskComparatorTimeToCompletion::getAbbreviation() const{ return "To Complete"; };

bool Task::TaskComparatorNumDependants::operator()(const Task& t1, const Task& t2) { return t1.getDependants().size() < t2.getDependants().size(); };
bool Task::TaskComparatorNumDependants::operator()(const Task* t1, const Task* t2) { return t1->getDependants().size() < t2->getDependants().size(); };
string Task::TaskComparatorNumDependants::getAbbreviation() const{ return "N Dependants"; };

bool Task::TaskComparatorNumDependencies ::operator()(const Task& t1, const Task& t2) { return t1.getDependencies().size() < t2.getDependencies().size(); };
bool Task::TaskComparatorNumDependencies ::operator()(const Task* t1, const Task* t2) { return t1->getDependencies().size() < t2->getDependencies().size(); };
string Task::TaskComparatorNumDependencies::getAbbreviation() const{ return "N Dependencies"; };