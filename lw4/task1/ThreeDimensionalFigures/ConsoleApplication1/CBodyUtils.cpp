#include <sstream>
#include <regex>
#include <algorithm>
#include <map>

#include "CBodyUtils.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "CCompound.h"

namespace
{
	using Properties = std::map<std::string, double>;
	using Compounds = std::vector<std::shared_ptr<CCompound>>;

	const auto REGEX_FOR_TYPE = std::regex(R"(\[[a-zA-Z]+\])");
	const auto REGEX_FOR_PROPERTY = std::regex(R"(([a-zA-Z]+)=(.*?))");
	const auto REGEX_FOR_ZERO_VALUE = std::regex(R"([0]+.?[0]*)");
	const std::string END_TYPE_TEXT = "[end_type]";

	struct Property
	{
		std::string key;
		double value;
	};

	const enum class BODY_TYPE
	{
		compound = 0,
		cone,
		cylinder,
		parallelepiped,
		sphere,
	};

	const std::map<std::string, BODY_TYPE> STRING_TO_BODY_TYPE = {
		{"cone", BODY_TYPE::cone},
		{"cylinder", BODY_TYPE::cylinder},
		{"parallelepiped", BODY_TYPE::parallelepiped},
		{"sphere", BODY_TYPE::sphere},
		{"compound", BODY_TYPE::compound}
	};

	const std::vector<std::string> PROPERTIES_KEYS = {
		"density", "height", "baseRadius", "width", "depth", "radius"
	};

