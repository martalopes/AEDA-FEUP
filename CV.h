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
	
	///@brief construtor de um candidato 
	/// @param i numero que desejamos dar ao colaborador
	CV(int i);
	
	///@brief 
	///@return ID do candidato
	int getID()const;

	///@brief 
	///@return titulo do candidato
	string getTitle() const;

	///@brief 
	///@return nome do candidato
	string getName() const;

	///@brief 
	///@return contacto do candidato
	string getContact() const;

	///@brief 
	///@return endereco do candidato
	string getAddress() const;

	///@brief 
	///@return se ele ja trabalhou na empresa ou nao
	bool getPreviouslyEmployed() const;

	///@brief 
	///@return experiencia do candidato
	size_t getExperience() const;

	///@brief 
	///@return skills do candidato
	size_t getNumSkills() const;

	///passa o ID para string
	string toString() const;

	///@brief escolhe um titulo para o candidato
	/// @param newTitle titulo que vai ser escolhido
	void setTitle(string newTitle);
	///@brief escolhe um nome para o candidato
	/// @param newName nome que vai ser escolhido
	void setName(string newName);
	///@brief escolhe um contacto para o candidato
	/// @param newContact contacto que vai ser escolhido
	void setContact(string newContact);
	///@brief escolhe um endereco para o candidato
	/// @param newAddres endereco que vai ser escolhido
	void setAddress(string newAddress);
	///@brief escolhe se o candidato ja esteve empregue nesta empresa ou nao
	/// @param newPE o estado do candidato (empregue anteriormente ou nao)
	void setPreviouslyEmployed(bool newPE);
	///@brief da uma experiencia ao candidato
	/// @param newExp experiencia que vai ser escolhida
	void setExperience(size_t newExp);
	///@brief escolhe o numero de skills para o candidato
	/// @param newNumSkills numero de skills que vao ser escolhidas
	void setNumSkills(size_t newNumSkills);

	///@brief cria um novo colaborador dependendo do seu titulo (programmer, architect, manager, tester)
	Collaborator* toCollaborator(int maxWorkingHours)const;

	///@brief retorna todas as informacoes sobre o candidato
	///@param out stream de saida
	///@param c candidato
	friend ostream & operator<<(ostream& out, const CV& c);

	///@brief vai inserir todas as informacoes sobre o candidato
	///@param in stream de entrada
	///@param c candidato
	friend istream & operator>>(istream& in, CV& c);

	///@brief operador menor associado aos candidatos
	///@brief verifica qual apresenta melhor CV
	///@param c2 candidato
	///@return compara os candidatos
	bool operator< (const CV& c2) const;

	///@brief operador de igualdade associado aos candidatos
	///@brief verifica se os seus ID's sao iguais
	///@param c2 candidato a ser comparado
	///@return ve se os candidatos são iguais
	bool operator==(const CV& c2) const;

	///retorna o valor do candidato
	int getValue() const;
};




#endif