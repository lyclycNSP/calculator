// a simple calculator based on command line
// the calculation logic of this calculator is based on
// both the operation numbers are positive
// if not the case, perform equivalent conversion to other case
// so the functions can be used repeatedly

#include "../lib/calculator.h"
#include "../lib/addition.h"
#include "../lib/subtraction.h"
#include "../lib/multiplication.h"
#include "../lib/division.h"

using namespace std;
using namespace calculator;
using namespace addition;
using namespace subtraction;
using namespace multiplication;
using namespace division;

int main()
{
    // get the first number
    string first_num = get_num();

    // get the operation symbol;
    string symbol = get_symbol();

    // get the second number
    string second_num = get_num();

    // check if the numbers are negative
    bool is_first_num_neg = is_neg(first_num);
    bool is_sec_num_neg = is_neg(second_num);

    string ans;

    //classify addition and subtraction into a few categories
    
    
    if(symbol[0] == '+' or symbol[0] == '-')
    {
        //first: both numbers are positive 
        if(!is_first_num_neg and !is_sec_num_neg)
        {
            switch(symbol[0])
            {
                case '+':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_addition(first_num, second_num);
        
                    else
                        ans = integer_addition(first_num, second_num);

                    break;
                }
                
                case '-':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_subtraction(first_num, second_num);

                    else
                        ans = integer_subtraction(first_num, second_num);

                    break;
                }
                default: ans = "Bug:the switch case fall into default";
            }
        }
        
        //second: the first number is negative, the second is positive
        else if(is_first_num_neg and !is_sec_num_neg)
        {
            to_absolute(first_num);
            switch(symbol[0])
            {
                // this case is equivalent to sec - abs(fir)
                case '+':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_subtraction(second_num, first_num);

                    else 
                        ans = integer_subtraction(second_num, first_num);

                    break;
                }

                // this case is equivalent to -(abs(fir) + sec)
                case '-':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_addition(first_num, second_num);

                    else 
                        ans = integer_addition(first_num, second_num);
                    
                    // the final ans should be the return value's negative
                    if(ans.at(0) == '-')
                        ans.erase(0, 1);
                    else 
                        ans.insert(ans.begin(), '-');
                    break;

                }
                default: ans = "Bug:the switch case fall into default";break;
            }
        }

        //third: the first number is positive, the second is negative
        else if(!is_first_num_neg and is_sec_num_neg)
        {
            to_absolute(second_num);
            switch(symbol[0])
            {
                //this case is equivalent to fir - abs(sec)
                case '+':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_subtraction(first_num, second_num);
                
                    else
                        ans = integer_subtraction(first_num, second_num);

                    break;
                }

                //this case is equivalent to fir + abs(sec)
                case '-':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_addition(first_num, second_num);

                    else 
                        ans = integer_addition(first_num, second_num);
                    
                    break;
                }

                default: ans = "Bug:the switch case fall into default";break;
            }
        }
        
        //fourth: both numbers are negative
        else if(is_first_num_neg and is_sec_num_neg)
        {
            to_absolute(first_num);
            to_absolute(second_num);
            switch(symbol[0])
            {
                // this case is equivalent to -(abs(fir) + abs(sec))
                case '+':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_addition(first_num, second_num);
                    
                    else 
                        ans = integer_addition(first_num, second_num);
                        
                    // the final ans should be the return value's negative
                    if(ans.at(0) == '-')
                        ans.erase(0, 1);
                    else 
                        ans.insert(ans.begin(), '-');

                    break;
                }

                // this case is equivalent to abs(sec) - abs(fir)
                case '-':
                {
                    if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
                        ans = floating_point_subtraction(second_num, first_num);
                    
                    else
                        ans = integer_subtraction(second_num, first_num);

                    break;
                }

                default: ans = "Bug:the switch case fall into default";break;
            }
        }
    }
    
    // multiplication and division don't care about the signs when calculating
    // else if(symbol == '*' or symbol == '/')
    // {
    //     to_absolute(first_num);
    //     to_absolute(second_num);
    //     if(is_first_num_neg == is_sec_num_neg)
    //     {
    //         switch(symbol)
    //         {
    //             case '*':
    //             {
    //                 if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
    //                     ans = floating_point_multiplication(first_num, second_num);
                    
    //                 else
    //                     ans = integer_multiplication(first_num, second_num);
    //             }

    //             case '/':
    //             {
    //                 if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
    //                     ans = floating_point_division(first_num, second_num);
                    
    //                 else
    //                     ans = integer_division(first_num, second_num);
                    
    //                 break;
    //             }

    //             default: ans = "Bug:the switch case fall into default";break;
    //         }
    //     }

    //     else
    //     {
    //         if(is_first_num_neg != is_sec_num_neg)
    //         {
    //             switch(symbol)
    //             {
    //                 case '*':
    //                 {
    //                     if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
    //                         ans = floating_point_multiplication(first_num, second_num);
                        
    //                     else 
    //                         ans = integer_multiplication(first_num, second_num);
                        
    //                     break;
    //                     }
                        
    //                     case '/':
    //                     {
    //                         if(is_a_floating_point(first_num) or is_a_floating_point(second_num))
    //                             ans = floating_point_division(first_num, second_num);
                            
    //                         else
    //                             ans = integer_division(first_num, second_num);
                            
    //                         break;
    //                     }
    //                     default: ans = "Bug:the switch case fall into default";break;
    //                 }
    //             }
    //             ans.insert(ans.begin(), '-');
    //         }
    // }
     
    cout << "The result is " << ans << endl;
}
