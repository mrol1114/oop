#include <iostream>

#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double density, double height, double width, double depth)
	: CBody("parallelepiped", density)
	, m_height(height)
	, m_width(width)
	, m_depth(depth)
{
	if (density < 0 || height < 0 || width < 0 || depth < 0)
	{
		throw std::invalid_argument("Body properties values cant be less than zero");
	}
}

double CParallelepiped::GetVolume() const
{
	return m_height * m_width * m_depth;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

void CParallelepiped::AppendProperties(std::ostream& strm, const std::string& prefix) const
{
	strm << prefix << "\twidth = " << GetWidth() << std::endl;
	strm << prefix << "\theight = " << GetHeight() << std::endl;
	strm << prefix << "\tdepth = " << GetDepth() << std::endl;
}
