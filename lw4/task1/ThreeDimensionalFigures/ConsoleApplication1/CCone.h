#pragma once

#include "CBody.h"

class CCone final: public CBody // выделить новый класс
{
public:
	CCone(double density, double height, double baseRadius);

	double GetVolume()const override;
	double GetBaseRadius()const;
	double GetHeight()const;

private://методы выше полей
	double m_baseRadius;
	double m_height;

	void AppendProperties(std::ostream& strm, const std::string& prefix = "") const override;
};