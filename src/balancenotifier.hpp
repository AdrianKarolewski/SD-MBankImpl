#pragma once

#include "balancelistener.hpp"
#include <vector>

class BalanceNotifier
{
public:
	void notify(const std::string& _desc, const double& _amount);
	void subscribe(IBalanceListener* _s);
	void unsubscribe(IBalanceListener* _s);

private:
	std::vector<IBalanceListener*> listeners;
};