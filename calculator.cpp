#include "calculator.h"

// get arithmetic number from user
string calculator::get_num()
{
    string num;
    getline(cin,num);
    return num;
}

// get arithmetic symbol from user
char calculator::get_symbol()
{
    char symbol;
    cin >> symbol;
    return symbol;
}

// judge if the number is a floating point
bool calculator::is_a_floating_point(string num)
{
    if(num.find('.') == string::npos)
        return false;
    else 
        return true;
}


string reverse_addition(string fir, string sec)
{
    string ans;
    
    int carry{};  //the carry produced by every two digit'sum
    int result{}; //the number minus carry from the sum
    size_t length_fir = fir.length();
    size_t length_sec = sec.length();
    auto min_length = min(length_fir, length_sec);

    size_t index{};
    for(;index < min_length; index++)
    {
        int sum = atoi(&fir[index]) + atoi(&sec[index]) + carry;
        carry = sum % 10;
        result = sum / 10;
        
        ans.append(to_string(result));
    }
    
    if(index != length_fir)
    {
        for( ;index < length_fir; index++)
        {
            int sum = atoi(&fir[index]) + carry;
            carry = sum % 10;
            result = sum / 10;

            ans.append(to_string(result));
        }
    }

    else if(index != length_sec)
    {
        for( ;index < length_sec; index++)
        {
            int sum = atoi(&sec[index]) + carry;
            carry = sum % 10;
            result = sum / 10;

            ans.append(to_string(result));
        }
    }
    
    ans.append(to_string(carry));
    
    reverse(ans.begin(),ans.end());
    return ans;
}

// add two integers
string calculator::integer_addition(string fir, string sec)
{
    string ans;
    reverse(fir.begin(), fir.end());
    reverse(sec.begin(), sec.end());
    
    ans = reverse_addition(fir, sec);
    return ans;
}

// judge if two integer's addition produce a carry
bool calculator::if_carry(string fir, string sec)
{
    auto max_length = max(fir.length(), sec.length());
    
    auto sum = integer_addition(fir, sec);

    auto sum_length = sum.length();
    if(sum_length > max_length)
        return true;
    else
        return false;
}

// reverse a floating point
// put the result in a pair, put the before-decimal part into the first
// the rest into the second
pair<string, string> reverse_flot(string num)
{
    pair<string, string> reversed_num;

    int decimal_pos = num.find('.');
    reversed_num.first = num.substr(0,decimal_pos);
    reversed_num.second = num.substr(decimal_pos + 1);
    
    return reversed_num;
}

// add two floating points
string calculator::floating_point_addition(string fir, string sec)
{
    string ans;
    auto fir_rev = reverse_flot(fir);
    auto sec_rev = reverse_flot(sec);
    
    string sum_after_decimal;
    string sum_before_decimal;
    sum_before_decimal = reverse_addition(fir_rev.first, sec_rev.first);

    if(if_carry(fir_rev.second, sec_rev.second))
    {
        sum_after_decimal = reverse_addition(fir_rev.second, sec_rev.second);
        sum_after_decimal.erase(0, 1);

        // add the carry to the sum
        sum_before_decimal = integer_addition(sum_before_decimal, "1");

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    else
    {
        sum_after_decimal = reverse_addition(fir_rev.second, sec_rev.second);

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    return ans; 
}



