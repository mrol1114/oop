#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../CMyString/String.h"

SCENARIO("initializing string")
{
	WHEN("initializing by char*")
	{
		String string = "qwerty";

		REQUIRE(string.GetLength() == 6);
		REQUIRE(std::string(string.GetStringData()) == std::string("qwerty"));
	}

	WHEN("initializing by char* and size")
	{
		String string("qwerty", 3);

		REQUIRE(string.GetLength() == 3);
		REQUIRE(std::string(string.GetStringData()) == std::string("qwe"));
	}

	WHEN("initializing by std::string")
	{
		std::string input = "qwerty";
		String string = input;

		REQUIRE(string.GetLength() == 6);
		REQUIRE(std::string(string.GetStringData()) == std::string("qwerty"));
	}

	WHEN("initializing by copying")
	{
		std::string input = "qwerty";
		String string1 = input;
		String string2 = string1;

		REQUIRE(string2.GetLength() == 6);
		REQUIRE(std::string(string2.GetStringData()) == std::string("qwerty"));

		string1[0] = 'a';
		REQUIRE(string1[0] == 'a');
		REQUIRE(string2[0] == 'q');
	}

	WHEN("initializing by moving")
	{
		std::string input = "qwerty";
		String string1 = input;
		String string2 = std::move(string1);

		REQUIRE(string2.GetLength() == 6);
		REQUIRE(std::string(string2.GetStringData()) == std::string("qwerty"));
		REQUIRE(!string1.GetStringData());
		REQUIRE(string1.GetLength() == 0);
	}
}

SCENARIO("testing string methods")
{
	WHEN("testing SubString")
	{
		String string = "qwerty";

		String subStr = string.SubString(2, 2);
		REQUIRE(std::string(subStr.GetStringData()) == "er");

		subStr[0] = 'a';
		REQUIRE(string[2] == 'e');

		REQUIRE(std::string(string.SubString(0).GetStringData()) == "qwerty");
		REQUIRE(std::string(string.SubString(0, 8).GetStringData()) == "qwerty");
		REQUIRE_THROWS(string.SubString(8));
	}

	WHEN("testing Clear")
	{
		String string = "qwerty";

		string.Clear();
		REQUIRE(string.GetLength() == 0);
		REQUIRE(std::string(string.GetStringData()) == "");
	}
}

SCENARIO("testing string operators")
{
	WHEN("operator + char*")
	{
		REQUIRE(std::string((String("qwe") + "rty").GetStringData()) == "qwerty");
	}

	WHEN("operator + std::string")
	{
		REQUIRE(std::string((String("qwe") + std::string("rty")).GetStringData()) == "qwerty");
	}

	WHEN("operator + String")
	{
		REQUIRE(std::string((String("qwe") + String("rty")).GetStringData()) == "qwerty");
	}

	WHEN("operator +=")
	{
		String string = "qwerty";
		string += "abc";

		REQUIRE(std::string(string.GetStringData()) == "qwertyabc");
	}

	String string1 = "qwerty";
	String string2 = "qwerty";
	String string3 = "abc";
	String string4 = "qwertya";

	WHEN("operator ==")
	{
		REQUIRE(string1 == string2);
		REQUIRE(!(string2 == string3));
	}

	WHEN("operator !=")
	{
		REQUIRE(!(string1 != string2));
		REQUIRE(string2 != string3);
	}

	WHEN("operator <")
	{
		REQUIRE(!(string1 < string2));
		REQUIRE(string3 < string2);
		REQUIRE(string2 < string4);
	}

	WHEN("operator >")
	{
		REQUIRE(!(string2 > string1));
		REQUIRE(string2 > string3);
		REQUIRE(string4 > string2);
	}

	WHEN("operator <=")
	{
		REQUIRE(string2 <= string1);
		REQUIRE(string3 <= string2);
		REQUIRE(string2 <= string4);
	}

	WHEN("operator >=")
	{
		REQUIRE(string2 >= string1);
		REQUIRE(string2 >= string3);
		REQUIRE(string4 >= string2);
	}

	WHEN("operator <<")
	{
		std::ostringstream output;

		output << string1;
		REQUIRE(output.str() == std::string(string1.GetStringData()));
	}

	WHEN("operator >>")
	{
		std::istringstream input("qwerty");
		String string;

		input >> string;
		REQUIRE(std::string(string.GetStringData()) == "qwerty");
	}
}

SCENARIO("testing iterator operations")
{
	String baseString = "qwerty";

	auto it = baseString.begin();
	REQUIRE(*it == 'q');

	it = it + 2;
	REQUIRE(*it == 'e');

	it += -2;
	REQUIRE(*it == 'q');
	REQUIRE(it[4] == 't');

	auto it1 = baseString.end();
	REQUIRE(it1 - it == 6);

	it[4] = 'a';
	REQUIRE(it[4] == 'a');
	REQUIRE(*(it1 + -2) == 'a');
	REQUIRE(baseString[4] == 'a');
}

SCENARIO("testing string methods with iterator")
{
	String baseString = "qwerty";

	WHEN("testing range-based for")
	{
		String string = baseString;
		for (char& value : string)
		{
			value = 'a';
		}

		REQUIRE(std::string(string.GetStringData()) == "aaaaaa");
	}

	WHEN("reverse iterator")
	{
		auto it = baseString.rbegin();
		REQUIRE(*it == 'y');

		std::string expected;
		for (auto i = baseString.rbegin(); i != baseString.rend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected == "ytrewq");
	}

	WHEN("const iterator")
	{
		std::string expected;

		for (auto i = baseString.cbegin(); i != baseString.cend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected == "qwerty");
	}

	WHEN("const iterator reverse")
	{
		auto it = baseString.rcbegin();
		REQUIRE(*it == 'y');

		std::string expected;
		for (auto i = baseString.rcbegin(); i != baseString.rcend(); ++i)
		{
			expected.push_back(*i);
		}

		REQUIRE(expected == "ytrewq");
	}
}