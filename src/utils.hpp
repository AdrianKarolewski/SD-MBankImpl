#pragma once

#include <ctime>

namespace Doubles
{
    bool compare(const double& _a, const double& _b);
}

namespace Date
{
    struct Date
    {
        int day;
        int month;
        int year;
    };
    Date currentDate();
    bool operator==(const Date& _d1, const Date& _d2);
    bool operator<(const Date& _d1, const Date& _d2);
    bool operator>(const Date& _d1, const Date& _d2);
 }