#include "lib/calculator.h"
#include "lib/subtraction.h"

// inside main, where this function is called, both numbers are preserved to be positive
// whereever this function is called, make sure that the numbers passed in are positive
// besides, this function can decide which number is bigger
// so don't worry the order of the two parameters
// this function can also make sure larger one minus smaller one
string subtraction::integer_subtraction(string fir, string sec)
{
    string ans;

    int flag =  calculator::which_is_bigger(fir, sec);

    reverse(fir.begin(), fir.end());
    reverse(sec.begin(), sec.end());

    if(flag == 1)
        ans = reverse_subtraction(fir, sec);
    else if(flag == -1)
    {
        ans = reverse_subtraction(sec, fir);
        // take the opposite of the answer
        ans.insert(ans.begin(), '-');
    }

    else if(flag == 0)
        ans = "0";
    return ans;
}

// return the remainder
// fir is absolutely bigger than sec
// so the difference must be positive
// remember that both string are REVERSED
string subtraction::reverse_subtraction(string fir, string sec)
{
    string ans;

    size_t minlength = sec.length();
    size_t maxlength = fir.length();

    //always non-negative here
    int borrow{};
    int result{};
    size_t i{};
    for(; i < minlength; i++)
    {
        result = (fir[i] - '0' - borrow) - (sec[i] - '0');

        if(result < 0)
        {
            result += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        ans.append(to_string(result));
    }

    while(i < maxlength)
    {
        result = fir[i] - '0' - borrow;
        if(result < 0)
        {
            result += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        ans.append(to_string(result));
        i++;
    }
    reverse(ans.begin(), ans.end());
    calculator::delete_leading_zero(ans);

    return ans;
}

// apply subtraction to two floating points numbers
// both of the numbers are guarded to be positive
string subtraction::floating_point_subtraction(string fir, string sec)
{
    string ans{};

    auto splited_fir = calculator::split_flot(fir);
    auto splited_sec = calculator::split_flot(sec);

    
    auto diff_before_decimal = integer_subtraction(splited_fir.first, splited_sec.first);
    auto diff_after_decimal = decimal_subtraction(splited_fir.second, splited_sec.second);

    bool int_pt_neg = calculator::is_neg(diff_before_decimal);
    bool dec_pt_neg = calculator::is_neg(diff_after_decimal);

    // both are negative
    if(int_pt_neg and dec_pt_neg)
    {
        diff_after_decimal.erase(0, 1);
        ans = diff_before_decimal + "." + diff_after_decimal;
    }

    // both are positive
    else if(!int_pt_neg and !dec_pt_neg)
        ans = diff_before_decimal + "." + diff_after_decimal;

    // integer part is positive while decimal part is not
    else if(!int_pt_neg and dec_pt_neg)
    {
        if(diff_before_decimal != "0")
        {
            // borrow 1 from the integer part
            diff_before_decimal = integer_subtraction(diff_before_decimal, "1");

            // remove the sign before the string
            diff_after_decimal.erase(0, 1);

            // 1 borrow from units should be ten in tenth place
            // the result must be positive
            diff_after_decimal = integer_subtraction("10", diff_after_decimal);

            ans = diff_before_decimal + "." + diff_after_decimal;
        }
        else
        {
            diff_after_decimal.erase(0, 1);
            ans = diff_before_decimal + "." + diff_after_decimal;
        }
    }
    
    // integer part is negative and decimal part is positive
    else if(int_pt_neg and !dec_pt_neg)
    {
        // the absolute value of integer part should minus one
        diff_before_decimal.erase(0, 1);
        diff_before_decimal = integer_subtraction(diff_before_decimal, "1");

        diff_after_decimal = integer_subtraction("10", diff_after_decimal);

        diff_before_decimal.insert(diff_before_decimal.begin(), '-');
        ans = diff_before_decimal + "." + diff_after_decimal;
    }
    return ans;
}

// the return value of this function is the difference of fir and sec
// remember that fir and sec are both positive
string subtraction::decimal_subtraction(string fir, string sec)
{
    string ans{};
    
    size_t fir_length = fir.length();
    size_t sec_length = sec.length();
    if(fir_length == sec_length)
    {
        ans = integer_subtraction(fir, sec);
        return ans;
    }

    int flag = calculator::which_dec_is_bigger(fir, sec);
    // among this case, the length of fir and sec must be different
    if(flag == 0)
        ans = "0";

    else if(flag > 0)
       ans = bigger_dec_minus_sml_dec(fir, sec); 

    else if(flag < 0)
    {
        ans = bigger_dec_minus_sml_dec(sec, fir);
        ans.insert(ans.begin(), '-');    
    }
}

// this function handles a bigger decimal fir minus smaller decimal sec
// and the number of digits of fir is bigger too
// make sure the parameters passed in  always satisfy fir > sec 
string subtraction::bigger_dec_minus_sml_dec(string fir, string sec)
{
    string ans{};

    size_t fir_length = fir.length();
    size_t sec_length = sec.length();

    if(fir_length > sec_length)
        sec.append('0', fir_length - sec_length);
    else
        fir.append('0', sec_length - fir_length);

    ans = integer_subtraction(fir, sec);
    return ans;
}



