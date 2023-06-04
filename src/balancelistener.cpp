#include "balancelistener.hpp"
#include <iostream>

void BalanceListenerRaport1000Up::balanceChanged(const std::string& _desc, const double& _amount)
{
	if (_amount >= 1000 || _amount <= 1000)
	{
		std::cout << _desc << std::endl;
	}
}