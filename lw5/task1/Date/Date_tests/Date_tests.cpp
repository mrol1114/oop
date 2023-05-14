#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../ConsoleApplication1/Date.h"

SCENARIO("creating date")
{
	WHEN("A Date created through day, month, year")
	{
		GIVEN("Valid date")
		{
			CDate date(1, Month::FEBRUARY, 2023);

			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::FEBRUARY);
			REQUIRE(date.GetYear() == 2023);
			REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}

		GIVEN("Min date")
		{
			CDate date(1, Month::JANUARY, 1970);

			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == 1970);
			REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
		}

		GIVEN("Max date")
		{
			CDate date(31, Month::DECEMBER, 9999);

			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetYear() == 9999);
		}

		GIVEN("Invalid year")
		{
			REQUIRE_THROWS(new CDate(1, Month::JANUARY, 10000));
		}

		GIVEN("Invalid day")
		{
			REQUIRE_THROWS(new CDate(29, Month::FEBRUARY, 1999));
		}
	}

	WHEN("A Date created through timestamp")
	{
		GIVEN("Valid date")
		{
			CDate date(19389);

			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::FEBRUARY);
			REQUIRE(date.GetYear() == 2023);
		}

		GIVEN("Min date")
		{
			CDate date(0);

			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == 1970);
		}

		GIVEN("Max date")
		{
			CDate date(2932896);

			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetYear() == 9999);
		}

		GIVEN("Invalid year")
		{
			REQUIRE_THROWS(new CDate(2932897));
		}
	}
}

SCENARIO("testing operators")
{
	WHEN("Testing += operator")
	{
		CDate date(26, Month::FEBRUARY, 2023);

		date += 5;

		REQUIRE(date.GetDay() == 3);
		REQUIRE(date.GetMonth() == Month::MARCH);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Testing -= operator")
	{
		CDate date(3, Month::MARCH, 2023);

		date -= 5;

		REQUIRE(date.GetDay() == 26);
		REQUIRE(date.GetMonth() == Month::FEBRUARY);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Testing - operator")
	{
		CDate firstDate(31, Month::DECEMBER, 2022);
		CDate secondDate(31, Month::JANUARY, 2023);

		REQUIRE(firstDate - secondDate == -31);

		CDate result = firstDate - 5;
		REQUIRE(result.GetDay() == 26);
		REQUIRE(result.GetMonth() == Month::DECEMBER);
		REQUIRE(result.GetYear() == 2022);
	}

	WHEN("Testing -- operator")
	{
		CDate firstDate(31, Month::DECEMBER, 2022);
		CDate secondDate(31, Month::JANUARY, 2023);
		
		CDate result = firstDate--;

		REQUIRE(result.GetDay() == 31);
		REQUIRE(result.GetMonth() == Month::DECEMBER);
		REQUIRE(result.GetYear() == 2022);
		REQUIRE(firstDate.GetDay() == 30);
		REQUIRE(firstDate.GetMonth() == Month::DECEMBER);
		REQUIRE(firstDate.GetYear() == 2022);

		CDate secondResult = --secondDate;

		REQUIRE(secondResult.GetDay() == 30);
		REQUIRE(secondResult.GetMonth() == Month::JANUARY);
		REQUIRE(secondResult.GetYear() == 2023);
		REQUIRE(secondDate.GetDay() == 30);
		REQUIRE(secondDate.GetMonth() == Month::JANUARY);
		REQUIRE(secondDate.GetYear() == 2023);
	}

	WHEN("Testing ++ operator")
	{
		CDate firstDate(31, Month::DECEMBER, 2022);
		CDate secondDate(31, Month::JANUARY, 2023);

		CDate result = firstDate++;

		REQUIRE(result.GetDay() == 31);
		REQUIRE(result.GetMonth() == Month::DECEMBER);
		REQUIRE(result.GetYear() == 2022);
		REQUIRE(firstDate.GetDay() == 1);
		REQUIRE(firstDate.GetMonth() == Month::JANUARY);
		REQUIRE(firstDate.GetYear() == 2023);

		CDate secondResult = ++secondDate;

		REQUIRE(secondResult.GetDay() == 1);
		REQUIRE(secondResult.GetMonth() == Month::FEBRUARY);
		REQUIRE(secondResult.GetYear() == 2023);
		REQUIRE(secondDate.GetDay() == 1);
		REQUIRE(secondDate.GetMonth() == Month::FEBRUARY);
		REQUIRE(secondDate.GetYear() == 2023);
	}

	WHEN("Testing < operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(firstDate < secondDate);
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(!(firstDate < secondDate));
		}
	}

	WHEN("Testing <= operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(firstDate <= secondDate);
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(firstDate <= secondDate);
		}
	}

	WHEN("Testing > operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(secondDate > firstDate);
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(!(secondDate > firstDate));
		}
	}

	WHEN("Testing >= operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(secondDate >= firstDate);
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(secondDate >= firstDate);
		}
	}

	WHEN("Testing == operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(!(secondDate == firstDate));
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(secondDate == firstDate);
		}
	}

	WHEN("Testing != operator")
	{
		GIVEN("Not equal dates")
		{
			CDate firstDate(31, Month::DECEMBER, 2022);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(secondDate != firstDate);
		}

		GIVEN("Equal dates")
		{
			CDate firstDate(31, Month::JANUARY, 2023);
			CDate secondDate(31, Month::JANUARY, 2023);

			REQUIRE(!(secondDate != firstDate));
		}
	}

	WHEN("Testing >> operator")
	{
		GIVEN("valid date")
		{
			std::istringstream input("31.01.2023");
			CDate date(0);
			input >> date;

			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == 2023);
		}

		GIVEN("invalid date")
		{
			std::istringstream input("31.01.10000");
			CDate date(0);
			input >> date;

			REQUIRE(!date.IsValid());
		}
	}

	WHEN("Testing << operator")
	{
		GIVEN("valid date")
		{
			std::ostringstream output;
			CDate date(31, Month::JANUARY, 2023);
			output << date;

			REQUIRE(output.str() == "31.01.2023");
		}

		GIVEN("invalid date")
		{
			std::ostringstream output;
			CDate date(31, Month::DECEMBER, 9999);
			date++;
			output << date;

			REQUIRE(output.str() == "INVALID");
		}
	}
}

SCENARIO("Operations with invalid date")
{
	WHEN("overflow")
	{
		CDate date(31, Month::DECEMBER, 9999);
		date++;
		REQUIRE(!date.IsValid());

		unsigned day = date.GetDay();
		
		date++;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		++date;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date--;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		--date;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date += 4;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date -= 4;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);
	}

	WHEN("underflow")
	{
		CDate date(0);
		date--;
		REQUIRE(!date.IsValid());

		unsigned day = date.GetDay();

		date++;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		++date;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date--;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		--date;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date += 4;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);

		date -= 4;
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == day);
	}
}