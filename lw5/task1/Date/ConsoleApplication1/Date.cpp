#include "Date.h"
#include <map>
#include <vector>
#include <regex>

CDate::CDate(int day, Month month, int year)
{
	m_timestamp = CalculateTimestampFromRawDate({day, static_cast<signed long long>(month), year});
}

CDate::CDate(int timestamp)
{
	m_timestamp = timestamp;
}

int CDate::GetDay() const
{
	return CalculateRawDateFromTimestamp().day;
}

Month CDate::GetMonth() const
{
	return static_cast<Month>(CalculateRawDateFromTimestamp().day);
}

int CDate::GetYear() const
{
	return CalculateRawDateFromTimestamp().year;
}

CDate::RawDate CDate::CalculateRawDateFromTimestamp() const
{
	int currTimestamp = m_timestamp;
	CDate::RawDate date;

	int year = START_YEAR;
	while (true)
	{
		bool isLeapYear = IsLeapYear(year + 1);

		if ((isLeapYear && currTimestamp < NUMBER_OF_DAYS_IN_LEAP_YEAR)
			|| (!isLeapYear && currTimestamp < NUMBER_OF_DAYS_IN_YEAR))
		{
			break;
		}

		year++;
		currTimestamp -= isLeapYear
			? NUMBER_OF_DAYS_IN_LEAP_YEAR
			: NUMBER_OF_DAYS_IN_YEAR;
	}
	date.year = year;

	int month = 1;
	while (true)
	{
		auto daysInMonth = M_MONTH_TO_NUMBER_OF_DAYS.at(month);
		int numberOfDaysInMonth = IsLeapYear(year)
			? daysInMonth.back()
			: daysInMonth[0];

		if (currTimestamp < numberOfDaysInMonth)
		{
			break;
		}

		currTimestamp -= numberOfDaysInMonth;
		month++;
	}
	date.month = month;
	date.day = currTimestamp;

	return date;
}

int CDate::CalculateTimestampFromRawDate(RawDate date) const
{
	int timestamp = date.day;

	while (date.month != 1)
	{
		auto daysInMonth = M_MONTH_TO_NUMBER_OF_DAYS.at(date.month);
		int numberOfDaysInMonth = IsLeapYear(date.year)
			? daysInMonth.back()
			: daysInMonth[0];

		timestamp += numberOfDaysInMonth;
		date.month--;
	}

	while (date.year > START_YEAR)
	{
		timestamp += IsLeapYear(date.year)
			? NUMBER_OF_DAYS_IN_LEAP_YEAR
			: NUMBER_OF_DAYS_IN_YEAR;
		date.year--;
	}

	return timestamp;
}

bool CDate::IsLeapYear(int year) const
{
	return year % 400 == 0
		|| ((year % 4 == 0) && (year % 100 != 0));
}

WeekDay CDate::GetWeekDay()const
{
	return static_cast<WeekDay>(m_timestamp);
};

bool CDate::IsValid()const
{
	return m_timestamp > 0
		&& CalculateRawDateFromTimestamp().year <= MAX_YEAR;
};

bool CDate::operator ==(const CDate& date) const
{
	return m_timestamp == date.m_timestamp;
}

bool CDate::operator !=(const CDate& date) const
{
	return m_timestamp != date.m_timestamp;
}

bool CDate::operator <(const CDate& date) const
{
	return m_timestamp < date.m_timestamp;
}

bool CDate::operator >(const CDate& date) const
{
	return m_timestamp > date.m_timestamp;
}

bool CDate::operator <=(const CDate& date) const
{
	return m_timestamp <= date.m_timestamp;
}

bool CDate::operator >=(const CDate& date) const
{
	return m_timestamp >= date.m_timestamp;
}

CDate CDate::operator +(const CDate& date) const
{
	return CDate{m_timestamp + date.m_timestamp};
}

CDate CDate::operator +(int days) const
{
	return CDate{m_timestamp + days};
}

CDate CDate::operator -(const CDate& date) const
{
	return CDate{m_timestamp - date.m_timestamp};
}

CDate CDate::operator -(int days) const
{
	return CDate{m_timestamp - days};
}

CDate& CDate::operator +=(const CDate& date)
{
	m_timestamp += date.m_timestamp;
	return *this;
}

CDate& CDate::operator +=(int days)
{
	m_timestamp += days;
	return *this;
}

CDate& CDate::operator ++()
{
	m_timestamp++;
	return *this;
}

CDate CDate::operator ++(int)
{
	CDate prevDate{m_timestamp};

	++*this;
	return prevDate;
}

CDate& CDate::operator -=(const CDate& date)
{
	m_timestamp -= date.m_timestamp;

	return *this;
}

CDate& CDate::operator -=(int days)
{
	m_timestamp -= days;

	return *this;
}

CDate& CDate::operator --()
{
	m_timestamp--;

	return *this;
}

CDate CDate::operator --(int)
{
	CDate prevDate{m_timestamp};

	--*this;
	return prevDate;
}

std::ostream& CDate::operator <<(std::ostream& stream)
{
	stream << GetDay() << '.' << static_cast<unsigned>(GetMonth()) << '.' << GetYear();
	return stream;
}

std::istream& CDate::operator >>(std::istream& stream)
{
	std::string value;
	const std::regex r(R"([0-9]{2}.[0-9]{2}.[0-9]{4})");
	std::smatch m;
	stream >> value;

	if (std::regex_match(value, m, r))
	{
		int day = stoi(m[0].str().substr(0, 2));
		int month = stoi(m[0].str().substr(3, 2));
		int year = stoi(m[0].str().substr(6, 4));

		m_timestamp = CalculateTimestampFromRawDate({ day, month, year });
	}

	return stream;
}