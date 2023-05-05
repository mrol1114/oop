#include <iostream>

#include "CCompound.h"

CCompound::CCompound(const std::vector<std::shared_ptr<CBody>> bodies)
	: CBody("compound", 0)
	, m_childs(bodies)
{
	if (bodies.size() == 0)
	{
		throw std::runtime_error("compound body must have at least one child");
	}
}

CCompound::~CCompound()
{

}

bool CCompound::IsContainsSameBody(std::shared_ptr<CBody> addingBody, const CCompound* mainBody) const
{
	if (mainBody == addingBody.get())
	{
		return true;
	}

	auto compound = std::dynamic_pointer_cast<CCompound>(addingBody);
	if (compound)
	{
		for (const std::shared_ptr<CBody>& body: compound->GetChilds())
		{
			if (mainBody == body.get())
			{
				return true;
			}

			auto internalCompound = std::dynamic_pointer_cast<CCompound>(body);
			if (internalCompound
				&& internalCompound->IsContainsSameBody(addingBody, mainBody))
			{
				return true;
			}
		}
	}

	return false;
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> body)
{
	if (IsContainsSameBody(body, this))
	{
		return false;
	}

	m_childs.push_back(body);
	return true;
}

std::vector<std::shared_ptr<CBody>> CCompound::GetChilds() const
{
	return m_childs;
}

double CCompound::GetDensity() const
{
	double volume = GetVolume();
	if (volume == 0)
	{
		return 0;
	}

	return GetMass() / volume;
}

double CCompound::GetVolume()const
{
	double volume = 0;
	for (const std::shared_ptr<CBody>& body: m_childs)
	{
		volume += body->GetVolume();
	}

	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (const std::shared_ptr<CBody>& body: m_childs)
	{
		mass += body->GetMass();
	}

	return mass;
}

void CCompound::AppendProperties(std::ostream& strm, const std::string& prefix) const
{
	strm << std::endl;
	for (const std::shared_ptr<CBody>& body: m_childs)
	{
		strm << body->ToString(prefix + "\t");
	}
}
