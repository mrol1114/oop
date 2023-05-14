#include "Date.h"
#include <map>
#include <vector>
#include <regex>

namespace
{
	struct RawDate
	{
		unsigned day;
		Month month;
		unsigned year;
	};

	const unsigned WEEKDAY_OF_FIRST_DAY = 4;
	const RawDate START_DATE = { 1, Month::JANUARY, 1970 };
	const unsigned MAX_YEAR = 9999;
	const unsigned NUMBER_OF_DAYS_IN_WEEK = 7;
	const unsigned NUMBER_OF_DAYS_IN_YEAR = 365;
	const unsigned NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;
	const unsigned COUNT_DAYS_IN_400_YEARS = 97 * NUMBER_OF_DAYS_IN_LEAP_YEAR
		+ 303 * NUMBER_OF_DAYS_IN_YEAR;
	const unsigned COUNT_DAYS_IN_100_YEARS = 24 * NUMBER_OF_DAYS_IN_LEAP_YEAR
		+ 76 * NUMBER_OF_DAYS_IN_YEAR;
	const unsigned COUNT_DAYS_IN_4_YEARS = NUMBER_OF_DAYS_IN_LEAP_YEAR
		+ 3 * NUMBER_OF_DAYS_IN_YEAR;
	const unsigned COUNT_DAYS_IN_FEBRUARY_IN_LEAP_YEAR = 29;
	const unsigned INVALID_TIMESTAMP_VALUE = std::numeric_limits<unsigned int>::max();

	const std::map<Month, unsigned> M_MONTH_TO_NUMBER_OF_DAYS = {
		{Month::JANUARY, 31},
		{Month::FEBRUARY, 28},
		{Month::MARCH, 31},
		{Month::APRIL, 30},
		{Month::MAY, 31},
		{Month::JUNE, 30},
		{Month::JULY, 31},
		{Month::AUGUST, 31},
		{Month::SEPTEMBER, 30},
		{Month::OCTOBER, 31},
		{Month::NOVEMBER, 30},
		{Month::DECEMBER, 31},
	};

	const std::map<Month, Month> NEXT_MONTH = {
		{Month::JANUARY, Month::FEBRUARY},
		{Month::FEBRUARY, Month::MARCH},
		{Month::MARCH, Month::APRIL},
		{Month::APRIL, Month::MAY},
		{Month::MAY, Month::JUNE},
		{Month::JUNE, Month::JULY},
		{Month::JULY, Month::AUGUST},
		{Month::AUGUST, Month::SEPTEMBER},
		{Month::SEPTEMBER, Month::OCTOBER},
		{Month::OCTOBER, Month::NOVEMBER},
		{Month::NOVEMBER, Month::DECEMBER},
		{Month::DECEMBER, Month::JANUARY},
	};

	bool IsLeapYear(unsigned year)
	{
		return year % 400 == 0
			|| ((year % 4 == 0) && (year % 100 != 0));
	}

	unsigned GetNumberOfDaysInMonth(Month month, unsigned year)
	{
		if (IsLeapYear(year) && month == Month::FEBRUARY)
		{
			return COUNT_DAYS_IN_FEBRUARY_IN_LEAP_YEAR;
		}

		return M_MONTH_TO_NUMBER_OF_DAYS.at(month);
	}

	unsigned GetCountOfDaysInYear(unsigned year)
	{
		unsigned count400years = year / 400;
		unsigned count100years = year / 100;
		unsigned count4years = year / 4;

		unsigned countLeapYears = count400years
			+ count4years - count100years;

		unsigned countYears = year - countLeapYears;

		return countLeapYears * NUMBER_OF_DAYS_IN_LEAP_YEAR
			+ countYears * NUMBER_OF_DAYS_IN_YEAR;
	}

	unsigned GetCountOfDaysBeforeMonth(Month month, unsigned year)
	{
		unsigned days = 0;

		Month curMonth = Month::JANUARY;
		while (curMonth != month)
		{
			unsigned numberOfDaysInMonth = GetNumberOfDaysInMonth(curMonth, year);

			days += numberOfDaysInMonth;
			curMonth = NEXT_MONTH.at(curMonth);
		}

		return days;
	}

	unsigned GetCountOfDaysInDate(RawDate date)
	{
		return GetCountOfDaysInYear(date.year)
			+ GetCountOfDaysBeforeMonth(date.month, date.year)
			+ date.day - 1;
	}

	unsigned CalculateTimestampFromRawDate(RawDate date)
	{
		return GetCountOfDaysInDate(date) - GetCountOfDaysInDate(START_DATE);
	}

	unsigned GetYearFromTimestamp(unsigned& timestamp)
	{
		unsigned year = timestamp / COUNT_DAYS_IN_400_YEARS * 400;
		timestamp %= COUNT_DAYS_IN_400_YEARS;

		year += timestamp / COUNT_DAYS_IN_100_YEARS * 100;
		timestamp %= COUNT_DAYS_IN_100_YEARS;

		year += timestamp / COUNT_DAYS_IN_4_YEARS * 4;
		timestamp %= COUNT_DAYS_IN_4_YEARS;

		year += timestamp / NUMBER_OF_DAYS_IN_YEAR;
		timestamp %= NUMBER_OF_DAYS_IN_YEAR;

		return year;
	}

