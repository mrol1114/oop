#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cfenv>
#include "Algorithm.h"

namespace
{
    void EnsureOperationProcceedCorrect()
    {
        if (static_cast<bool>(std::fetestexcept(FE_DIVBYZERO)))
        {
            throw std::range_error("Division by zero happened, minimum value can't be zero");
        }
    }
}

std::vector<double> ReadVector(std::istream& input)
{
    std::vector<double> vector;
    std::string value;

    while (input >> value)
    {
        vector.push_back(std::stod(value));
    }

    return vector;
}

void ProcessVector(std::vector<double>& vector)
{
    std::feclearexcept(FE_DIVBYZERO);
    double maxElement;
    double minElement;

    if (vector.size() > 0)
    {
        maxElement = *std::max_element(vector.begin(), vector.end());
        minElement = *std::min_element(vector.begin(), vector.end());
    }

    for (double& element : vector)
    {
        element *= maxElement;
        element /= minElement;
        EnsureOperationProcceedCorrect();
    }
}

void PrintVector(std::ostream& output, std::vector<double>& vector)
{
    for (double element : vector)
    {
        output << std::fixed << std::setprecision(3) << element << ' ';
    }

    std::cout << std::endl;
}