#include "Cursor.h"

Cursor::Cursor()
{
	this->pos = 0;
	this->pos_max = 1;
}
Cursor::Cursor(int pos_max)
{
	this->pos = 0;
	this->pos_max = pos_max;
}
bool Cursor::changeMax(int max)
{
	if (this->pos_max == max)
		return false;
	else
	{
		this->pos = 0;
		this->pos_max = max;
		return true;
	}
}
Cursor::Cursor(int pos, int pos_max)
{
	this->pos = pos;
	this->pos_max = pos_max;
}
bool Cursor::dec()
{
	if (this->pos_max == 0)
		return false;
	else if (this->pos > 0)
		pos--;
	else this->pos = this->pos_max;
	return true;
}
bool Cursor::inc()
{
	if (this->pos_max == 0)
		return false;
	if (this->pos < pos_max)
		pos++;
	else this->pos = 0;
	return true;
}
bool Cursor::setPosition(int position)
{
	if (position >= 0 && position <= pos_max)
	{
		this->pos = position;
		return true;
	}
	else return false;
}

TwoCursor::TwoCursor() : Cursor()
{
	this->pos2 = 0;
	this->pos_max2 = 256;
}
TwoCursor::TwoCursor(int pos_max, int pos_max2) : Cursor(pos_max)
{
	this->pos2 = 0;
	this->pos_max2 = pos_max2;
}
bool TwoCursor::changeMax2(int max2)
{
	if (this->pos_max2 == max2)
		return false;
	else
	{
		this->pos2 = 0;
		this->pos_max2 = max2;
		return true;
	}
}
TwoCursor::TwoCursor(int pos, int pos_max, int pos2, int pos_max2) : Cursor(pos, pos_max)
{
	this->pos2 = pos2;
	this->pos_max2 = pos_max2;
}
bool TwoCursor::dec2()
{
	if (this->pos_max2 == 0)
		return false;
	else if (this->pos2 > 0)
		pos2--;
	else this->pos2 = this->pos_max2;
	return true;
}
bool TwoCursor::inc2()
{
	if (this->pos_max2 == 0)
		return false;
	if (this->pos2 < pos_max2)
		pos2++;
	else this->pos2 = 0;
	return true;
}
bool TwoCursor::setPosition2(int position)
{
	if (position >= 0 && position <= pos_max2)
	{
		this->pos2 = position;
		return true;
	}
	else return false;
}