#include "Task.h"



int Task::lastID = 0;

int Task::getPriority() const
{
	double sum = calculateEstimatedTime();
	for (size_t i = 0; i < dependants.size(); i++)
		sum += double(dependants.at(i)->getPriority()) / dependencies.size();
	return sum;
};
void Task::setProject(Project* p, bool addTask)
{
	if (p == NULL)
		throw TaskExcept("Invalid Project");
	project = p;
	if (addTask)
		p->addTask(this, false);
}
bool Task::addDependency(Task* t, bool addDependant)
{
	if (t == NULL)
		throw TaskExcept("No Task being added to Task:", ID);
	if (!(*project == *t->project))
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
	if (!(*project == *t->project))
		return false;
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
	for (size_t i = 0; i < this->collaborators.size(); ++i)
	{
		if (*collaborators[i].first == *c1)
		{
			return false;
			//throw TaskExcept("Collaborator already exists");
		}
	}
	collaborators.push_back(make_pair(c1, hours));
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
		sum += collaborators.at(i).second; //soma das horas que a tarefa é trabalhada por semana
	if (sum == 0)
		return -1;//tempo é 'infinito'
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
	Project * ptr = Application::getProjectPtr((int)project);
		project = ptr;
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
	out << t.project->getID() << endl;
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
		throw(TaskExcept("Task has no project"));
	if (removeTask)
		project->removeTask(this, false);
	project = NULL;
	return true;
}
bool Task::removeTrace()//remover todas as referencias de outros objectos à tarefa
{
	project->removeTask(this, false); // remover referencia do projecto à tarefa
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
		return t->removeDependency(this, false);
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