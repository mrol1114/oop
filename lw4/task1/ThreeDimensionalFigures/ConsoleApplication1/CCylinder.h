#pragma once

#include "CBody.h"

class CCylinder final: public CBody
{
public:
	CCylinder(double density, double height, double baseRadius);

	double GetVolume()const override;
	double GetBaseRadius()const;
	double GetHeight()const;

private:
	double m_baseRadius;
	double m_height;

	void AppendProperties(std::ostream& strm, const std::string& prefix = "") const override;
};