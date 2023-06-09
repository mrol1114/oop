#include <map>
#include <regex>

#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "StringUtils.h"

namespace
{
	const std::regex REGEX_FOR_URL(R"((https?):\/\/)"
		R"(((([^\/:.]+)?:([^\/:.]+)?@)?([a-zA-Z]+\.)?([a-zA-Z0-9]+)(\.[\w]{2,})?|(([\d]{1,3}\.){3}[\d]{1,3}))(:([\d]*))?)"
		R"((\/((([a-zA-Z0-9:]+\/)*([a-zA-Z0-9:]+)?)?(\?(([a-zA-Z0-9:]+=[a-zA-Z0-9:]*)+&?)*)?))?$)", std::regex_constants::icase);
	const std::regex REGEX_FOR_DOMAIN(R"(((([^\/:.]+)?:([^\/:.]+)?@)?([a-zA-Z]+\.))"
		R"(?([a-zA-Z0-9]+)(\.[\w]{2,})?)|(([\d]{1,3}\.){3}[\d]{1,3})$)");
	const std::regex REGEX_FOR_DOMAIN_API(R"(([\d]{1,3})\.([\d]{1,3})\.([\d]{1,3})\.([\d]{1,3})$)");
	const std::regex REGEX_FOR_DOCUMENT(R"((\/?([a-zA-Z0-9:]+\/)*([a-zA-Z0-9:]+)?)?)"
		R"((\?(([a-zA-Z0-9:]+=[a-zA-Z0-9:]*)+&?)*)?$)");

	const char PATH_SEPARATOR = '/';
	const char PROTOCOL_SEPARATOR = ':';
	const char AUTHORIZATION_SEPARATOR = '@';

	const int LENGTH_OF_PROTOCOL_SEPARATOR_SUBSTRING = 3;
	const int NUMBER_OF_PARTS_IN_API_DOMAIN = 4;
	const int MAX_API_DOMAIN_PART_VALUE = 255;
	const int MAX_PORT = 65535;
	const int MIN_PORT = 1;

	const short int INDEX_OF_PROTOCOL_GROUP = 1;
	const short int INDEX_OF_DOMAIN_GROUP = 2;
	const short int INDEX_OF_PORT_GROUP = 12;
	const short int INDEX_OF_DOCUMENT_GROUP = 14;

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
			throw CUrlParsingError("wrong port");
		}
	}

	void ValidateDomain(const std::string& domain)
	{
		std::smatch match;

		if (!std::regex_match(domain, REGEX_FOR_DOMAIN))
		{
			throw CUrlParsingError("invalid domain");
		}
		else if (std::regex_search(domain, match, REGEX_FOR_DOMAIN_API))
		{
			for (int i = 1; i <= NUMBER_OF_PARTS_IN_API_DOMAIN; i++)
			{
				int partOfDomainApi = std::stoi(match[i].str());

				if (partOfDomainApi > MAX_API_DOMAIN_PART_VALUE)
				{
					throw CUrlParsingError("value in domain exceed maximum(255)");
				}
			}
		}
	}

	void ValidateDocument(const std::string& document)
	{
		if (!std::regex_match(document, REGEX_FOR_DOCUMENT))
		{
			throw CUrlParsingError("invalid document");
		}
	}

	unsigned short ParsePort(const std::string &portStr, Protocol protocol)
	{
		if (portStr == "")
		{
			return PROTOCOL_STANDART_PORTS.at(protocol);
		}

		unsigned short port;
		try
		{
			port = static_cast<unsigned short>(stoi(portStr));
		}
		catch (const std::exception &ex)
		{
			throw CUrlParsingError("invalid port");
		}

		ValidatePort(port);

		return port;
	}
}

CHttpUrl::CHttpUrl(const std::string &url)
{
	std::smatch match;
	if (!std::regex_search(url, match, REGEX_FOR_URL))
	{
		throw CUrlParsingError("invalid url");
	}
	ValidateDomain(match[INDEX_OF_DOMAIN_GROUP].str());
	
	Protocol protocol = PROTOCOL_TYPES.at(StringToLowerCaseCopy(match[INDEX_OF_PROTOCOL_GROUP].str()));
	std::string domain = match[INDEX_OF_DOMAIN_GROUP].str();
	unsigned short port = ParsePort(match[INDEX_OF_PORT_GROUP].str(), protocol);
	std::string document = match[INDEX_OF_DOCUMENT_GROUP].str();

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