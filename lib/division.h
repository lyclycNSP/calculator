#ifndef DIVISION_H
#define DIVISION_H

#include "calculator.h"
namespace division
{
    string integer_division(string, string, long long);
    string floating_point_division(string, string, long long);
    string decide_divident(string, string, size_t&, string&);
    string divide(string, string, string&);
}; //namespace division

#endif
