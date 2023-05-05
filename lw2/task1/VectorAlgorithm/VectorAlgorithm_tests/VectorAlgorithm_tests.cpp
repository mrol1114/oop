#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "Algorithm.h"

SCENARIO("stream can be readed in vector")
{
	GIVEN("An empty strem")
	{
		std::vector<double> vIn, vOut;
		std::istringstream iss;

		vIn = ReadVector(iss);
		REQUIRE(vIn == vOut);
	}

	GIVEN("A strem with valid elements")
	{
		std::vector<double> vIn;
		std::vector<double> vOut = {12.123, 12.56, 4.5, 123};
		std::istringstream iss("12.123 12.56 4.5 123");

		vIn = ReadVector(iss);
		REQUIRE(vIn == vOut);
	}

	GIVEN("A stream with characters")
	{
		std::vector<double> vIn, vOut;
		std::istringstream iss("12.123 adw 4.5 123");

		try
		{
			vIn = ReadVector(iss);
			REQUIRE(false);
		}
		catch (std::exception)
		{
			REQUIRE(true);
		}
	}
}

SCENARIO("each element of vector is multiplied by max element and divided by min element")
{
	GIVEN("An empty vector")
	{
		std::vector<double> vIn = {};
		std::vector<double> vOut = {};

		ProcessVector(vIn);
		REQUIRE(vIn == vOut);
	}

	GIVEN("A vector with valid elements")
	{
		std::vector<double> vIn = {12.123, 12.56, 4.5, 123};
		std::vector<double> vOut = {331.362, 343.3066666667, 123.0, 3362.0};

		ProcessVector(vIn);
		REQUIRE(vIn == vOut);
	}

	GIVEN("A vector with min equal zero")
	{
		std::vector<double> vIn = {12.123, 0, 4.5, 123};

		try
		{
			ProcessVector(vIn);
			REQUIRE(false);
		}
		catch (std::exception)
		{
			REQUIRE(true);
		}
	}
}

SCENARIO("vector can be printed")
{
	GIVEN("Empty vector")
	{
		std::vector<double> v ;
		std::ostringstream oss;

		PrintVector(oss, v);
		REQUIRE(oss.str() == "");

	}

	GIVEN("Vector with elements")
	{
		std::vector<double> v = {331.362, 343.3066666667, 123.0, 3362.0};

		std::ostringstream oss;

		PrintVector(oss, v);
		REQUIRE(oss.str() == "331.362 343.307 123.000 3362.000 ");
	}
}