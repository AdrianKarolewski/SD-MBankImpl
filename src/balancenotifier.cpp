#include "balancenotifier.hpp"

void BalanceNotifier::notify(const std::string& _desc, const double& _amount)
{
	for (auto l : listeners)
		l->balanceChanged(_desc, _amount);
}

void BalanceNotifier::subscribe(IBalanceListener* _s)
{
	listeners.emplace_back(_s);
}

void BalanceNotifier::unsubscribe(IBalanceListener* _s)
{
	auto it = std::find(listeners.begin(), listeners.end(), _s);
	if (it != listeners.end())
		listeners.erase(it);
}