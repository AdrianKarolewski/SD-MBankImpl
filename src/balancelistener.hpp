#pragma once

#include <string>

class IBalanceListener
{
public:
	virtual void balanceChanged(const std::string& _desc, const double& _amount) = 0;
};

class BalanceListenerRaport1000Up : public IBalanceListener
{
	void balanceChanged(const std::string& _desc, const double& _amount) override;
};