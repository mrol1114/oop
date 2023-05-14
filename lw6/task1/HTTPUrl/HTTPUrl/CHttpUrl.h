#pragma once

#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

private:
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
	Protocol m_protocol;
};