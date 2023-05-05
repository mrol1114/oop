#include "CBody.h"
#include <sstream>
#include <iomanip>

CBody::CBody(std::string type, double density)
	: m_type(type)
	, m_density(density)
{

}

double CBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

std::string CBody::ToString(const std::string& prefix) const
{
	std::ostringstream strm;
	strm << prefix <<  "[" << m_type << "]" << std::endl << std::setprecision(10)
		<< prefix << "\tdensity = " << GetDensity() << std::endl
		<< prefix << "\tvolume = " << GetVolume() << std::endl
		<< prefix << "\tmass = " << GetMass() << std::endl;
	AppendProperties(strm, prefix);
	strm  << prefix << "[end_type]" << std::endl << std::endl;

	return strm.str();
}

double CBody::GetDensity() const
{
	return m_density;
}