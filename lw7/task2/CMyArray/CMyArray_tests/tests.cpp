#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../CMyArray/CMyArray.h"

SCENARIO("testing array of strings")
{
	CMyArray<std::string> baseArray;
	baseArray.PushBack("123");
	baseArray.PushBack("456");
	baseArray.PushBack("789");

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
		CMyArray<std::string> arr1 = baseArray;
		CMyArray<std::string> arr2 = std::move(arr1);

		REQUIRE(arr1.GetSize() == 0);
		REQUIRE(arr2.GetSize() == 3);
		REQUIRE(arr2[0] == "123");
		REQUIRE(arr2[1] == "456");
		REQUIRE(arr2[2] == "789");
		REQUIRE_THROWS(arr1[0]);
	}

	WHEN("testing resize method")
	{
		CMyArray<std::string> arr1 = baseArray;

		arr1.Resize(2);
		REQUIRE(arr1.GetSize() == 2);
		REQUIRE(arr1[1] == "456");
		REQUIRE_THROWS(arr1[2]);

		CMyArray<std::string> arr2 = baseArray;

		arr2.Resize(5);
		REQUIRE(arr2.GetSize() == 5);
		REQUIRE(arr2[2] == "789");
		REQUIRE(arr2[4] == "");
		REQUIRE_THROWS(arr2[5]);
	}

	WHEN("testing clear operator")
	{
		CMyArray<std::string> arr1 = baseArray;

		arr1.Clear();
		REQUIRE(arr1.GetSize() == 0);
		REQUIRE_THROWS(arr1[0]);
	}

	WHEN("testing operator copy")
	{
		CMyArray<std::string> arr1 = baseArray;
		CMyArray<std::string> arr2;

		arr2 = arr1;

		REQUIRE(arr2[0] == "123");
		REQUIRE(arr2[1] == "456");
		REQUIRE(arr2[2] == "789");
		REQUIRE(arr2.GetSize() == 3);

		arr1[0] = "qwerty";
		REQUIRE(arr2[0] == "123");
		REQUIRE(arr1[0] == "qwerty");

		arr1 = arr1;
		REQUIRE(arr1[0] == "qwerty");
		REQUIRE(arr1[1] == "456");
		REQUIRE(arr1[2] == "789");
		REQUIRE(arr2.GetSize() == 3);
	}

	WHEN("testing operator move")
	{
		CMyArray<std::string> arr1 = baseArray;
		CMyArray<std::string> arr2;

		arr2 = move(arr1);

		REQUIRE(arr1.GetSize() == 0);
		REQUIRE_THROWS(arr1[0]);
		REQUIRE(arr2[0] == "123");
		REQUIRE(arr2[1] == "456");
		REQUIRE(arr2[2] == "789");
		REQUIRE(arr2.GetSize() == 3);

		arr2 = move(arr2);

		REQUIRE(arr2[0] == "123");
		REQUIRE(arr2[1] == "456");
		REQUIRE(arr2[2] == "789");
		REQUIRE(arr2.GetSize() == 3);
	}

	WHEN("testing operations with iterator")
	{
		auto it = baseArray.begin();
		REQUIRE(*it == "123");

		it++;
		REQUIRE(*it == "456");

		it += -1;
		REQUIRE(*it == "123");

		it += 2;
		REQUIRE(*it == "789");

		auto it1 = it + -2;
		REQUIRE(*it1 == "123");
		REQUIRE(*it == "789");

		*it = "qwerty";
		REQUIRE(*it == "qwerty");
	}

	WHEN("testing range-based for")
	{
		auto it = baseArray.rbegin();
		REQUIRE(*it == "789");

		CMyArray<std::string> array = baseArray;
		for (std::string& value : array)
		{
			value = "qwerty";
		}

		REQUIRE(array[0] == "qwerty");
		REQUIRE(array[1] == "qwerty");
		REQUIRE(array[2] == "qwerty");
	}

	WHEN("reverse iterator")
	{
		auto it = baseArray.rbegin();
		REQUIRE(*it == "789");
		std::vector<std::string> expected;

		for (auto i = baseArray.rbegin(); i != baseArray.rend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected[0] == "789");
		REQUIRE(expected[1] == "456");
		REQUIRE(expected[2] == "123");
	}

	WHEN("const iterators")
	{
		std::vector<std::string> expected;

		for (auto i = baseArray.cbegin(); i != baseArray.cend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected[0] == "123");
		REQUIRE(expected[1] == "456");
		REQUIRE(expected[2] == "789");
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

	CMyArray<float> baseArray;
	baseArray.PushBack(1);
	baseArray.PushBack(2);
	baseArray.PushBack(3);

	WHEN("testing operations with iterator")
	{
		auto it = baseArray.begin();
		REQUIRE(*it == 1.0);

		it++;
		REQUIRE(*it == 2.0);

		it += -1;
		REQUIRE(*it == 1.0);

		it += 2;
		REQUIRE(*it == 3.0);

		auto it1 = it + -2;
		REQUIRE(*it1 == 1.0);
		REQUIRE(*it == 3.0);

		*it = 2.0;
		REQUIRE(*it == 2.0);
	}

	WHEN("testing range-based for")
	{
		auto it = baseArray.rbegin();
		REQUIRE(*it == 3.0);

		CMyArray<float> array = baseArray;
		for (float& value: array)
		{
			value = 1.0;
		}

		REQUIRE(array[0] == 1.0);
		REQUIRE(array[1] == 1.0);
		REQUIRE(array[2] == 1.0);
	}

	WHEN("reverse iterator")
	{
		auto it = baseArray.rbegin();
		REQUIRE(*it == 3.0);
		std::vector<float> expected;

		for (auto i = baseArray.rbegin(); i != baseArray.rend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected[0] == 3.0);
		REQUIRE(expected[1] == 2.0);
		REQUIRE(expected[2] == 1.0);
	}

	WHEN("const iterators")
	{
		std::vector<float> expected;

		for (auto i = baseArray.cbegin(); i != baseArray.cend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected[0] == 1.0);
		REQUIRE(expected[1] == 2.0);
		REQUIRE(expected[2] == 3.0);
	}
}