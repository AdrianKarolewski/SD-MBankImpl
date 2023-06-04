#include "utils.hpp"
#include <ctime>

bool Doubles::compare(const double& _a, const double& _b)
{
	auto diff = _a - _b;
	double r{ 0.0000001 };
	return (diff < r) && (-diff < r);
}

Date::Date Date::currentDate()
{
    const int BASE_YEAR = 1900;
    time_t timer;
    tm* time;
    std::time(&timer);
    time = localtime(&timer);

    return { time->tm_mday, time->tm_mon + 1, time->tm_year + BASE_YEAR };
}

bool Date::operator==(const Date& _d1, const Date& _d2)
{
    return _d1.day == _d2.day && _d1.month == _d2.month && _d1.year == _d2.year;
}

bool Date::operator<(const Date& _d1, const Date& _d2)
{
    if (_d1.year < _d2.year)
        return true;
    if (_d1.year == _d2.year)
    {
        if (_d1.month < _d2.month)
            return true;
        if (_d1.month == _d2.month)
        {
            if (_d1.day < _d2.day)
                return true;
        }
    }
    return false;
}

bool Date::operator>(const Date& _d1, const Date& _d2)
{
    return !(_d1 < _d2);
}