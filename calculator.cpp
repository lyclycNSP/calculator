#include "calculator.h"

// get arithmetic number from user
string calculator::get_num()
{
    string num;
    cout << "Enter a number: " << endl;
    getline(cin,num);
    return num;
}

// get arithmetic symbol from user
string calculator::get_symbol()
{
    string symbol;
    cout << "Enter a symbol: " << endl;
    getline(cin,symbol);
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

// apply addition to two reversed integer
string calculator::reverse_addition(string fir, string sec)
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
        int sum = (fir[index] - '0') + (sec[index] - '0') + carry;
        carry = sum / 10;
        result = sum % 10;
        
        ans.append(to_string(result));
    }

    if(index != length_fir)
    {
        for( ;index < length_fir; index++)
        {
            int sum = (fir[index] - '0') + carry;
            carry = sum / 10;
            result = sum % 10;

            ans.append(to_string(result));
        }
    }

    else if(index != length_sec)
    {
        for( ;index < length_sec; index++)
        {
            int sum = sec[index] - '0' + carry;
            carry = sum / 10;
            result = sum % 10;

            ans.append(to_string(result));
        }
    }

    if(carry != 0)
        ans.append(to_string(carry));
    
    reverse(ans.begin(),ans.end());
    // delete_leading_zero(ans);
    return ans;
}

// delete the leading zero of the correct result
void calculator::delete_leading_zero(string& ans)
{
    size_t length = ans.length();
    for(size_t i = 0; i < length; i++)
    {
        if(ans[i] != 0)
            break;
        else
        {
            ans.erase(i,1);
            i--;
        }
    }
    return;
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
pair<string, string> calculator::split_flot(string num)
{
    pair<string, string> splited_num;

    if(!is_a_floating_point(num))
    {
        splited_num.first = num;
        splited_num.second = "";
    }
    auto decimal_pos = num.find('.');
    splited_num.first = num.substr(0,decimal_pos);
    splited_num.second = num.substr(decimal_pos + 1);
    
    return splited_num;
}

// add two floating points
string calculator::floating_point_addition(string fir, string sec)
{
    string ans;
    auto fir_splited = split_flot(fir);
    auto sec_splited = split_flot(sec);
    
    string sum_after_decimal;
    string sum_before_decimal;
    sum_before_decimal = integer_addition(fir_splited.first, sec_splited.first);

    if(if_carry(fir_splited.second, sec_splited.second))
    {
        sum_after_decimal = integer_addition(fir_splited.second, sec_splited.second);
        sum_after_decimal.erase(0, 1);

        // add the carry to the sum
        sum_before_decimal = integer_addition(sum_before_decimal, "1");

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    else
    {
        sum_after_decimal = integer_addition(fir_splited.second, sec_splited.second);

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    return ans; 
}



