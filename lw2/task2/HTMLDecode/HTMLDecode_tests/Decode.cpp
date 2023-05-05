#include "Decode.h"

using Map = std::map<std::string, std::string>;

namespace
{
	Map GetDecodeMap()
	{
		return {
			{"&quot;", "\""},
			{"&apos;", "'"},
			{"&lt;", "<"},
			{"&gt;", ">"},
			{"&amp;", "&"}
		};
	}

	std::string DecodeString(const std::string& line, const Map& replacementMap)
	{
		const char tagStartSymbol = '&';
		const char tagEndSymbol = ';';

		std::string result;
		result.reserve(line.size());

		size_t pos = 0;

		while (pos < line.length())
		{
			size_t tagStartSymbolPos = line.find(tagStartSymbol, pos);
			size_t secondTagStartSymbolPos = std::string::npos;
			size_t tagEndSymbolPos = std::string::npos;
			std::string tag;

			if (tagStartSymbolPos != std::string::npos)
			{
				tagEndSymbolPos = line.find(tagEndSymbol, tagStartSymbolPos);
			}

			if (tagEndSymbolPos == std::string::npos)
			{
				result.append(line, pos, std::string::npos);
				break;
			}

			secondTagStartSymbolPos = line.find(tagStartSymbol, tagStartSymbolPos + 1);
			if (secondTagStartSymbolPos != std::string::npos && tagEndSymbolPos > secondTagStartSymbolPos)
			{
				result.append(line, pos, secondTagStartSymbolPos);
				pos = secondTagStartSymbolPos;
				continue;
			}

			tag = line.substr(tagStartSymbolPos, tagEndSymbolPos + 1 - tagStartSymbolPos);
			result.append(line, pos, tagStartSymbolPos - pos);

			result += replacementMap.contains(tag) ? replacementMap.at(tag) : tag;

			pos = tagEndSymbolPos + 1;
		}

		return result;
	}
}

void CopyStreamWithHTMLDecode(std::istream& input, std::ostream& output)
{
	std::string line;
	auto replacementMap = GetDecodeMap();

	while (std::getline(input, line))
	{
		output << DecodeString(line, replacementMap) << std::endl;
	}
}