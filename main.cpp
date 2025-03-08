// a simple calculator based on command line
#include "calculator.h"
using namespace std;
using namespace addition;
using namespace subtraction;

int main()
{
    // get the first number
    string first_num = get_num();

    // get the operation symbol;
    string sym = get_symbol();

    // get the second number
    string second_num = get_num();

    string ans;
    
    switch(sym[0])
    {
        case '+':
        {
            if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
            {
                ans = floating_point_addition(first_num, second_num);
                break;
            }

            else 
            {
                ans = integer_addition(first_num, second_num);
                break;
            }
        }
        default: cout << "Invalid symbol!";return -1;
    }

    cout << "The result is " << ans << endl;
}
