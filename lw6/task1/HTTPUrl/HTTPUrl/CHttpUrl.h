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
	explicit CHttpUrl(const std::string &url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		unsigned short port,
		Protocol protocol = Protocol::HTTP);

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