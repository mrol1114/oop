#include <iostream>

#include "CommandsController.h"

int main()
{
	std::string inputString;
	CommandsController controller(std::cin, std::cout);
	Command command = Command::Start;

	while (command != Command::Exit)
	{
		std::cout << "Enter command: ";
		std::cin >> inputString;

		try
		{
			command = STRING_TO_COMMAND.at(inputString);
		}
		catch (const std::exception &ex)
		{
			std::cout << "Unexisting command" << std::endl << std::endl;
			continue;
		}

		try
		{
			controller.ExecuteCommand(command);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl << std::endl;
		}

		std::cout << std::endl << std::endl;
	}
}