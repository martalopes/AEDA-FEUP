#ifndef SMART_PTR
#define SMART_PTR

using namespace std;

/*
Class SmartPtr:
Vai servir para conseguirmos estabelecer comparacoes nos elementos da BST.
*/

template<class T, class Comparison = less<T>>
class SmartPtr
{
public:
	class NullDereference
	{
	public:
		string operator()() { return "NULL pointer was dereferenced\n" };
	};
	class NullDelete
	{
	public:
		string operator()() { return "NULL pointer was deleted\n" };
	};

	///construtor com apontador nulo e forma de comparacao vazia
	SmartPtr() : pointee(NULL) { comparison = new Comparison() };
	///@brief construtor com apontador igual ao apontador pretendido pelo utlizador e forma de comparacao vazia
	///@param pointee apontador 
	SmartPtr(T* pointee) : pointee(pointee) { comparison = new Comparison(); };
	///@brief construtor com apontador nulo e a forma de comparacao pretendida pelo utilizador
	///@param c forma de comparacao
	SmartPtr(Comparison * c) : pointee(NULL) { comparison = new Comparison(c) };
	///@brief construtor com apontador e a forma de comparacao escolhidos pelo utilizador
	///@param pointee apontador
	///@param c forma de comparacao
	SmartPtr(T* pointee, Comparison* c) : pointee(pointee) { comparison = new Comparison(*c); };
	///@brief construtor em que a forma de comparacao vai ser a forma de comparacao de p2
	///@param p2 elemento constante da classe SmartPtr
	SmartPtr(const SmartPtr& p2) : pointee(p2.pointee) { comparison = new Comparison(*p2.comparison); };
	///@brief modifica o valor de pointee para t
	///@param t apontador
	void setPointer(T* t){ pointee = t; };
	///@brief modifica a forma de comparacao para c
	///@param c forma de comparacao
	void setComparison(Comparison* c){ delete comparison; comparison = new Comparison(*c); };
	///@throw quando o apontador e nulo
	///@return apontador
	T& operator*(){ if (pointee == NULL) throw NullDereference(); return *pointee; };
	///@return apontador
	T* operator->(){ return pointee; };
	///@return apontador
	T* getPointer(){ return pointee; };
	///destrutor onde vai eliminar a comparacao
	~SmartPtr(){ delete comparison; };
	///@param p2 elemento constante da classe p2
	///@return o apontador que se encontra na diferenca entre os dois apontadores
	int operator-(const SmartPtr& p2) const { return this->pointee - p2.pointee; };
	///@param p2 elemento constante da classe p2
	///@return o apontador que resulta da soma dos dois apontadores
	int operator+(const SmartPtr& p2) const { return this->pointee + p2.pointee; };
	///@param i inteiro
	///@return o apontador que esta i vezes atras de pointee
	SmartPtr operator-(int i) const { return SmartPtr(this->pointee - i); };
	///@param i inteiro
	///@return o apontador que esta i vezes a frente de pointee
	SmartPtr operator+(int i) const { return SmartPtr(this->pointee + i); };
	SmartPtr operator++(int) { SmartPtr(*this) out;  pointee++; return out; };
	SmartPtr& operator++() { ++pointee; return *this; };
	///@param c2 elemento constante da classe SmartPtr
	///@return um novo elemento com o apontador e a forma de comparacao iguais a c2
	SmartPtr& operator=(const SmartPtr& c2){ this->pointee = c2.pointee; delete comparison; this->comparison = new Comparison(*c2.comparison); return *this; };
	//SmartPtr& operator=(T* pointee){ this->pointee = pointee; this->comparison = new Comparison(); };
	///@param p2 elemento constante de SmartPtr
	///@return 
	bool operator<(const SmartPtr<T, Comparison>& p2) const { return (*comparison)(*this->pointee, *p2.pointee); }; 
	///@return verifica se o apontador e nulo
	bool isNull() const { return pointee == NULL; };
	///@brief o elimina apontador
	///@throw se o apontador nao existe
	void deletePtr(){ if (pointee == NULL) throw NullDelete(); delete pointee; };
private:
	T* pointee;
	Comparison* comparison;
};
#endif