/***********************************************************************
* Program:
*    Week 09, Password Strength
*    Brother Wilson, CS470
* Author:
*    Edgar Wright
* Summary: 
*    Please include a detailed description of:
*    1. This program will take a password and return the number of combinations
*       followed by the bit equivliancy  
*    2. This program will check for the char types and return the right number.
*    3. This program assumes the input is less than 256 char
*    4. Algorithm was borrowed from Security for Software Engineers
************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

int parser(string password);
long int passwordComb(string password);
long int passwordBits(string password);

int main()
{

    string password;

    cout << "Please enter the password: ";
    cin >> password;

    cout << "There are " << passwordComb(password) << " combinations\n";
    cout << "That is equivalent to a key of " << passwordBits(password) << " bits\n";
return 0;
}

long int passwordComb(string password)
{
   long int numCombinations;
    //Length of alphabet
    int n;
    //Length of passwrod
    int m;
    m = password.length();
    n = parser(password);
   numCombinations = pow(n,m);
    return numCombinations;
}

long int passwordBits(string password)
{
    //Number of bits in a passsword
    long int bits;
    //Length of alphabet
    int n;
    //Length of passwrod
    int m;

    n = parser(password);
    m = password.length();
    bits = log2(pow(n, m));
    
    return bits;
}

int parser(string password)
{
    int libSize;
    bool notAlpha = false;
    bool upper = false;

    bool lower = false;
    bool digit = false;
    char c[1];

    for(int i = 0; i < password.length(); i++)
    {
        c[0] = password.at(i);
        if(!isalpha(c[0]) && !isdigit(c[0]) && !notAlpha)
        {
            libSize += 32;
            notAlpha = true;
        }
        else if(islower(c[0]) && !lower)
        {
            libSize += 26;
            lower = true;
        }
        else if(isupper(c[0]) && !upper)
        {
            libSize += 26;
            upper = true;
        }
        else if(isdigit(c[0]) && !digit)
        {
            libSize += 10;
            digit = true;
        }
    }

    return libSize;
}