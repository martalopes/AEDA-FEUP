#include "Application.h"

Application& Application::addCollaborator(Collaborator* c)
{
	for(size_t i = 0; i < collaborators.size(); ++i)
		if(*collaborators.at(i) == *c)
			throw ApplicationExcept("Collaborator already exists");
	collaborators.push_back(c);
	return *this;
}
