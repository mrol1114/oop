#include "Decode.h"

int main()
{
	try
	{
		CopyStreamWithHTMLDecode(std::cin, std::cout);

		return 0;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;

		return 1;
	}
}