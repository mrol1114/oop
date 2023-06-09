#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../CMyArray/CMyArray.h"

SCENARIO("testing array of strings")
{
	WHEN("initializing array by copying")
	{

		GIVEN("object with 1 element")
		{
			CMyArray<std::string> arr1;
			arr1.PushBack("qwerty");
			CMyArray<std::string> arr2 = arr1;

			REQUIRE(arr1.GetSize() == 1);
			REQUIRE(arr2.GetSize() == 1);
			REQUIRE(arr2[0] == "qwerty");

			arr1[0] = "123";
			REQUIRE(arr2[0] == "qwerty");
		}

		GIVEN("object with 3 element")
		{
			CMyArray<std::string> arr1;
			arr1.PushBack("1");
			arr1.PushBack("245");
			arr1.PushBack("388");

			CMyArray<std::string> arr2 = arr1;

			REQUIRE(arr1.GetSize() == 3);
			REQUIRE(arr2.GetSize() == 3);
			REQUIRE(arr2[0] == "1");
			REQUIRE(arr2[1] == "245");
			REQUIRE(arr2[2] == "388");

			arr1[0] = "123";
			REQUIRE(arr2[0] == "1");
		}
	}

	WHEN("initializing by moving")
	{

	}

	WHEN("adding elements at the end")
	{

	}

	WHEN("testing operator copy")
	{

	}

	WHEN("testing operator move")
	{

	}

	WHEN("testing operations with iterator")
	{

	}
}

SCENARIO("testing array of floats")
{

	WHEN("initializing array by copying")
	{
		GIVEN("empty object")
		{
			CMyArray<float> arr1;
			CMyArray<float> arr2 = arr1;

			REQUIRE(arr1.GetSize() == 0);
		}

		GIVEN("object with 1 element")
		{
			CMyArray<float> arr1;
			arr1.PushBack(2.3);
			CMyArray<float> arr2 = arr1;

			REQUIRE(arr1.GetSize() == 1);
			REQUIRE(arr2.GetSize() == 1);
			REQUIRE(arr2[0] == 2.3f);

			arr1[0] = 1.23f;
			REQUIRE(arr2[0] == 2.3f);
		}

		GIVEN("object with 3 element")
		{
			CMyArray<float> arr1;
			arr1.PushBack(1);
			arr1.PushBack(2);
			arr1.PushBack(3);

			CMyArray<float> arr2 = arr1;

			REQUIRE(arr1.GetSize() == 3);
			REQUIRE(arr2.GetSize() == 3);
			REQUIRE(arr2[0] == 1.0);
			REQUIRE(arr2[1] == 2.0);
			REQUIRE(arr2[2] == 3.0);

			arr1[0] = 1.23;
			REQUIRE(arr2[0] == 1);
		}
	}

	WHEN("initializing by moving")
	{
		CMyArray<float> arr1;
		arr1.PushBack(1);
		arr1.PushBack(2);
		arr1.PushBack(3);

		CMyArray<float> arr2 = std::move(arr1);

		REQUIRE(arr1.GetSize() == 0);
		REQUIRE(arr2.GetSize() == 3);
		REQUIRE(arr2[0] == 1.0);
		REQUIRE(arr2[1] == 2.0);
		REQUIRE(arr2[2] == 3.0);
		REQUIRE_THROWS(arr1[0]);
	}

	WHEN("testing resize method")
	{
		CMyArray<float> arr1;
		arr1.PushBack(1);
		arr1.PushBack(2);
		arr1.PushBack(3);

		arr1.Resize(2);
		REQUIRE(arr1.GetSize() == 2);
		REQUIRE(arr1[1] == 2.0);
		REQUIRE_THROWS(arr1[2]);

		CMyArray<float> arr2;
		arr2.PushBack(1);
		arr2.PushBack(2);
		arr2.PushBack(3);

		arr2.Resize(5);
		REQUIRE(arr2.GetSize() == 5);
		REQUIRE(arr2[2] == 3.0);
		REQUIRE(arr2[4] == 0.0);
		REQUIRE_THROWS(arr2[5]);

		CMyArray<float> arr3;
		arr3.PushBack(1);
		arr3.PushBack(2);
		arr3.PushBack(3);
		arr3.PushBack(4);

		arr3.Resize(5);
		REQUIRE(arr3.GetSize() == 5);
		REQUIRE(arr3[2] == 3.0);
		REQUIRE(arr3[4] == 0.0);
		REQUIRE_THROWS(arr3[5]);
	}

	WHEN("testing clear operator")
	{
		CMyArray<float> arr1;
		arr1.PushBack(1);
		arr1.PushBack(2);
		arr1.PushBack(3);

		arr1.Clear();
		REQUIRE(arr1.GetSize() == 0);
		REQUIRE_THROWS(arr1[0]);
	}

	WHEN("testing operations with iterator")
	{

	}
}