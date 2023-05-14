#pragma once
#include <iostream>
#include <map>
#include <vector>

enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timestamp = 0);

	unsigned GetDay()const;
	Month GetMonth()const;
	unsigned GetYear()const;
	WeekDay GetWeekDay()const;
	bool IsValid()const;

	bool operator ==(const CDate& date)const;
	bool operator !=(const CDate& date)const;
	bool operator <(const CDate& date)const;
	bool operator >(const CDate& date)const;
	bool operator >=(const CDate& date)const;
	bool operator <=(const CDate& date)const;

	int operator -(const CDate& date)const;
	CDate operator +(unsigned days)const;
	CDate operator -(unsigned days)const;

	CDate& operator ++();
	CDate operator ++(int);
	CDate& operator --();
	CDate operator --(int);
	CDate& operator +=(unsigned days);
	CDate& operator -=(unsigned days);

	friend std::ostream& operator <<(std::ostream& stream, const CDate& date);
	friend std::istream& operator >>(std::istream& stream, CDate& date);

private:
	unsigned m_timestamp;
};