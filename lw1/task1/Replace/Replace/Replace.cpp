#include <iostream>
#include <fstream>
#include <string>

struct arguments
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::string searchString;
	std::string replacementString;
};

void EnsureArgumentCountMatch(int argc);
void EnsureFilesNotTheSame(const std::string infileName, const std::string outfileName);
arguments InitArguments(char* argv[]);
std::ifstream OpenFileOnRead(const std::string fileName);
std::ofstream OpenFileOnWrite(const std::string fileName);
void CopyStreamWithReplacement(arguments& args);
std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString);

int main(int argc, char* argv[])
{		
	try
	{
		EnsureArgumentCountMatch(argc);
		EnsureFilesNotTheSame(argv[1], argv[2]);

		arguments args = InitArguments(argv);
		CopyStreamWithReplacement(args);

		return 0;
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << ex.what();
		return 1;
	}
}

void EnsureArgumentCountMatch(int argc)
{
	if (argc != 5)
		throw std::runtime_error("Invalid argument count\n"
			"Usage: replace.exe <inputFile> <outputFile> " 
			"<searchString> <replacementString>\n");
}

void EnsureFilesNotTheSame(const std::string infileName, const std::string outfileName)
{
	if (infileName == outfileName)
		throw std::runtime_error("Error! Files are the same\n");
}

arguments InitArguments(char* argv[])
{
	arguments args;

	args.inputFile = OpenFileOnRead(argv[1]);
	args.outputFile = OpenFileOnWrite(argv[2]);

	args.searchString = argv[3];
	args.replacementString = argv[4];

	return args;
}

std::ifstream OpenFileOnRead(const std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("Can not open file to read\n");

	return file;
}

std::ofstream OpenFileOnWrite(const std::string fileName)
{
	std::ofstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("Can not open file to write\n");

	return file;
}

void CopyStreamWithReplacement(arguments& args)
{
	std::string line;

	while (std::getline(args.inputFile, line))
	{
		args.outputFile << ReplaceString(line, args.searchString, args.replacementString) << "\n";
	}

	args.outputFile.flush();
	args.inputFile.close();
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0,
		sizeOfSearchString = searchString.length(),
		sizeOfreplacementString = replacementString.length();
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, std::string::npos);
			break;
		}
		else
		{
			result.append(subject, pos, foundPos - pos);
			result += replacementString;
			pos = foundPos + sizeOfSearchString;
		}
	}

	return result;
}