#include <iostream>

#include "CCylinder.h"

CCylinder::CCylinder(double density, double height, double baseRadius)
	: CBody("cylinder", density)
	, m_height(height)
	, m_baseRadius(baseRadius)
{
	if (density < 0 || height < 0 || baseRadius < 0)
	{
		throw std::invalid_argument("Body properties values cant be less than zero");
	}
}

double CCylinder::GetVolume() const
{
	return M_PI * m_baseRadius * m_baseRadius * m_height;
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

void CCylinder::AppendProperties(std::ostream& strm, const std::string& prefix) const
{
	strm << prefix << "\tbaseRadius = " << GetBaseRadius() << std::endl;
	strm << prefix << "\theight = " << GetHeight() << std::endl;
}
