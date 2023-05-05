#include "CBodyUtils.h"

int main()
{
	try
	{
		Bodies bodies;

		ReadCBodiesInVector(std::cin, bodies);
		PrintInfoAboutBodies(std::cout, bodies);

		return 0;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}
}