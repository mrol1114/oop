#include "Algorithm.h"

int main()
{
    try
    {
        std::vector<double> vector = ReadVector(std::cin);
        ProcessVector(vector);

        PrintVector(std::cout, vector);

        return  0;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;

        return 1;
    }
}