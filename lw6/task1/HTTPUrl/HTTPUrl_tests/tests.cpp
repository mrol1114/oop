#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../HTTPUrl/CHttpUrl.h"

SCENARIO("creating url throught string")
{
	GIVEN("Url without authethication, query parameters, port")
	{
		auto url = CHttpUrl("htTp://youtube/page/1");

		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "youtube");
		REQUIRE(url.GetDocument() == "page/1");
	}

	GIVEN("Url without authethication, query parameters")
	{
		auto url = CHttpUrl("http://youtube:8800");

		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "youtube");
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetPort() == 8800);
	}

	GIVEN("Url without authethication, query parameters")
	{
		auto url = CHttpUrl("HTTP://www.youtube.com/page/1");

		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "page/1");
	}

	GIVEN("Url without authethication")
	{
		auto url = CHttpUrl("https://www.youtube.com/page/1?verified=true&download=true");

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "page/1?verified=true&download=true");
	}

	GIVEN("Url")
	{
		auto url = CHttpUrl("https://login:password@www.youtube.com:65535/page/1?verified=true&download=");

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "login:password@www.youtube.com");
		REQUIRE(url.GetDocument() == "page/1?verified=true&download=");
		REQUIRE(url.GetPort() == 65535);
	}

	GIVEN("Url with api")
	{
		auto url = CHttpUrl("https://127.0.0.1");

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "127.0.0.1");

		auto url1 = CHttpUrl("https://255.255.255.255");

		REQUIRE(url1.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url1.GetDomain() == "255.255.255.255");

		auto url2 = CHttpUrl("https://0.0.0.0");

		REQUIRE(url2.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url2.GetDomain() == "0.0.0.0");

		REQUIRE_THROWS(CHttpUrl("https://255.255.255"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255.256"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255.asw"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255."));
		REQUIRE_THROWS(CHttpUrl("https://-255.255.255.255"));
	}

	GIVEN("Url with invalid protocol")
	{
		REQUIRE_THROWS(CHttpUrl("hps://www.youtube.com"));
	}

	GIVEN("Url with invalid port")
	{
		REQUIRE_THROWS(CHttpUrl("https://www.youtube.com:abcd"));
		REQUIRE_THROWS(CHttpUrl("https://www.youtube.com:-8000"));
		REQUIRE_THROWS(CHttpUrl("https://www.youtube.com:0"));
		REQUIRE_THROWS(CHttpUrl("https://www.youtube.com:65536"));
	}

	GIVEN("Url with invalid query parameters")
	{
		REQUIRE_THROWS(CHttpUrl("https://www.youtube.com?page=="));
	}
}

SCENARIO("creating url throught parameters")
{
	GIVEN("Url with port")
	{
		auto url = CHttpUrl("youtube", "page", 8800, Protocol::HTTPS);

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "youtube");
		REQUIRE(url.GetDocument() == "page");
		REQUIRE(url.GetPort() == 8800);
	}

	GIVEN("Url")
	{
		auto url = CHttpUrl("login:password@www.youtube.com", "page/1?verified=true&download=true", Protocol::HTTPS);

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "login:password@www.youtube.com");
		REQUIRE(url.GetDocument() == "page/1?verified=true&download=true");
	}

	GIVEN("Url with api")
	{
		auto url = CHttpUrl("https://127.0.0.1");

		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "127.0.0.1");

		auto url1 = CHttpUrl("https://255.255.255.255");

		REQUIRE(url1.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url1.GetDomain() == "255.255.255.255");

		auto url2 = CHttpUrl("https://0.0.0.0");

		REQUIRE(url2.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url2.GetDomain() == "0.0.0.0");

		REQUIRE_THROWS(CHttpUrl("https://255.255.255"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255.256"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255.asw"));
		REQUIRE_THROWS(CHttpUrl("https://255.255.255."));
		REQUIRE_THROWS(CHttpUrl("https://-255.255.255.255"));
	}
}