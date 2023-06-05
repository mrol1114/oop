#include <map>
#include <regex>

#include "CHttpUrl.h"
#include "CUrlParsingError.h"

namespace
{
	const std::regex REGEX_FOR_URL(R"(https?:\/\/)"
		R"((([^\/:.]+)?:([^\/:.]+)?@)?([a-zA-Z]+\.)?([a-zA-Z0-9]+)(\.[\w]{2,})?(:[\d]*)?)"
		R"((\/([a-zA-Z0-9]+\/)*([a-zA-Z0-9]+)?)?(\?(([a-zA-Z0-9]+=[a-zA-Z0-9]*)+&?)*)?$)");
	const std::regex REGEX_FOR_DOMAIN(R"(((([^\/:.]+)?:([^\/:.]+)?@)?([a-zA-Z]+\.))"
		R"(?([a-zA-Z0-9]+)(\.[\w]{2,})?)|(([\d]{1,3}.){3}[\d]{1,3})$)");
	const std::regex REGEX_FOR_DOCUMENT(R"((\/?([a-zA-Z0-9]+\/)*([a-zA-Z0-9]+)?)?)"
		R"((\?(([a-zA-Z0-9]+=[a-zA-Z0-9]*)+&?)*)?$)");

	const char PATH_SEPARATOR = '/';
	const char PROTOCOL_SEPARATOR = ':';
	const char AUTHORIZATION_SEPARATOR = '@';
	const char LENGTH_OF_PROTOCOL_SEPARATOR_SUBSTRING = 3;

	const int MAX_PORT = 65535;
	const int MIN_PORT = 1;

	const std::map<Protocol, unsigned short> PROTOCOL_STANDART_PORTS = {
		{Protocol::HTTP, 80},
		{Protocol::HTTPS, 443},
	};

	const std::map<std::string, Protocol> PROTOCOL_TYPES = {
		{"http", Protocol::HTTP},
		{"https", Protocol::HTTPS},
	}; // подходящее сообщение

	void ValidatePort(int port)
	{
		if (port > MAX_PORT || port < MIN_PORT) // добавить тест
		{
			throw CUrlParsingError("invalid port");
		}
	}

	void ValidateDomain(const std::string& domain)
	{
		if (!std::regex_match(domain, REGEX_FOR_DOMAIN))
		{
			throw CUrlParsingError("invalid domain");
		}
	}

	void ValidateDocument(const std::string& document)
	{
		if (!std::regex_match(document, REGEX_FOR_DOCUMENT))
		{
			throw CUrlParsingError("invalid document");
		}
	}

	Protocol ParseProtocol(const std::string& url, size_t& pos)
	{
		size_t endOfProtocolPos = url.find(PROTOCOL_SEPARATOR);
		pos = endOfProtocolPos + LENGTH_OF_PROTOCOL_SEPARATOR_SUBSTRING;

		return PROTOCOL_TYPES.at(url.substr(0, endOfProtocolPos));
	}

	std::string ParseDomain(const std::string& url, size_t& pos)
	{
		size_t prevPos = pos;

		size_t endOfAuthorizationPos = url.find(AUTHORIZATION_SEPARATOR, prevPos);
		size_t startOfPortPos = url.find(PROTOCOL_SEPARATOR,
			endOfAuthorizationPos != std::string::npos ? endOfAuthorizationPos + 1 : pos);
		
		if (startOfPortPos != std::string::npos)
		{
			pos = startOfPortPos;
			return url.substr(prevPos, startOfPortPos - prevPos);
		}
		
		pos = url.find(PATH_SEPARATOR, prevPos);
		if (pos == std::string::npos)
		{
			return url.substr(prevPos);
		}

		return url.substr(prevPos, pos - prevPos);
	}

	unsigned short ParsePort(const std::string& url, size_t& pos, Protocol protocol)
	{
		size_t startOfPortPos = url.find(PROTOCOL_SEPARATOR, pos);
		pos = url.find(PATH_SEPARATOR, pos);

		if (startOfPortPos != std::string::npos)
		{
			int port = stoi(url.substr(startOfPortPos + 1, pos - startOfPortPos));
			ValidatePort(port);

			return static_cast<unsigned short>(port);
		}
		else
		{
			return PROTOCOL_STANDART_PORTS.at(protocol);
		}
	}
	
	std::string ParseDocument(const std::string& url, size_t& pos)
	{
		return pos != std::string::npos ? url.substr(pos + 1) : "";
	}
}

CHttpUrl::CHttpUrl(const std::string &url)
{
	if (!std::regex_match(url, REGEX_FOR_URL))
	{
		throw CUrlParsingError("invalid url");
	}

	size_t pos = 0;
	Protocol protocol = ParseProtocol(url, pos);
	std::string domain = ParseDomain(url, pos);
	unsigned int port = ParsePort(url, pos, protocol);
	std::string document = ParseDocument(url, pos);

	swap(m_domain, domain);
	swap(m_document, document);
	m_protocol = protocol;
	m_port = port;
}

CHttpUrl::CHttpUrl(
	const std::string &domain,
	const std::string &document,
	Protocol protocol)
{
	ValidateDomain(domain);
	ValidateDocument(document);

	std::string domainCopy = domain;
	std::string documentCopy = document;

	swap(m_domain, domainCopy);
	swap(m_document, documentCopy);
	m_protocol = protocol;
	m_port = PROTOCOL_STANDART_PORTS.at(protocol);
}

CHttpUrl::CHttpUrl(
	const std::string &domain,
	const std::string &document,
	unsigned short port,
	Protocol protocol)
{
	ValidateDomain(domain);
	ValidateDocument(document);

	std::string domainCopy = domain;
	std::string documentCopy = document;

	swap(m_domain, domainCopy);
	swap(m_document, documentCopy);

	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetURL()const
{
	std::string port = PROTOCOL_STANDART_PORTS.at(m_protocol) == m_port
		? ""
		: PROTOCOL_SEPARATOR + std::to_string(m_port);

	std::string protocolName;
	for (auto const& [key, val] : PROTOCOL_TYPES)
	{
		if (m_protocol == val)
		{
			protocolName = key;
		}
	}

	return protocolName + PROTOCOL_SEPARATOR + PATH_SEPARATOR + PATH_SEPARATOR
		+ m_domain + port + m_document;
}

std::string CHttpUrl::GetDomain()const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument()const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol()const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort()const
{
	return m_port;
}