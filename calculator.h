#ifndef CALCULATE_H
#define CALCULATE_H

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <utility>
using namespace std;

namespace calculator
{
    string get_num();
    string get_symbol();
    bool is_a_floating_point(string);
    string floating_point_addition(string, string);
    string integer_addition(string, string);
    bool if_carry(string, string);
    pair<string,string> split_flot(string);
    string reverse_addition(string, string);
    void delete_leading_zero(string&);
}

#endif
