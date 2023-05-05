#pragma once

#include <string>

#include "CBody.h"

class CSphere final: public CBody
{
public:
	CSphere(double density, double radius);

	double GetRadius()const;
	double GetVolume()const override;

private:
	double m_radius;

	void AppendProperties(std::ostream& strm, const std::string& prefix = "") const override;
};