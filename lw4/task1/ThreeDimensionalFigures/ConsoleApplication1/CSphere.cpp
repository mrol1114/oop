#include <iostream>

#include "CSphere.h"

CSphere::CSphere(double density, double radius)
	: CBody("sphere", density)
	, m_radius(radius)
{
	if (density < 0 || radius < 0)
	{
		throw std::invalid_argument("Body properties values cant be less than zero");
	}
}

double CSphere::GetVolume() const
{
	return M_PI * 4 / 3 * m_radius * m_radius * m_radius;
}

double CSphere::GetRadius() const
{
	return m_radius;
}

void CSphere::AppendProperties(std::ostream& strm, const std::string& prefix) const
{
	strm << prefix << "\tradius = " << GetRadius() << std::endl;
}
