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
	CDate(int day, Month month, int year);
	CDate(int timestamp = 0);

	int GetDay()const;
	Month GetMonth()const;
	int GetYear()const;
	WeekDay GetWeekDay()const;
	bool IsValid()const;

	bool operator ==(const CDate& date)const;
	bool operator !=(const CDate& date)const;
	bool operator <(const CDate& date)const;
	bool operator >(const CDate& date)const;
	bool operator >=(const CDate& date)const;
	bool operator <=(const CDate& date)const;

	CDate operator +(const CDate& date)const;
	CDate operator -(const CDate& date)const;
	CDate operator +(int days)const;
	CDate operator -(int days)const;

	CDate& operator ++();
	CDate operator ++(int);
	CDate& operator --();
	CDate operator --(int);
	CDate& operator +=(const CDate& date);
	CDate& operator -=(const CDate& date);
	CDate& operator +=(int days);
	CDate& operator -=(int days);

	std::ostream& operator <<(std::ostream& stream);
	std::istream& operator >>(std::istream& stream);

private:
	const WeekDay WEEKDAY_OF_FIRST_DAY = WeekDay::THURSDAY;
	const int START_YEAR = 1970;
	const int MAX_YEAR = 9999;
	const int START_MONTH = 0;
	const int NUMBER_OF_DAYS_IN_WEEK = 7;
	const int NUMBER_OF_DAYS_IN_YEAR = 365;
	const int NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;

	const std::map<int, std::vector<int>> M_MONTH_TO_NUMBER_OF_DAYS = {
		{1, {31}},
		{2, {28, 29}},
		{3, {31}},
		{4, {30}},
		{5, {31}},
		{6, {30}},
		{7, {31}},
		{8, {31}},
		{9, {30}},
		{10, {31}},
		{11, {30}},
		{12, {31}},
	};

	int m_timestamp;

	struct RawDate
	{
		int day;
		int month;
		int year;
	};

	RawDate CalculateRawDateFromTimestamp()const;
	bool IsLeapYear(int year)const;
	int CalculateTimestampFromRawDate(RawDate date)const;
};