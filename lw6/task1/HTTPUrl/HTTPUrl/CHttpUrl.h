#pragma once

#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
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

	// возвращает доменное имя
	std::string GetDomain()const;

	/*
		Возвращает имя документа. Примеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument()const;

	// возвращает тип протокола
	Protocol GetProtocol()const;

	// возвращает номер порта
	unsigned short GetPort()const;

private:
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
	Protocol m_protocol;
};