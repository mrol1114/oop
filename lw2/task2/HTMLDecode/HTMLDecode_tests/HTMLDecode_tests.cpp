#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "Decode.h"

SCENARIO("strings from stream is decoded")
{
	GIVEN("An empty stream")
	{
		std::istringstream iss("");
		std::ostringstream oss;

		CopyStreamWithHTMLDecode(iss, oss);
		REQUIRE(oss.str() == "");
	}

	// NOT WORKING
	GIVEN("String with amp before html entity")
	{
		std::istringstream iss("&&amp;");
		std::ostringstream oss;

		CopyStreamWithHTMLDecode(iss, oss);
		REQUIRE(oss.str() == "&&\n");
	}

	GIVEN("A stream with some html tags only")
	{
		std::istringstream iss("&lt;\n&apos;");
		std::ostringstream oss;

		CopyStreamWithHTMLDecode(iss, oss);
		REQUIRE(oss.str() == "<\n'\n");
	}

	GIVEN("A stream without html tags")
	{
		std::istringstream iss("qwerty says hello\n Hello World");
		std::ostringstream oss;

		CopyStreamWithHTMLDecode(iss, oss);
		REQUIRE(oss.str() == "qwerty says hello\n Hello World\n");
	}

	GIVEN("A stream with mixed tags and other words")
	{
		std::istringstream iss("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		std::ostringstream oss;

		CopyStreamWithHTMLDecode(iss, oss);
		REQUIRE(oss.str() == "Cat <says> \"Meow\". M&M's\n");
	}
} 