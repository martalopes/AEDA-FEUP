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
	bool previously_employed;  /// diz-nos se o candidato ja trabalhou na empresa
	size_t experience;
	size_t num_skills;
public:
	///construtor por defeito
	CV();

	///construtor de um candidato aleatorio
	CV(string name, string contact, string address, string title, bool previously_employed, size_t experience, size_t num_skills);
	
	///construtor de um candidato 
	/// @param i número que desejamos dar ao colaborador
	CV(int i);
	
	///@return ID do candidato
	int getID()const;
	///@return titulo do candidato
	string getTitle() const;
	///@return nome do candidato
	string getName() const;
	///@return contacto do candidato
	string getContact() const;
	///@return endereço do candidato
	string getAddress() const;
	///@return se ele já trabalhou na empresa ou nao
	bool getPreviouslyEmployed() const;
	///@return experiencia do candidato
	size_t getExperience() const;
	///@return skills do candidato
	size_t getNumSkills() const;

	string toString() const;

	/// escolhe um titulo para o candidato
	/// @param newTitle titulo que vai ser escolhido
	void setTitle(string newTitle);
	/// escolhe um nome para o candidato
	/// @param newName nome que vai ser escolhido
	void setName(string newName);
	/// escolhe um contacto para o candidato
	/// @param newContact contacto que vai ser escolhido
	void setContact(string newContact);
	/// escolhe um endereco para o candidato
	/// @param newAddres endereco que vai ser escolhido
	void setAddress(string newAddress);
	/// escolhe se o candidato já esteve empregue nesta empresa ou nao
	/// @param newPE o estado do candidato (empregue anteriormente ou nao)
	void setPreviouslyEmployed(bool newPE);
	/// da uma experiencia ao candidato
	/// @param newExp experiencia que vai ser escolhida
	void setExperience(size_t newExp);
	/// escolhe o numero de skills para o candidato
	/// @param newNumSkills numero de skills que vao ser escolhidas
	void setNumSkills(size_t newNumSkills);

	///cria um novo colaborador dependendo do seu titulo (programmer, architect, manager, tester)
	Collaborator* toCollaborator(int maxWorkingHours)const;

	
	friend ostream & operator<<(ostream& out, const CV& c);
	friend istream & operator>>(istream& in, CV& c);
	bool operator< (const CV& c2) const;
	bool operator==(const CV& c2) const;

	int getValue() const;
};




#endif