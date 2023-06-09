#include "StringUtils.h"
#include <cctype>
#include <algorithm>

std::string StringToLowerCaseCopy(const std::string& str)
{
	std::string toLowerCopy = str;

	std::transform(toLowerCopy.begin(), toLowerCopy.end(), toLowerCopy.begin(),
		[](char c) { return std::tolower(c); });

	return toLowerCopy;
}