#include "../lib/multiplication.h"
#include "../lib/calculator.h"

// this function handles two positive integers's multiplication
// the positiveness is guarantee by the calculation func's preprosession
// string multiplication::integer_multiplication(string fir, string sec)
// {
//     string ans{};
//     if(calculator::is_zero(fir) or calculator::is_zero(sec))
//         return "0";

//     string longnum = fir.length() >= sec.length() ? fir : sec;
//     string shortnum = fir.length() < sec.length() ? fir : sec;

//     reverse(longnum.begin(), longnum.end());
//     reverse(shortnum.begin(), shortnum.end());


//     ans = reverse_multiplication(longnum, shortnum);
//     return ans;
// }

// // this function handles two reversed integer's multiplication
// string multiplication::reverse_multiplication(string longnum, string shortnum)
// {
//     string ans{};
//     size_t shortlen = shortnum.length();    
//     size_t longlen = longnum.length();

//     int result{};
//     int carry{};

//     for(size_t i{}; i < shortlen; i++)
//     {
//         for(size_t j{}; j < longlen; j++)
//         {
//             int sum = (longnum[i] - '0') * (shortnum[j] - '0') + carry;
//             result = sum % 10;
//             carry = sum / 10;
//         }
//     }

//     // ...... unfinished
//     return ans;
// }