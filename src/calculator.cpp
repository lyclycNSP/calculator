#include "../lib/calculator.h"
#include "../lib/addition.h"

// get arithmetic number from user
string calculator::get_num()
{
    cout << endl;
    string num;
    cout << "Warning: invalid input will be identified as zero" << endl;
    cout << "Enter a number: " << endl;
    getline(cin,num);
    if(num.length() == 0 or (num.length() == 1 and !isdigit(num[0])))
        return "0";
    else
        return num;
}

// get arithmetic symbol from user
string calculator::get_symbol()
{
    cout << endl;
    cout << "Valid symbols includes '+' '-" << endl;
    cout << "Enter a symbol: " << endl;
    string symbol;
    // while(1)
    // {
    //     cin >> symbol;
    //     if(symbol != '+' or symbol != '-')
    //     {
    //         cout << "Please enter a valid symbol" << endl;
    //         cin.clear();
    //         cin.ignore(1, EOF);
    //     }
    //     else
    //         break;
    // }
    // cin.ignore(1, EOF);
    getline(cin, symbol);
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

// delete the leading zero of the correct result
void calculator::delete_leading_zero(string& ans)
{
    size_t length = ans.length();
    if(length == 1) // if there is only a zero, don't delete it
        return;
    for(size_t i = 0; i < length; i++)
    {
        if(ans[i] != '0')
            break;
        else
        {
            ans.erase(i,1);
            i--;
        }
    }
    return;
}

// judge if two integer's addition produce a carry
bool calculator::if_carry(string fir, string sec)
{
    size_t maxlength = fir.length() > sec.length() ? fir.length() : sec.length();

    string ans = addition::decimal_addition(fir, sec);
    if(ans.length() > maxlength)
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
        splited_num.second = "0";
        return splited_num;
    }
    auto decimal_pos = num.find('.');
    splited_num.first = num.substr(0,decimal_pos);
    splited_num.second = num.substr(decimal_pos + 1);
    
    return splited_num;
}

// judge if a number is negative
bool calculator::is_neg(string num)
{
    if(num[0] == '-')
        return true;
    else
        return false;
}

// remove the leading '-' of the number string
void calculator::to_absolute(string& fir)
{
    if(fir[0] == '-')
        fir.erase(0, 1);
    return;
}

// return 1 for fir > sec
// return -1 for fir < sec
// return 0 for fir = sec
int calculator::which_is_bigger(string fir, string sec)
{
    size_t fir_length = fir.length();
    size_t sec_length = sec.length();

    if(fir_length > sec_length)
        return 1;
    else if(fir_length < sec_length)
        return -1;
    else
    {
        for(size_t i{}; i < fir_length; i++)
        {
            if(fir[i] > sec[i])
                return 1;
            else if(fir[i] < sec[i])
                return -1;
        }
        return 0;
    }
}

// this function judge which decimal part is bigger
// return 1 for fir > sec
// return -1 for fir < sec
// return 0 for fir = sec
int calculator::which_dec_is_bigger(string fir, string sec)
{
    size_t fir_length = fir.length();
    size_t sec_length = sec.length();

    string longstr = fir_length > sec_length ? fir : sec;
    string shortstr = fir_length < sec_length ? fir : sec;
    size_t maxlength = longstr.length();
    size_t minlength = shortstr.length();

    size_t i{};
    for(; i < minlength; i++)
    {
        if(fir[i] > sec[i])
            return 1;
        else if(fir[i] < sec[i])
            return -1;
    }
    while(i < maxlength)
    {
        if(longstr[i] != '0')
        {
            if(longstr == fir)
                return 1;
            else 
                return -1;
        }
    }
    return 0;
}

// this function gets the significant digits of a decimal part
// return 1 for all zero or only one siginificant digit
size_t calculator::get_significant_digits_of_dec(string num)
{
    size_t length = num.length();
    if(length == 1)
        return 1;

    int index = static_cast<int>(length) - 1;
    for(; index >= 0; index--)
    {
        if(num[index] != 0)
            break;
    }
    if(index == -1)
        return 1;
    else
        return index + 1;
}
