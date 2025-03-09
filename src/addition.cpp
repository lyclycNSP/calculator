#include "lib/addition.h"
#include "lib/calculator.h"

// apply addition to two reversed integer
string addition::reverse_addition(string fir, string sec)
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

// add two integers
string addition::integer_addition(string fir, string sec)
{
    string ans;
    reverse(fir.begin(), fir.end());
    reverse(sec.begin(), sec.end());
    
    ans = reverse_addition(fir, sec);
    return ans;
}

string addition::decimal_addition(string fir, string sec)
{
    string ans;
    size_t fir_length = fir.length();
    size_t sec_length = sec.length();

    if(fir_length == sec_length)
        ans = integer_addition(fir,sec);
    else
    {
        string biggerNum = fir_length > sec_length ? fir : sec;
        string smallerNum = fir_length < sec_length ? fir : sec;

        size_t maxlength = biggerNum.length();
        size_t minlength = smallerNum.length();

        string truncted_left_Num = biggerNum.substr(0,minlength);
        string trunctedNum = biggerNum.substr(minlength, maxlength - minlength);
        ans = integer_addition(truncted_left_Num, smallerNum);
        ans.append(trunctedNum);
    }
    return ans;
}

// add two floating points
string addition::floating_point_addition(string fir, string sec)
{
    string ans;
    auto fir_splited = calculator::split_flot(fir);
    auto sec_splited = calculator::split_flot(sec);
    
    string sum_after_decimal;
    string sum_before_decimal;
    sum_before_decimal = integer_addition(fir_splited.first, sec_splited.first);

    if(calculator::if_carry(fir_splited.second, sec_splited.second))
    {
        sum_after_decimal = decimal_addition(fir_splited.second, sec_splited.second);
        sum_after_decimal.erase(0, 1);

        // add the carry to the sum
        sum_before_decimal = integer_addition(sum_before_decimal, "1");

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    else
    {
        sum_after_decimal = decimal_addition(fir_splited.second, sec_splited.second);

        //combine two sums
        ans = sum_before_decimal + "." + sum_after_decimal;
    }

    return ans; 
}
