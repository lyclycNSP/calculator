#include "lib/calculator.h"
#include "lib/subtraction.h"

// make sure larger one minus smaller one
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

string reverse_subtraction(string fir, string sec)
{

}




