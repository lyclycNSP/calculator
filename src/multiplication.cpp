#include "../lib/multiplication.h"
#include "../lib/calculator.h"

/*
* this function handles two positive integers's multiplication
* the positiveness is guarantee by the calculation()'s preprosession
*/
string multiplication::integer_multiplication(string fir, string sec)
{
    string ans{};
    if(calculator::is_zero(fir) or calculator::is_zero(sec))
        return "0";

    string longnum = fir.length() >= sec.length() ? fir : sec;
    string shortnum = fir.length() < sec.length() ? fir : sec;

    reverse(longnum.begin(), longnum.end());
    reverse(shortnum.begin(), shortnum.end());


    ans = reverse_multiplication(longnum, shortnum);
    return ans;
}

// this function handles two reversed integer's multiplication
string multiplication::reverse_multiplication(string longnum, string shortnum)
{
    string ans{};

    char result{}; 
    char carry{};
    size_t cur_pos{};
    char product{};
    size_t end_zero_count{};

   /*
    * end_zero_count is the sum of the zero at the end of this two numbers
    * this zero will be appended to the answer
    * attention here, the string that is passed in was reversed
    */
    end_zero_count += calculator::count_the_zero_at_the_end(longnum);
    end_zero_count += calculator::count_the_zero_at_the_end(shortnum);

    // remove the zeros at the end to simplify multiplication
    calculator::remove_end_zeros(longnum);
    calculator::remove_end_zeros(shortnum);

    size_t shortlen = shortnum.length();    
    size_t longlen = longnum.length();
    for(size_t i{}; i < shortlen; i++)
    {
        cur_pos = i;
        for(size_t j{}; j < longlen; j++)
        {
            // ture if the ans is empty or current position doesn't exist
            if(ans.length() == 0 or (ans.length() != 0 and cur_pos > ans.length() - 1))
            {
                product = static_cast<char>((shortnum[i] - '0') * (longnum[j] - '0') + carry);
                result = product % 10;
                carry = product / 10;
                ans.append(to_string(result));
            }
            
            // the current pos exist
            else
            {  
                product = static_cast<char>((shortnum[i] - '0') * (longnum[j] - '0') + carry);
                product += static_cast<char>(ans[cur_pos] - '0');
                result = product % 10;
                carry = product / 10;
                ans[cur_pos] = result + '0';
            }
            cur_pos++;
        }
        ans.append(to_string(carry));
        carry = 0;
    }
    reverse(ans.begin(), ans.end());
    calculator::delete_leading_zero(ans);

    ans.append(end_zero_count, '0');
    return ans;
}

string multiplication::floating_point_multiplication(string fir, string sec)
{
    string ans{};
    size_t dec_offset{};

    auto splited_fir = calculator::split_flot(fir);
    auto splited_sec = calculator::split_flot(sec);
    
    // count the sum of digits after the decimal point of the two number
    if(!calculator::is_zero(splited_fir.second))
        dec_offset += splited_fir.second.length();
    if(!calculator::is_zero(splited_sec.second))
        dec_offset += splited_sec.second.length();

    // set two numbers to integer to simplify calculation
    string new_fir{};
    string new_sec{};
    if(calculator::is_zero(splited_fir.second))
        new_fir = splited_fir.first;
    else
    {
        size_t fir_dec_pos = fir.find('.');
        fir.erase(fir_dec_pos, 1);
        new_fir = fir;
    }
    if(calculator::is_zero(splited_sec.second))
        new_sec = splited_sec.first;
    else
    {
        size_t sec_dec_pos = sec.find('.');
        sec.erase(sec_dec_pos, 1);
        new_sec = sec;
    }

    ans = integer_multiplication(new_fir, new_sec);

    // moving the decimal point of the answer
    size_t ans_length = ans.length();
    if(ans_length > dec_offset)
        ans.insert(ans.begin() + (ans_length - dec_offset), '.');
    
    else
    {
        for(size_t i{}; i < (dec_offset - ans_length + 1); i++)
            ans.insert(ans.begin(), '0');
        ans.insert(ans.begin() + 1, '.');
    }   

    return ans;
}