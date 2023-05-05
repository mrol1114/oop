#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../ConsoleApplication1/Date.h"

SCENARIO("creating date")
{
	GIVEN("A Date created through day, month, year")
	{
		CDate date(5, Month::JANUARY, 2023);

		REQUIRE(date.GetDay() == 5);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 2023);
	}

	GIVEN("A Date created through timestamp")
	{
		CDate date(0);

		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 1970);
	}
}

SCENARIO("testing operators")
{

}