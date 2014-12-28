#ifndef SMART_PTR
#define SMART_PTR

using namespace std;

//template<class T, class Comparison = less<T>>
//class SmartPtr
//{
//public:
//	class NullDereference
//	{
//	public:
//		string operator()() { return "NULL pointer was dereferenced\n" };
//	};
//	class NullDelete
//	{
//	public:
//		string operator()() { return "NULL pointer was deleted\n" };
//	};
//	SmartPtr() : pointee(NULL) { comparison = new Comparison() };
//	SmartPtr(T* pointee) : pointee(pointee) { comparison = new Comparison(); };
//	SmartPtr(Comparison * c) : pointee(NULL) { comparison = new Comparison(c) };
//	SmartPtr(T* pointee, Comparison* c) : pointee(pointee) { comparison = new Comparison(c); };
//	SmartPtr(const SmartPtr& p2) : t(p2.pointee) { comparison = new Comparison(p2.comparison); };
//	void setPointee(T* t){ pointee = t; };
//	void setComparison(Comparison* c){ delete comparison; comparison = new Comparison(c); };
//	T& operator*(){ if (pointee == NULL) throw NullDereference(); return *pointee; };
//	T* operator->(){ return pointee; };
//	T* getPointee(){ return pointee; };
//	~SmartPtr(){ delete comparison; };
//	int operator-(const SmarPtr& p2) const { return this->pointee - p2.pointee; };
//	int operator+(const SmarPtr& p2) const { return this->pointee + p2.pointee; };
//	SmartPtr operator-(int i) const { return SmartPtr(this->pointee - i); };
//	SmartPtr operator+(int i) const { return SmrtPtr(this->pointee + i); };
//	SmartPtr operator++(int) { SmartPtr(*this) out;  pointee++; return out; };
//	SmartPtr& operator++() { ++pointee; return *this; };
//	SmartPtr& operator=(const SmartPtr& c2){ this->pointee = c2.pointee; this->comparison = new Comparison(c2.comparison); };
//	//SmartPtr& operator=(T* pointee){ this->pointee = pointee; this->comparison = new Comparison(); };
//	bool operator<(SmartPtr& p2) const { return (*comparison)(*this, p2); };
//	bool isNull() const { return pointee == NULL; };
//	void deletePtr(){ if (pointee == NULL) throw NullDelete(); delete pointee; };
//private:
//	T* pointee;
//	Comparison* comparison;
//};

/*
Class SmartPtr:
Vai servir para conseguirmos estabelecer compara��es nos elementos da BST.
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

	///construtor com apontador nulo e forma de compara��o vazia
	SmartPtr() : pointee(NULL) { comparison = new Comparison() };
	///@param pointee apontador 
	///construtor com apontador igual ao apontador pretendido pelo utlizador e forma de compara��o vazia
	SmartPtr(T* pointee) : pointee(pointee) { comparison = new Comparison(); };
	///@param c forma de compara��o
	///construtor com apontador nulo e a forma de compara��opretendida pelo utilizador
	SmartPtr(Comparison * c) : pointee(NULL) { comparison = new Comparison(c) };
	///@param pointee apontador
	///@param c forma de compara��o
	///construtor com apontador e a forma de compara��o escolhidos pelo utilizador
	SmartPtr(T* pointee, Comparison* c) : pointee(pointee) { comparison = new Comparison(*c); };
	///@param p2 elemento constante da classe SmartPtr
	///construtor em que a forma de compara��o vai ser a forma de compara��o de p2
	SmartPtr(const SmartPtr& p2) : pointee(p2.pointee) { comparison = new Comparison(*p2.comparison); };
	///@param t apontador
	///modifica o valor de pointee para t
	void setPointer(T* t){ pointee = t; };
	///@param c forma de compara��o
	///modifica a forma de compara��o para c
	void setComparison(Comparison* c){ delete comparison; comparison = new Comparison(*c); };
	///@throw quando o apontador � nulo
	///@return apontador
	T& operator*(){ if (pointee == NULL) throw NullDereference(); return *pointee; };
	///@return apontador
	T* operator->(){ return pointee; };
	///@return apontador
	T* getPointer(){ return pointee; };
	///destrutor onde vai eliminar a compara��o
	~SmartPtr(){ delete comparison; };
	///@param p2 elemento constante da classe p2
	///@return o apontador que se encontra na diferen�a entre os dois apontadores
	int operator-(const SmartPtr& p2) const { return this->pointee - p2.pointee; };
	///@param p2 elemento constante da classe p2
	///@return o apontador que resulta da soma dos dois apontadores
	int operator+(const SmartPtr& p2) const { return this->pointee + p2.pointee; };
	///@param i inteiro
	///@return o apontador que est� i vezes atr�s de pointee
	SmartPtr operator-(int i) const { return SmartPtr(this->pointee - i); };
	///@param i inteiro
	///@return o apontador que est� i vezes � frente de pointee
	SmartPtr operator+(int i) const { return SmartPtr(this->pointee + i); };
	SmartPtr operator++(int) { SmartPtr(*this) out;  pointee++; return out; };
	SmartPtr& operator++() { ++pointee; return *this; };
	///@param c2 elemento constante da calsse SmartPtr
	///@return um novo elemento com o apontador e a forma de compara��o iguais a c2
	SmartPtr& operator=(const SmartPtr& c2){ this->pointee = c2.pointee; delete comparison; this->comparison = new Comparison(*c2.comparison); return *this; };
	//SmartPtr& operator=(T* pointee){ this->pointee = pointee; this->comparison = new Comparison(); };
	///@param p2 elemento constante de SmartPtr
	///@return 
	bool operator<(const SmartPtr<T, Comparison>& p2) const { return (*comparison)(*this->pointee, *p2.pointee); };
	///@return verifica se o apontador � nulo
	bool isNull() const { return pointee == NULL; };
	///@throw se o apontador n�o existe
	///vai eliminar o apontador
	void deletePtr(){ if (pointee == NULL) throw NullDelete(); delete pointee; };
private:
	T* pointee;
	Comparison* comparison;
};
#endif