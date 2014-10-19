
#include "Date.h"

using namespace std;

//Date::Date(int day, int month, int year, int hours = 0, int minutes = 0, int seconds = 0)
//{
//	this->day = day;
//	this->month = month;
//	this->year = year;
//	this->hours = hours;
//	this->minutes = minutes;
//	this->seconds = seconds;
//}
//
//int Date::getDay() const	{ return this->day; }
//int Date::getMonth() const	{ return this->month; }
//int Date::getYear() const	{ return this->year; }
//int Date::getHours() const	{ return this->hours; }
//int Date::getMinutes() const	{ return this->minutes; }
//int Date::getSeconds() const	{ return this->seconds; }


bool Date::operator<(const Date& d2) const
{
	if (this->year < d2.year)
		return true;
	 if (this->month < d2.month)
		return true;
	 if (this->day < d2.day)
		 return true;
	 if (this->hours < d2.hours)
		 return true;
	 if (this->minutes < d2.minutes)
		 return true;
	 if (this->seconds < d2.seconds)
		 return true;
	 else return false;

}

string Date::printDate() const
{
	stringstream data;

	data << day << "/" << month << "/" << year ;

	return data.str();	
}

string Date::printTime() const
{
	stringstream tempo;

	tempo << hours << ":" << minutes << ":" << seconds;

	return tempo.str();
}