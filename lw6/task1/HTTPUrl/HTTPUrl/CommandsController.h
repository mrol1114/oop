#pragma once
#include <string>
#include <map>
#include "CHttpUrl.h"

const enum class Command
{
	Start,
	Exit,
	NewUrl,
	NewUrlProperties,
	PrintUrl,
	Help,
};

const std::map<std::string, Command> STRING_TO_COMMAND =
{
	{"exit", Command::Exit},
	{"new_url", Command::NewUrl},
	{"new_url_properties", Command::NewUrlProperties},
	{"print_url", Command::PrintUrl},
	{"help", Command::Help},
};

using UrlObject = std::unique_ptr<CHttpUrl>;

class CommandsController
{
public:
	CommandsController(std::istream& input, std::ostream& output);

	void ExecuteCommand(Command command);

private:
	std::istream& m_input;
	std::ostream& m_output;
	UrlObject m_urlObject = nullptr;
};