#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Point
{
	int x, y;
};

void EnsureArgumentCountMatch(int argc);
void EnsureFilesNotTheSame(const std::string infileName, const std::string outfileName);
std::vector<std::string> ReadFieldFromFile(const std::string& inFileName);
void AddValuesIfNedded(std::vector<std::string>& field);
void Fill(std::vector<std::string>& field);
void ReplaceSymbols(std::vector<std::string>& field, int x, int y);
std::vector<std::vector<bool>> getVisitedMask(size_t neededNumberOfRows,
	size_t neededNumberOfColumns);
bool IsPointInArray(std::vector<std::string>& field, Point point);
void PrintField(const std::string& inFileName, std::vector<std::string>& field);

int main(int argc, char* argv[])
{
	try
	{
		EnsureArgumentCountMatch(argc);
		EnsureFilesNotTheSame(argv[1], argv[2]);

		auto field = ReadFieldFromFile(argv[1]);
		AddValuesIfNedded(field);

		Fill(field);
		PrintField(argv[2], field);

		return 0;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;

		return 1;
	}
}

void EnsureArgumentCountMatch(int argc)
{
	if (argc != 2)
		throw std::runtime_error("Invalid argument count\n"
			"Usage: Flip.exe <inputFile> <outputFile>");
}

void EnsureFilesNotTheSame(const std::string infileName, const std::string outfileName)
{
	if (infileName == outfileName)
		throw std::runtime_error("Error! Files are the same\n");
}

std::vector<std::string> ReadFieldFromFile(const std::string& inFileName)
{
	std::ifstream inFile(inFileName);
	if (!inFile.is_open())
		throw std::runtime_error("Can not open file to read");

	size_t neededNumberOfRows = 100;
	size_t neededNumberOfColumns = 100;
	size_t curNumberOfRows = 0;

	std::vector<std::string> field;
	std::string line;

	while (std::getline(inFile, line) && curNumberOfRows < neededNumberOfRows)
	{
		field.push_back(line.substr(0, neededNumberOfColumns));
		curNumberOfRows++;
	}

	return field;
}

void AddValuesIfNedded(std::vector<std::string>& field)
{
	size_t neededNumberOfRows = 100;
	size_t neededNumberOfColumns = 100;

	for (std::string& row : field)
		row += std::string(neededNumberOfColumns - row.length(), ' ');

	for (size_t curSize = field.size(); curSize < neededNumberOfRows; curSize++)
		field.push_back(std::string(neededNumberOfColumns, ' '));
};

void Fill(std::vector<std::string>& field)
{
	const char startSymbol = 'O';

	for (int x = 0; x < field.size(); x++)
		for (int y = 0; y < field[0].size(); y++)
			if (field[x][y] == startSymbol)
				ReplaceSymbols(field, x , y);
}

void ReplaceSymbols(std::vector<std::string>& field, int x, int y)
{
	const char fillSymbol = '.';
	const char borderSymbol = '#';
	const char blankSymbol = ' ';
	std::vector<Point> stack;
	std::vector<std::vector<bool>> visitedMask = getVisitedMask(field.size(), field[0].size());

	stack.push_back({x, y});
	while (!stack.empty())
	{
		Point curPoint = stack.back();
		stack.pop_back();

		if (!(IsPointInArray(field, curPoint) && field[curPoint.x][curPoint.y] != borderSymbol
			&& !visitedMask[curPoint.x][curPoint.y]))
			continue;

		if (field[curPoint.x][curPoint.y] == blankSymbol)
			field[curPoint.x][curPoint.y] = fillSymbol;
		visitedMask[curPoint.x][curPoint.y] = true;

		stack.push_back({curPoint.x + 1, curPoint.y});
		stack.push_back({curPoint.x - 1, curPoint.y});
		stack.push_back({curPoint.x, curPoint.y + 1});
		stack.push_back({curPoint.x, curPoint.y - 1});
	}
}

std::vector<std::vector<bool>> getVisitedMask(size_t neededNumberOfRows,
	size_t neededNumberOfColumns)
{
	std::vector<std::vector<bool>> visitedMask;

	for (int i = 0; i < neededNumberOfRows; i++)
		visitedMask.push_back(std::vector<bool>(neededNumberOfColumns, false));

	return visitedMask;
}

bool IsPointInArray(std::vector<std::string>& field, Point point)
{
	return  point.x < field.size() && point.x >= 0
		&& point.y < field[0].size() && point.y >= 0;
}

void PrintField(const std::string& inFileName, std::vector<std::string>& field)
{
	const char blankSymbol = ' ';

	std::ofstream outFile(inFileName);
	if (!outFile.is_open())
		throw std::runtime_error("Can not open file to write");

	auto is_blank = [&](char elem) {return elem == blankSymbol;};

	for (const std::string& line : field)
	{
		if (!std::all_of(line.begin(), line.end(), is_blank))
			outFile << line;

		outFile << std::endl;
	}
};