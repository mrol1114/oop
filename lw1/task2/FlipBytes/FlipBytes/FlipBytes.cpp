#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

void EnsureArgumentCountMatch(const int argc);
void EnsureNumberIs8bitNumber(const std::string number);
uint8_t ParseArgument(int argc, char* argv[]);
uint8_t FlipBitsIn8BitNumber(const uint8_t number);
uint8_t ChangeBytes(uint8_t number, int numberOfBytesToChange);
uint8_t GetMask(int numberOfBytesToChange, bool isFirstHalf);

int main(int argc, char* argv[])
{
    try
    {
        uint8_t number = ParseArgument(argc, argv);
        uint8_t flipedNumber = FlipBitsIn8BitNumber(number);

        std::cout << static_cast<int>(flipedNumber) << std::endl;

        return 0;
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}

uint8_t ParseArgument(int argc, char* argv[])
{
    EnsureArgumentCountMatch(argc);
    EnsureNumberIs8bitNumber(argv[1]);

    return std::stoi(argv[1]);
}

void EnsureArgumentCountMatch(const int argc)
{
    if (argc != 2)
        throw std::invalid_argument("Invalid argument count\n"
            "Usage: FlipBytes.exe <number>");
}

void EnsureNumberIs8bitNumber(const std::string number)
{
    const std::string maxValue = "255";
    const std::regex regexForDecimalNumber(R"(^[0-9]\d*$)");

    if (!std::regex_match(number.data(), regexForDecimalNumber))
        throw std::invalid_argument("<number> must not include characters");

    if (number.size() >= 3 && number > maxValue)
        throw std::invalid_argument("<number> must be in range 0 < number < 255");
}

uint8_t FlipBitsIn8BitNumber(const uint8_t number)
{
    const int countOfBitsInHalfNumber = 4;

    return ChangeBytes(number, countOfBitsInHalfNumber);
}

uint8_t ChangeBytes(uint8_t number, int numberOfBitsToChange)
{
    if (numberOfBitsToChange <= 0) return number;

    uint8_t firstHalfNumber = (number & GetMask(numberOfBitsToChange, true))
        << numberOfBitsToChange;
    uint8_t secondHalfNumber = (number & GetMask(numberOfBitsToChange, false))
        >> numberOfBitsToChange;

    return ChangeBytes(firstHalfNumber + secondHalfNumber, numberOfBitsToChange / 2);
}

uint8_t GetMask(int numberOfBitsToChange, bool isFirstHalf)
{
    uint8_t mask = 0;
    const int sizeOfNumberInBytes = 8;
    const int base = 2;

    for (int indexOfCurBit = 0; indexOfCurBit < sizeOfNumberInBytes; indexOfCurBit++)
    {
        int numberOfWholeParts = indexOfCurBit / numberOfBitsToChange;

        if ((numberOfWholeParts % 2 == 0 && isFirstHalf)
            || (numberOfWholeParts % 2 != 0 && !isFirstHalf))
            mask += static_cast<uint8_t>(pow(base, indexOfCurBit));
    }

    return mask;
}