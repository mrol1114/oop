#include <iostream>

#include "CCone.h"

CCone::CCone(double density, double height, double baseRadius)
	: CBody("cone", density)
	, m_height(height)
	, m_baseRadius(baseRadius)
{
	if (density < 0 || height < 0 || baseRadius < 0)
	{
		throw std::invalid_argument("Body properties values cant be less than zero");
	}
}

double CCone::GetVolume()const
{
	return M_PI / 3 * m_baseRadius * m_baseRadius * m_height;
}

double CCone::GetBaseRadius()const
{
	return m_baseRadius;
}

double CCone::GetHeight()const
{
	return m_height;
}

void CCone::AppendProperties(std::ostream& strm, const std::string& prefix) const
{
	strm << prefix << "\tbaseRadius = " << GetBaseRadius() << std::endl;
	strm << prefix << "\theight = " << GetHeight() << std::endl;
}
