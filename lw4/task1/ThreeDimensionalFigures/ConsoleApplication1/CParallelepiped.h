#pragma once

#include "CBody.h"

class CParallelepiped final: public CBody
{
public:
	CParallelepiped(double density, double height, double width, double depth);

	double GetVolume()const override;
	double GetWidth()const;
	double GetHeight()const;
	double GetDepth()const;

private:
	double m_height;
	double m_width;
	double m_depth;

	void AppendProperties(std::ostream& strm, const std::string& prefix = "") const override;
};