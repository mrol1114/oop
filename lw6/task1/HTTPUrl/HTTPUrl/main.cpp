#include <string>
#include <iostream>

#include "CommandsController.h"

int main()
{
	std::string url;
	CommandsController controller;

	while (controller.ReadUrl(std::cin, std::cout, url))
	{
		try
		{
			CHttpUrl urlObject(url);
			controller.PrintInfoAboutUrl(std::cout, urlObject);

			std::cout << std::endl << std::endl;
		}
		catch(std::exception &ex)
		{
			std::cout << "Could not create url: " << std::endl
				<< ex.what() << std::endl;
		}
	}
}