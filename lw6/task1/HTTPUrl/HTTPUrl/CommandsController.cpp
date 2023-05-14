#include <iostream>
#include <map>

#include "CommandsController.h"

namespace
{
	std::map<Protocol, std::string> PROTOCOL_NAMES = {
		{Protocol::HTTP, "http"},
		{Protocol::HTTPS, "https"},
	};
}

bool CommandsController::ReadUrl(std::istream& input, std::ostream& output, std::string& url)
{
	output << "Enter url: ";

	if (input >> url)
	{
		return true;
	}
	
	return false;
}

void CommandsController::PrintInfoAboutUrl(std::ostream& output, const CHttpUrl& url)
{
	output << "Protocol: " << PROTOCOL_NAMES.at(url.GetProtocol()) << std::endl;
	output << "Domain: " << url.GetDomain() << std::endl;
	output << "Port: " << url.GetPort() << std::endl;
	output << "Document: " << url.GetDocument() << std::endl;
}