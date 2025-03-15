#include "../lib/calculator.h"
#include "../lib/division.h"
#include "../lib/multiplication.h"
#include "../lib/subtraction.h"
#include "../lib/addition.h"

// this function calculate the quotient of two integers
string division::integer_division(string fir, string sec, long long prec)
{
    
    // handles special cases
    if(calculator::is_zero(sec))
    {
        cout << "You can't divide a number by 0" << endl;
        return "N/A";
    }
    if(calculator::is_zero(fir))
        return "0";

    if (sec == "1")
        return fir;

    // setting the default precision
    if(prec == -1)
        prec = 20;
    size_t after_dec_digits{};
        
    string ans{};
    string remainder{};
    size_t cur_pos{};
    bool is_added_dec_point{false};
    string divident{};
    string quotient{};
    long long dec_offset{};

    // remove the zero at the end to simplify calculation
    reverse(fir.begin(), fir.end());
    reverse(sec.begin(), sec.end());
    dec_offset += calculator::count_the_zero_at_the_end(fir);
    dec_offset -= calculator::count_the_zero_at_the_end(sec);
    calculator::delete_leading_zero(fir);
    calculator::delete_leading_zero(sec);
    reverse(fir.begin(), fir.end());
    reverse(sec.begin(), sec.end());


    // the main loop for division, one bit of digit per loop
    // calculate one more bit to round
    while(after_dec_digits < static_cast<size_t>(prec + 1))
    {
        divident = decide_divident(fir, sec, cur_pos, remainder);

        quotient = divide(divident, sec, remainder);

        if(remainder == "" and cur_pos != fir.length())
        {
            ans.append(quotient);
            ans.append(fir.length() - cur_pos, '0');
            break;
        }
        else if(remainder == "" and cur_pos == fir.length())
        {
            ans.append(quotient);
            break;
        }
        else
        {
            // if there is a decimal point added, count the digits after decimal point
            if(is_added_dec_point)
                after_dec_digits++;
            ans.append(quotient);
        }

        if(!is_added_dec_point and cur_pos == fir.length())
        {
            ans.append(".");
            is_added_dec_point = true;
        }
    }

    if(!calculator::is_a_floating_point(ans))
        ans = ans + ".0";
    auto[int_pt, dec_pt] = calculator::split_flot(ans);
    calculator::delete_leading_zero(int_pt);
    if(int_pt == "")
        int_pt = "0";
    ans = int_pt + "." + dec_pt;
    
    ans = calculator::move_dec_point(ans, dec_offset);
    return ans;
}

// this function calculates the quocient of two floating points
string division::floating_point_division(string fir, string sec, long long prec)
{
    string ans{};

    auto[fir_int_pt, fir_dec_pt] = calculator::split_flot(fir);
    auto[sec_int_pt, sec_dec_pt] = calculator::split_flot(sec);

    long long dec_offset{};
    
    reverse(fir_dec_pt.begin(), fir_dec_pt.end());
    reverse(sec_dec_pt.begin(), sec_dec_pt.end());
    calculator::delete_leading_zero(fir_dec_pt);
    calculator::delete_leading_zero(sec_dec_pt);
    reverse(fir_dec_pt.begin(), fir_dec_pt.end());
    reverse(sec_dec_pt.begin(), sec_dec_pt.end());

    if(!calculator::is_zero(fir_dec_pt))
    {
        dec_offset -= fir_dec_pt.length();
        if(!calculator::is_zero(fir_int_pt))
            fir = fir_int_pt + fir_dec_pt;
        else
            fir = fir_dec_pt;
    }
    else
        fir = fir_int_pt;
    if(!calculator::is_zero(sec_dec_pt))
    {
        dec_offset += sec_dec_pt.length();
        if(!calculator::is_zero(sec_int_pt))
            sec = sec_int_pt + sec_dec_pt;
        else
            sec = sec_dec_pt;
    }
    else 
        sec = sec_int_pt;

    ans = integer_division(fir, sec, prec);
    ans = calculator::move_dec_point(ans, dec_offset);

    return ans;
}

// this function decide the divident for each division
string division::decide_divident(string fir, string sec, size_t& cur_pos, string& remainder)
{
    string divident{};
    size_t fir_len = fir.length();

    if(cur_pos < fir_len)
    {
        divident = remainder + fir.substr(cur_pos, 1);
        cur_pos++;
    }   

    else
        divident = remainder + "0";
    
    return divident;
}

// this function calculate the quotient of each division
string division::divide(string divident, string sec, string& remainder)
{
    // divident is less than sec
    if(calculator::which_is_bigger(divident, sec) < 0)
    {
        remainder = divident;
        return "0";
    }

    size_t coeff{2};
    string product{};
    // maintain a copy of the previou product
    string prev_product{sec};
    // divident must be greater than sec
    for(; coeff <= 10; coeff++)
    {
        product = multiplication::integer_multiplication(sec, to_string(coeff));
        if(calculator::which_is_bigger(divident, product) == 0)
        {
            remainder = "";
            return to_string(coeff);
        }

        else if(calculator::which_is_bigger(divident, product) < 0)
        {
            remainder = subtraction::integer_subtraction(divident, prev_product);
            if(remainder == "0")
                remainder = "";
            calculator::delete_leading_zero(remainder);
            return to_string(coeff - 1);
        }
        prev_product = product;
    }
    return "something went wrong";
}