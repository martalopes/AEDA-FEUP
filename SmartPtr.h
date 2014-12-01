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
	SmartPtr() : pointee(NULL) { comparison = new Comparison() };
	SmartPtr(T* pointee) : pointee(pointee) { comparison = new Comparison(); };
	SmartPtr(Comparison * c) : pointee(NULL) { comparison = new Comparison(c) };
	SmartPtr(T* pointee, Comparison* c) : pointee(pointee) { comparison = new Comparison(*c); };
	SmartPtr(const SmartPtr& p2) : pointee(p2.pointee) { comparison = new Comparison(*p2.comparison); };
	void setPointer(T* t){ pointee = t; };
	void setComparison(Comparison* c){ delete comparison; comparison = new Comparison(*c); };
	T& operator*(){ if (pointee == NULL) throw NullDereference(); return *pointee; };
	T* operator->(){ return pointee; };
	T* getPointer(){ return pointee; };
	~SmartPtr(){ delete comparison; };
	int operator-(const SmartPtr& p2) const { return this->pointee - p2.pointee; };
	int operator+(const SmartPtr& p2) const { return this->pointee + p2.pointee; };
	SmartPtr operator-(int i) const { return SmartPtr(this->pointee - i); };
	SmartPtr operator+(int i) const { return SmartPtr(this->pointee + i); };
	SmartPtr operator++(int) { SmartPtr(*this) out;  pointee++; return out; };
	SmartPtr& operator++() { ++pointee; return *this; };
	SmartPtr& operator=(const SmartPtr& c2){ this->pointee = c2.pointee; delete comparison; this->comparison = new Comparison(*c2.comparison); return *this; };
	//SmartPtr& operator=(T* pointee){ this->pointee = pointee; this->comparison = new Comparison(); };
	bool operator<(const SmartPtr<T, Comparison>& p2) const { return (*comparison)(*this->pointee, *p2.pointee); };
	bool isNull() const { return pointee == NULL; };
	void deletePtr(){ if (pointee == NULL) throw NullDelete(); delete pointee; };
private:
	T* pointee;
	Comparison* comparison;
};
#endif