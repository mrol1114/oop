#include <iostream>
#include <sstream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../StringList/CStringList.h"

SCENARIO("initializing list")
{
	CStringList baseList;
	baseList.PushBack("123");
	baseList.PushBack("456");
	baseList.PushBack("789");

	GIVEN("testing copy operator")
	{
		CStringList list = baseList;

		REQUIRE(list.GetBackElement() == "789");
		REQUIRE(list.GetSize() == 3);
	}

	GIVEN("testing move operator")
	{
		CStringList list1 = baseList;
		CStringList list2 = std::move(list1);

		REQUIRE(list2.GetBackElement() == "789");
		REQUIRE(list2.GetSize() == 3);
		REQUIRE_THROWS(list1.GetBackElement());
		REQUIRE(list1.GetSize() == 0);
	}
}

SCENARIO("testing iterators")
{
	CStringList baseList;
	baseList.PushBack("123");
	baseList.PushBack("456");
	baseList.PushBack("789");

	WHEN("testing begin")
	{
		auto it = baseList.begin();

		REQUIRE(*it == "123");
	}

	WHEN("testing ++")
	{
		auto it = baseList.begin();
		std::ostringstream expected("123456789");
		std::ostringstream get;

		for (; it != baseList.end(); it++)
		{
			get << *it;
		}

		REQUIRE(get.str() == expected.str());
	}

	WHEN("testing --")
	{
		auto it = baseList.begin();

		it++;
		REQUIRE(*it == "456");

		it--;
		REQUIRE(*it == "123");
	}

	WHEN("testing range-based for")
	{
		auto it = baseList.begin();
		std::ostringstream expected("123456789");
		std::ostringstream get;

		for (std::string& value: baseList)
		{
			get << value;
		}

		REQUIRE(get.str() == expected.str());
	}

	WHEN("testing Erase")
	{
		CStringList list = baseList;

		auto it = list.begin();

		it++;
		it = list.Erase(it);
		REQUIRE(*it == "789");
		REQUIRE(list.GetSize() == 2);
		REQUIRE(list.GetBackElement() == "789");

		it = list.Erase(it);
		REQUIRE(list.GetSize() == 1);
		REQUIRE(list.GetBackElement() == "123");

		REQUIRE_THROWS(list.Erase(it));
	}

	WHEN("testing Insert")
	{
		CStringList list = baseList;
		std::ostringstream expected("abc123qwerty456789dc");
		std::ostringstream get;

		auto it = list.begin();
		list.Insert(it, "abc");

		it++;
		list.Insert(it, "qwerty");

		auto end = list.end();
		list.Insert(end, "dc");

		for (const std::string& value : list)
		{
			get << value;
		}
		REQUIRE(expected.str() == get.str());
	}
}

SCENARIO("testing const iterators")
{
	CStringList base;
	base.PushBack("123");
	base.PushBack("456");
	base.PushBack("789");

	const CStringList baseList = base;

	WHEN("testing begin")
	{
		auto it = baseList.cbegin();

		REQUIRE(*it == "123");
	}

	WHEN("testing ++")
	{
		auto it = baseList.cbegin();
		std::ostringstream expected("123456789");
		std::ostringstream get;

		for (; it != baseList.cend(); it++)
		{
			get << *it;
		}

		REQUIRE(get.str() == expected.str());
	}

	WHEN("testing --")
	{
		auto it = baseList.cbegin();

		it++;
		REQUIRE(*it == "456");

		it--;
		REQUIRE(*it == "123");
	}

	WHEN("testing range-based for")
	{
		auto it = baseList.cbegin();
		std::ostringstream expected("123456789");
		std::ostringstream get;

		for (const std::string& value : baseList)
		{
			get << value;
		}

		REQUIRE(get.str() == expected.str());
	}

	WHEN("testing reverse range-based for")
	{
		std::vector<std::string> expected;
		for (auto i = baseList.rbegin(); i != baseList.rend(); i++)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected[0] == "789");
		REQUIRE(expected[1] == "456");
		REQUIRE(expected[2] == "123");
	}
}