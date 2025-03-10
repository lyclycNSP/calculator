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
    cout << "a simple calculator" << endl;
    cout << "enter 'q' to quit" << endl;
    cout << "enter other characters to continue" << endl;
    cout << "WARNING: you could enter ONLY ONE CHARACTER or unexpected error will occur" << endl;
    
    int flag{};
    flag = cin.get();
    // flush the enter in buffer

    cin.ignore();
    while(flag != 'q')
    {
        // get the first number
        string first_num = get_num();

        // get the operation symbol;
        string symbol = get_symbol();

        // get the second number
        string second_num = get_num();

        // check if the numbers are negative
        cout << endl;
        string ans;

        //classify addition and subtraction into a few categories
        ans = calculation(first_num, second_num, symbol);

        cout << "The result is " << ans << endl;
        cout << endl;

        cout << "a simple calculator, enter q to quit, enter any other to continue" << endl;
        flag = cin.get();
        cin.ignore();
    }
}
