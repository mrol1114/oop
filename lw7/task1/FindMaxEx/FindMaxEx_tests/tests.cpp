#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../FindMaxEx/VectorUtils.h"

struct Sportsmen
{
	std::string name;
	int weight = 0;
	int height = 0;
};

SCENARIO("testing default function less")
{
	int maxElement;
	std::vector<int> arr = {1, 34 , 56, 1};
	FindMax(arr, maxElement);
	REQUIRE(FindMax(arr, maxElement));
}

SCENARIO("find sportsmen with max weight")
{
	auto findMax = [&](const Sportsmen& first, const Sportsmen& second)
	{
		return first.weight < second.weight;
	};

	GIVEN("array with 3 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {
			{"Andrey", 65, 170},
			{"Andersson", 70, 170},
			{"Smith", 70, 170}
		};

		REQUIRE(FindMax(arr, maxElement, findMax));
		REQUIRE(maxElement.weight == 70);
		REQUIRE(maxElement.name == "Andersson");
	}

	GIVEN("array with 1 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {
			{"Andersson", 70, 170}
		};

		REQUIRE(FindMax(arr, maxElement, findMax));
		REQUIRE(maxElement.weight == 70);
	}

	GIVEN("array with 0 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {};

		REQUIRE(!FindMax(arr, maxElement, findMax));
	}
}

SCENARIO("find sportsmen with max height")
{
	auto findMax = [&](const Sportsmen& first, const Sportsmen& second)
	{
		return first.height < second.height;
	};

	GIVEN("array with 3 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {
			{"Andrey", 65, 166},
			{"Andersson", 70, 160},
			{"Smith", 70, 180}
		};

		REQUIRE(FindMax(arr, maxElement, findMax));
		REQUIRE(maxElement.height == 180);
	}

	GIVEN("array with 1 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {
			{"Andersson", 70, 170}
		};

		REQUIRE(FindMax(arr, maxElement, findMax));
		REQUIRE(maxElement.height == 170);
	}

	GIVEN("array with 0 elements")
	{
		Sportsmen maxElement;
		std::vector<Sportsmen> arr = {};

		REQUIRE(!FindMax(arr, maxElement, findMax));
	}
}