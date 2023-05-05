#pragma once

#include "CBody.h"
#include <vector>

class CCompound final: public CBody
{
public:
	CCompound(const std::vector<std::shared_ptr<CBody>> bodies);
	~CCompound();

	bool AddChildBody(std::shared_ptr<CBody> child);
	std::vector<std::shared_ptr<CBody>> GetChilds() const;
	double GetDensity()const override;
	double GetVolume()const override;
	double GetMass()const override;

private:
	std::vector<std::shared_ptr<CBody>> m_childs;

	void AppendProperties(std::ostream& strm, const std::string& prefix = "") const override;
	bool IsContainsSameBody(std::shared_ptr<CBody> addingBody, const CCompound* mainBody) const;
};