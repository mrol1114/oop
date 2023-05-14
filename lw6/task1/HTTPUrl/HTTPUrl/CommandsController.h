#pragma once
#include <string>
#include <memory>
#include "CHttpUrl.h"

class CommandsController
{
public:
	bool ReadUrl(std::istream& input, std::ostream& output, std::string& url);
	void PrintInfoAboutUrl(std::ostream& output, const CHttpUrl& url);
};