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

string calculator::get_method()
{
    cout << endl;
    string method;
    cout << "Choose a method to display result" << endl;
    cout << "'e' for e_method, 'r' for ordinary_method" << endl;
    getline(cin, method);
    return method;
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
    size_t i = 0;

    if(length == 1) // if there is only a zero, don't delete it
        return;
    else if(ans[0] == '-')
        i = 1;
        
    for(; i < length; i++)
    {
        if(ans[i] == '-')
            continue;
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
        i++;
    }
    return 0;
}

// this function gets the significant digits of a decimal part
// in order to apply decimal part addition
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

//this function calculate how many numbers digits of the decimal places offset in string
// return a negative number indicates the decimal places offset to left
// return a positive number indicates the decimal places offset to right
// return zero when it doesn't offset
// the absolute value of the return value is the offset digits
size_t calculator::numbers_of_dec_offset(string num)
{
    size_t offset{};

    // integers
    if(!is_a_floating_point(num))
        offset = count_digits(num) - 1;

    // floating points
    else
    {
        to_absolute(num);

        auto splited_num = split_flot(num);

        // deciding offset_num based on the integer part
        size_t integer_digits = count_digits(splited_num.first);

        if(integer_digits != 1)
            offset = integer_digits - 1;
            
        else
        {
            if(splited_num.first[0] == '0')
                offset = -1;
            
            else
                offset = 0;
        }
    }

    return offset;
}

// this function count a number's digits excluding sign and decimal point
size_t calculator::count_digits(string num)
{
    to_absolute(num);

    size_t digits = num.length();
    
    if(is_a_floating_point(num))
        digits--;
    
    return digits;
}

// this function format the answer based on the parameter
string calculator::formatted_output(string ans, char method)
{
    if(ans == "0.0" or ans == "0")
        return "0";

    
    string modified_ans{ans};
    switch(method)
    {
        case 'r':
            return modified_ans;

        case 'e':
        {
            size_t offset = numbers_of_dec_offset(ans);
            
            modified_ans = e_method(ans, offset);
            return modified_ans;
        }

        default:return modified_ans;
    }
}

// this function format a number into e_method
string calculator::e_method(string ans, size_t offset)
{
    string e_suffix = "E" + to_string(offset);
    if(offset == 0)
    {
        ans.append(e_suffix);
        return ans;
    }

    if(!is_a_floating_point(ans))
    {
        // positive
        if(!is_neg(ans))
            ans.insert(ans.begin() + 1, '.');
            
        else
            ans.insert(ans.begin() + 2, '.');
            
    }

    else
    {
        //negative
        if(is_neg(ans))
        {
            if(offset < 0)
            {
                // remove the zero in integer part and decimal point
                ans.erase(1, 2);

                if(ans.length() != 2)
                    ans.insert(ans.begin() + 2, '.');
            }
            
            else if(offset > 0)
            {
                auto dec_point_pos = ans.find('.');
                ans.erase(dec_point_pos, 1);
                ans.insert(ans.begin() + 2, '.');
            }
        }

        // positive
        else
        {
            if(offset < 0)
            {
                ans.erase(0, 2);

                if(ans.length() != 1)
                    ans.insert(ans.begin() + 1, '.');
            }

            else if(offset > 0)
            {
                auto dec_point_pos = ans.find('.');
                ans.erase(dec_point_pos, 1);
                ans.insert(ans.begin() + 1, '.');
            }
        }
    }
    ans.append(e_suffix);

    return ans;
}

