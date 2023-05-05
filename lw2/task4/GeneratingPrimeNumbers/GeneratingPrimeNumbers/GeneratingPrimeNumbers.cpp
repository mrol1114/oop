#include <iostream>
#include <string>
#include <set>

using PrimeNumbers = std::set<int>;

int ParseArguments(int argc, char* argv[]);
PrimeNumbers GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(const PrimeNumbers& primes);

int main(int argc, char* argv[])
{
    try
    {
        int upperBound = ParseArguments(argc, argv);

        auto set = GeneratePrimeNumbersSet(upperBound);
        PrintPrimeNumbers(set);

        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;

        return 1;
    }
}

void EnsureArgumentCountMatch(int argc);
int GetUpperBound(const std::string& value);

int ParseArguments(int argc, char* argv[])
{
    EnsureArgumentCountMatch(argc);

    return GetUpperBound(argv[1]);
}

void EnsureArgumentCountMatch(int argc)
{
    if (argc != 2)
    {
        throw std::invalid_argument("");
    }
}

int GetUpperBound(const std::string& value)
{
    const int maxUpperBound = 100000000;
    const int minUpperBound = 3;
    int upperBound;

    try
    {
        upperBound =  std::stoi(value);
    }
    catch (std::exception)
    {
        throw std::invalid_argument("<upper_bound> should be int");
    }

    if (upperBound > maxUpperBound
        || upperBound < minUpperBound)
    {
        throw std::invalid_argument("<upper_bound> should be less or equal to 100_000_000 "
            "and more then 3");
    }

    return upperBound;
}

void FillValuesToUpperBound(PrimeNumbers& set, int startNumber, int step, int upperBound);
void SiftOutAllNonprimes(PrimeNumbers& set, int startNumber, int step, int upperBound);

PrimeNumbers GeneratePrimeNumbersSet(int upperBound)
{
    int firstPrimeNumber = 2;
    int secondPrimeNumber = 3;
    int step = 2;

    PrimeNumbers set;

    set.insert(firstPrimeNumber);
    FillValuesToUpperBound(set, secondPrimeNumber, step, upperBound);

    SiftOutAllNonprimes(set, secondPrimeNumber, step, upperBound);

    return set;
}

void FillValuesToUpperBound(PrimeNumbers& set, int startNumber, int step, int upperBound)
{
    for (int i = startNumber; i < upperBound; i += step)
    {
        set.insert(i);
    }
}

void EraseNonprimes(PrimeNumbers& set, int primeNumber, int upperBound);

void SiftOutAllNonprimes(PrimeNumbers& set, int startNumber, int step, int upperBound)
{
    for (int i = startNumber; i * i < upperBound; i += step)
    {
        if (set.contains(i))
        {
            EraseNonprimes(set, i, upperBound);
        }
    }
}

void EraseNonprimes(PrimeNumbers& set, int primeNumber, int upperBound)
{
    for (int j = primeNumber * primeNumber; j < upperBound; j += primeNumber)
    {
        if (set.contains(j))
        {
            set.erase(j);
        }
    }
}

void PrintPrimeNumbers(const PrimeNumbers& primes)
{
    for (const auto& value : primes)
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}