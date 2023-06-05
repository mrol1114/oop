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
	CHttpUrl(const std::string &url); // добавить обработку ip, добавить возможность ввода : в документе

	CHttpUrl(
		const std::string &domain,
		const std::string &document,
		Protocol protocol = Protocol::HTTP); // нечуствителен к регистру

	CHttpUrl(
		const std::string &domain,
		const std::string &document,
		unsigned short port, // 1 - 65535
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