	Month GetMonthFromTimestamp(unsigned& timestamp, unsigned year)
	{
		Month month = Month::JANUARY;
		while (month != Month::DECEMBER)
		{
			unsigned numberOfDaysInMonth = GetNumberOfDaysInMonth(month, year);

			if (timestamp < numberOfDaysInMonth)
			{
				break;
			}

			timestamp -= numberOfDaysInMonth;
			month = NEXT_MONTH.at(month);
		}

		return month;
	}

	RawDate CalculateRawDateFromTimestamp(unsigned timestamp)
	{
		unsigned currTimestamp = timestamp + GetCountOfDaysInDate(START_DATE);

		unsigned year = GetYearFromTimestamp(currTimestamp);
		Month month = GetMonthFromTimestamp(currTimestamp, year);

		return {currTimestamp + 1, month, year};
	}

	void ValidateDate(RawDate date)
	{
		if (date.year < START_DATE.year)
		{
			throw std::invalid_argument("Year must be greater or equal to 1970");
		}

		if (date.year > MAX_YEAR)
		{
			throw std::invalid_argument("Year must be lower than 9999");
		}

		if (date.day > GetNumberOfDaysInMonth(date.month, date.year))
		{
			throw std::invalid_argument("Invalid number of days in month");
		}
	}
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	ValidateDate({day, month, year});
	m_timestamp = CalculateTimestampFromRawDate({day, month, year});
}

CDate::CDate(unsigned timestamp)
{
	if (CalculateRawDateFromTimestamp(timestamp).year > MAX_YEAR)
	{
		throw std::invalid_argument("");
	}

	m_timestamp = timestamp;
}

unsigned CDate::GetDay() const
{
	return CalculateRawDateFromTimestamp(m_timestamp).day;
}

Month CDate::GetMonth() const
{
	return CalculateRawDateFromTimestamp(m_timestamp).month;
}

unsigned CDate::GetYear() const
{
	return CalculateRawDateFromTimestamp(m_timestamp).year;
}

WeekDay CDate::GetWeekDay()const
{
	return static_cast<WeekDay>((m_timestamp + WEEKDAY_OF_FIRST_DAY) % NUMBER_OF_DAYS_IN_WEEK);
};

bool CDate::IsValid()const
{
	return m_timestamp != INVALID_TIMESTAMP_VALUE
		&& CalculateRawDateFromTimestamp(m_timestamp).year <= MAX_YEAR;
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

CDate CDate::operator +(unsigned days) const
{
	if (!IsValid())
	{
		return *this;
	}

	return CDate{m_timestamp + days};
}

int CDate::operator -(const CDate& date) const
{
	if (!IsValid())
	{
		return date.m_timestamp;
	}

	return m_timestamp - date.m_timestamp;
}

CDate CDate::operator -(unsigned days) const
{
	if (!IsValid())
	{
		return *this;
	}

	return CDate{m_timestamp < days ? INVALID_TIMESTAMP_VALUE : m_timestamp - days};
}

CDate& CDate::operator +=(unsigned days)
{
	if (!IsValid())
	{
		return *this;
	}

	m_timestamp += days;
	return *this;
}

CDate& CDate::operator ++()
{
	if (!IsValid())
	{
		return *this;
	}

	m_timestamp++;
	return *this;
}

CDate CDate::operator ++(int)
{
	if (!IsValid())
	{
		return *this;
	}

	CDate prevDate{m_timestamp};

	++*this;
	return prevDate;
}

CDate& CDate::operator -=(unsigned days)
{
	if (!IsValid())
	{
		return *this;
	}

	m_timestamp = m_timestamp < days
		? INVALID_TIMESTAMP_VALUE : m_timestamp - days;

	return *this;
}

CDate& CDate::operator --()
{
	if (!IsValid())
	{
		return *this;
	}

	m_timestamp = m_timestamp == 0
		? INVALID_TIMESTAMP_VALUE : m_timestamp - 1;

	return *this;
}

CDate CDate::operator --(int)
{
	if (!IsValid())
	{
		return *this;
	}

	CDate prevDate{m_timestamp};

	--*this;
	return prevDate;
}

std::ostream& operator <<(std::ostream& stream, const CDate& date)
{
	if (!date.IsValid())
	{
		stream << "INVALID";
	}
	else
	{
		std::string month = date.GetMonth() < Month::OCTOBER
			? "0" + std::to_string(static_cast<unsigned>(date.GetMonth()))
			: std::to_string(static_cast<unsigned>(date.GetMonth()));

		stream << date.GetDay() << '.' << month << '.' << date.GetYear();
	}

	return stream;
}

std::istream& operator >>(std::istream& stream, CDate& date)
{
	std::string value;
	const std::regex r(R"([0-9]{2}.[0-9]{2}.[0-9]{4})");
	std::smatch m;
	stream >> value;

	if (std::regex_match(value, m, r))
	{
		unsigned day = stoi(m[0].str().substr(0, 2));
		unsigned month = stoi(m[0].str().substr(3, 2));
		unsigned year = stoi(m[0].str().substr(6, 4));

		try
		{
			date = CDate(day, static_cast<Month>(month), year);
			return stream;
		}
		catch (std::exception &ex)
		{
		}
	}

	date.m_timestamp = INVALID_TIMESTAMP_VALUE;
	return stream;
}