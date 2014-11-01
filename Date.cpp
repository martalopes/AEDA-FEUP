
#include "Date.h"


using namespace std;
bool operator<(const Date& d1, const Date& d2){ return d1.totalseconds < d2.totalseconds; }
bool operator==(const Date& d1, const Date& d2) { return d1.totalseconds == d2.totalseconds; }
bool operator!=(const Date& d1, const Date& d2){ return !(d1 == d2); }
Date operator+(const Date& d1, const Date& d2){ return Date(d1.totalseconds + d2.totalseconds); }
Date operator-(const Date& d1, const Date& d2){ if (d1.totalseconds < d2.totalseconds)throw Date::DateExcept("Invalid Date subtraction"); return Date(d1.totalseconds - d2.totalseconds); }
Date& operator+=(Date& d1, const Date& d2) { d1 = d1 + d2; return d1; }
Date& operator-=(Date& d1, const Date& d2) { d1 = d1 - d2; return d1; }

Date operator+(const Date& d1, const int& i)
{
	return Date(d1.totalseconds + i);
}
Date operator-(const Date& d1, const int& i){ if (d1.totalseconds < i) throw Date::DateExcept("Invalid Date subtraction"); return Date(d1.totalseconds - i); }
Date& operator+=(Date& d1, const int& i) { d1 = d1 + i; return d1; }
Date& operator-=(Date& d1, const int& i) { d1 = d1 - i; return d1; }
