#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using matrixOfDouble = std::vector<std::vector<double>>;
using rowOfDouble = std::vector<double>;

struct Parameters
{
    std::vector<std::vector<double>> firstMatrix;
    std::vector<std::vector<double>> secondMatrix;
};

void EnsureArgumentCountMatch(int argc);
Parameters InitParameters(char* argv[]);
std::ifstream OpenFileOnRead(std::string fileName);
void PrintMatrix(std::vector<std::vector<double>> matrix);
std::vector<std::vector<double>> ReadMatrixFromFile(const std::string& inFileName);
std::vector<double> ReadLine(const std::string& line);
std::vector<double> GetColumn(std::vector<std::vector<double>>& matrix, int indexOfColumn);
std::vector<std::vector<double>> InitializeMatrixWithZeros(const size_t numberOfRows,
    const size_t numberOfColumns);
std::vector<std::vector<double>> MultiplicateMatrix(
    std::vector<std::vector<double>>& firstMatrix,
    std::vector<std::vector<double>>& secondMatrix);
double MultiplicateVectors(
    std::vector<double>& firstVector,
    std::vector<double>& secondVector);

int main(int argc, char* argv[])
{
    try
    {
        EnsureArgumentCountMatch(argc);

        auto parameters = InitParameters(argv);
        auto result = MultiplicateMatrix(parameters.firstMatrix, 
            parameters.secondMatrix);

        PrintMatrix(result);

        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}

Parameters InitParameters(char* argv[])
{
    auto firstMatrix = ReadMatrixFromFile(argv[1]);
    auto secondMatrix = ReadMatrixFromFile(argv[2]);

    return {firstMatrix, secondMatrix};
}

void EnsureArgumentCountMatch(int argc)
{
    if (argc != 3)
        throw std::invalid_argument("Invalid argument count\n"
            "Usage: FlipBytes.exe <file-of-first-matrix> <file-of-second-matrix>");
}

std::ifstream OpenFileOnRead(std::string fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
        throw std::runtime_error("Can not open file to read");

    return file;
}

std::vector<std::vector<double>> ReadMatrixFromFile(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);
    if (!inFile.is_open())
        throw std::runtime_error("Can not open file to read");

    std::vector<std::vector<double>> matrix;
    std::string line;
    const int numberOfRows = 3;
    int curNumberOfRows = 0;

    while (std::getline(inFile, line))
    {
        matrix.push_back(ReadLine(line));
        curNumberOfRows++;
    }

    if (curNumberOfRows != numberOfRows)
        throw std::invalid_argument("Invalid number of rows in matrix");

    return matrix;
}

std::vector<double> ReadLine(const std::string& line)
{
    std::stringstream ss(line);
    std::vector<double> row;
    int curNumberOfColumns = 0;
    const int neededNumberOfColumns = 3;
    std::string value;

    while (ss >> value)
    {
        row.push_back(std::stod(value));
        curNumberOfColumns++;
    }

    if (curNumberOfColumns != neededNumberOfColumns)
        throw std::invalid_argument("Invalid number of columns in matrix");

    return row;
}

std::vector<std::vector<double>> InitializeMatrixWithZeros(const size_t numberOfRows,
    const size_t numberOfColumns)
{
    std::vector<std::vector<double>> resultMatrix = {};

    for (int i = 0; i < numberOfRows; i++)
        resultMatrix.push_back(std::vector<double>(numberOfColumns, 0));

    return resultMatrix;
}

std::vector<std::vector<double>> MultiplicateMatrix(
    std::vector<std::vector<double>>& firstMatrix,
    std::vector<std::vector<double>>& secondMatrix)
{
    if (firstMatrix[0].size() != secondMatrix.size())
        throw std::runtime_error("matrixes are inconsistent");

    const size_t resultNumberOfRows = firstMatrix.size();
    const size_t resultNumberOfColumns = secondMatrix[0].size();
    auto resultMatrix = InitializeMatrixWithZeros(resultNumberOfRows, resultNumberOfColumns);

    for (int indexOfCurrentRow = 0; indexOfCurrentRow < resultNumberOfRows;
        indexOfCurrentRow++)
        for (int indexOfCurrentColumn = 0; indexOfCurrentColumn < resultNumberOfColumns;
            indexOfCurrentColumn++)
        {
            auto column = GetColumn(secondMatrix, indexOfCurrentColumn);
            resultMatrix[indexOfCurrentRow][indexOfCurrentColumn] = MultiplicateVectors(
                firstMatrix[indexOfCurrentRow],
                column
            );
        }

    return resultMatrix;
}

std::vector<double> GetColumn(
    std::vector<std::vector<double>>& matrix,
    int indexOfColumn)
{
    std::vector<double> column;
    const size_t sizeOfRow = matrix[0].size();

    for (int indexOfCurrentRow = 0; indexOfCurrentRow < sizeOfRow; indexOfCurrentRow++)
        column.push_back(matrix[indexOfCurrentRow][indexOfColumn]);

    return column;
}

double MultiplicateVectors(
    std::vector<double>& firstVector,
    std::vector<double>& secondVector)
{
    double resultNumber = 0;

    for (int i = 0; i < firstVector.size(); i++)
    {
        double multResult = firstVector[i] * secondVector[i];
        resultNumber += multResult;
    }

    return resultNumber;
}

void PrintMatrix(std::vector<std::vector<double>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        std::for_each(matrix[i].begin(), matrix[i].end(), [&](double number) {
            std::cout << std::fixed << std::setprecision(3) << std::setw(10) << number << ' ';
            });
        std::cout << std::endl;
    }
}