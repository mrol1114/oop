#include <iostream>

#include "CommandsController.h"

namespace
{
	const std::map<Protocol, std::string> PROTOCOL_NAMES = {
		{Protocol::HTTP, "http"},
		{Protocol::HTTPS, "https"},
	};

	const std::map<std::string, Protocol> STRING_TO_PROTOCOl = {
		{"http", Protocol::HTTP},
		{"https", Protocol::HTTPS},
	};

	void InitUrl(std::istream& input, std::ostream& output, UrlObject& urlObject)
	{
		std::string url;

		output << "Enter url: ";
		input >> url;
		urlObject = std::make_unique<CHttpUrl>(url);
	}

	void PrintInfoAboutUrl(std::ostream& output, const UrlObject& urlObject)
	{
		if (!urlObject)
		{
			throw std::logic_error("Uninitialized url");
		}

		output << "Protocol: " << PROTOCOL_NAMES.at(urlObject->GetProtocol()) << std::endl;
		output << "Domain: " << urlObject->GetDomain() << std::endl;
		output << "Port: " << urlObject->GetPort() << std::endl;
		output << "Document: " << urlObject->GetDocument() << std::endl;
	}

	void InitUrlFromProperties(std::istream& input, std::ostream& output, UrlObject& urlObject)
	{
		std::string inputProtocol;
		Protocol protocol;
		std::string domain;
		std::string document;
		unsigned short port;

		output << "Enter protocol: ";
		input >> inputProtocol;
		protocol = STRING_TO_PROTOCOl.at(inputProtocol);

		output << "Enter domain: ";
		input >> domain;

		output << "Enter document: ";
		input >> document;

		output << "Enter port: ";
		input >> port;

		urlObject = std::make_unique<CHttpUrl>(domain, document, port, protocol);
	}

	void PrintAvaibleCommands(std::ostream& output)
	{
		output << "Avaible commands:" << std::endl;

		for (auto [key, value] : STRING_TO_COMMAND)
		{
			output << key << std::endl;
		}
	}
}

CommandsController::CommandsController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{

}

void CommandsController::ExecuteCommand(Command command)
{
	switch (command)
	{
	case Command::PrintUrl:
		PrintInfoAboutUrl(m_output, m_urlObject);
		break;
	case Command::NewUrl:
		InitUrl(m_input, m_output, m_urlObject);
		break;
	case Command::NewUrlProperties:
		InitUrlFromProperties(m_input, m_output, m_urlObject);
		break;
	case Command::Help:
		PrintAvaibleCommands(m_output);
		break;
	}
}