	std::vector<std::string> Split(const std::string& s, char delim) {
		std::vector<std::string> result;
		std::stringstream ss(s);
		std::string item;

		while (getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	void RemoveSpaces(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	}

	BODY_TYPE GetBodyType(std::string type)
	{
		auto isSquareBracket = [](char ch) {return ch == ']' || ch == '[';};
		type.erase(std::remove_if(type.begin(), type.end(), isSquareBracket), type.end());

		if (STRING_TO_BODY_TYPE.find(type) == STRING_TO_BODY_TYPE.end())
		{
			throw std::exception("invalid type");
		}

		return STRING_TO_BODY_TYPE.at(type);
	}

	Property GetProperty(const std::string& line)
	{
		const char DELIMITER = '=';

		auto property = Split(line, DELIMITER);

		if (std::find(PROPERTIES_KEYS.begin(), PROPERTIES_KEYS.end(), property[0])
			== PROPERTIES_KEYS.end())
		{
			throw std::runtime_error("invalid key for property");
		}

		return {property[0], stod(property[1])};
	}

	void EnsurePropertiesExists(BODY_TYPE type, const Properties& properties)
	{
		switch (type)
		{
		case BODY_TYPE::cone:
		case BODY_TYPE::cylinder:
			if (properties.find("density") != properties.end()
				&& properties.find("height") != properties.end()
				&& properties.find("baseRadius") != properties.end())
			{
				return;
			}
			break;

		case BODY_TYPE::parallelepiped:
			if (properties.find("density") != properties.end()
				&& properties.find("height") != properties.end()
				&& properties.find("width") != properties.end()
				&& properties.find("depth") != properties.end())
			{
				return;
			}
			break;

		case BODY_TYPE::sphere:
			if (properties.find("density") != properties.end()
				&& properties.find("radius") != properties.end())
			{
				return;
			}
			break;
		}

		throw std::invalid_argument("missing properties");
	}

	std::shared_ptr<CBody> CreateBody(BODY_TYPE type, const Properties& properties)
	{
		EnsurePropertiesExists(type, properties);

		switch (type)
		{
		case BODY_TYPE::cone:
			return std::make_shared<CCone>(
				properties.at("density"), properties.at("height"), properties.at("baseRadius"));
			break;

		case BODY_TYPE::cylinder:
			return std::make_shared<CCylinder>(
				properties.at("density"), properties.at("height"), properties.at("baseRadius"));
			break;

		case BODY_TYPE::parallelepiped:
			return std::make_shared<CParallelepiped>(
				properties.at("density"), properties.at("height"),
				properties.at("width"), properties.at("depth"));
			break;

		case BODY_TYPE::sphere:
			return std::make_shared<CSphere>(
				properties.at("density"), properties.at("radius"));
			break;

		default:
			throw std::exception("invalid type");
		}
	}

	std::shared_ptr<CCompound> CreateCompound(const Bodies& bodies)
	{
		return std::make_shared<CCompound>(bodies);
	}

	double CalculateWeightInWater(const Body& body)
	{
		const double DENSITY_OF_WATER = 1000;
		const double ACCELERATION_OF_GRAVITY = 9.81;

		return (body->GetDensity() - DENSITY_OF_WATER) * ACCELERATION_OF_GRAVITY * body->GetVolume();
	}

	void AppendCompound(Compounds& compounds, Bodies& bodies)
	{
		Body body = std::static_pointer_cast<CBody>(compounds.back());
		compounds.pop_back();

		if (compounds.size() == 0)
		{
			bodies.push_back(body);
		}
		else
		{
			compounds.back()->AddChildBody(body);
		}
	}

	void AppendNewBody(Bodies& bodies, Compounds& compounds, std::vector<BODY_TYPE>& uninitializedBodies, Body& body)
	{
		if (uninitializedBodies.size() != 0
			&& uninitializedBodies.back() == BODY_TYPE::compound)
		{
			compounds.push_back(CreateCompound({ body }));
			uninitializedBodies.pop_back();
			return;
		}

		if (compounds.size() == 0)
		{
			bodies.push_back(body);
		}
		else
		{
			compounds.back()->AddChildBody(body);
		}
	}

	void CheckBalance(int balance)
	{
		if (balance != 0)
		{
			throw std::runtime_error("Invalid syntax");
		}
	}
}

void ReadCBodiesInVector(std::istream& input, Bodies& bodies)
{
	Compounds compounds;
	std::vector<BODY_TYPE> uninitializedBodies;
	Properties properties;
	int balance = 0;

	std::string line;
	while (balance >= 0 && std::getline(input, line))
	{
		RemoveSpaces(line);

		if (std::regex_match(line, REGEX_FOR_TYPE))
		{
			balance++;
			auto type = GetBodyType(line);

			uninitializedBodies.push_back(type);
		}
		else if (std::regex_match(line, REGEX_FOR_PROPERTY))
		{
			auto property = GetProperty(line);
			properties[property.key] = property.value;
		}
		else if (line == END_TYPE_TEXT)
		{
			balance--;

			if (uninitializedBodies.size() == 0 && compounds.size() > 0)
			{
				AppendCompound(compounds, bodies);

				continue;
			}

			auto body = CreateBody(uninitializedBodies.back(), properties);
			uninitializedBodies.pop_back();
			properties.clear();

			AppendNewBody(bodies, compounds, uninitializedBodies, body);
		}
	}

	CheckBalance(balance);
}

Body GetBodyWithBiggestMass(const Bodies& bodies)
{
	if (bodies.size() == 0)
	{
		return nullptr;
	}
	
	auto compare = [](const Body& firstElm, const Body& secondElm)
	{
		return firstElm->GetMass() < secondElm->GetMass();
	};

	return *std::max_element(bodies.begin(), bodies.end(), compare);
}

Body GetLightestBodyInWater(const Bodies& bodies)
{
	if (bodies.size() == 0)
	{
		return nullptr;
	}

	auto compare = [](const Body& firstElm, const Body& secondElm)
	{
		return CalculateWeightInWater(firstElm) < CalculateWeightInWater(secondElm);
	};

	return *std::min_element(bodies.begin(), bodies.end(), compare);
}

void PrintInfoAboutBodies(std::ostream& output, const Bodies& bodies)
{
	if (bodies.empty())
	{
		return;
	}

	for (const Body& body : bodies)
	{
		output << body->ToString();
	}
	output << std::endl;

	output << "Body with biggest mass" << std::endl
		<< GetBodyWithBiggestMass(bodies)->ToString() << std::endl;

	output << "Lightest body in water" << std::endl
		<< GetLightestBodyInWater(bodies)->ToString();
}