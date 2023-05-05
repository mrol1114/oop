#pragma once

#include <string>

class CBody
{
public:
	const double M_PI = 3.14;

	CBody(std::string type, double density);
	virtual ~CBody() = default;
	virtual double GetDensity() const;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	virtual std::string ToString(const std::string& prefix = "") const;

private:
	double m_density;
	std::string m_type;

	virtual void AppendProperties(std::ostream& strm, const std::string& prefix = "") const = 0;
};