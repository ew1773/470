/***********************************************************************
* Program:
*    Week 06, Data Flow Diagram
* Author:
*    Br. Helfrich
* Summary: 
*    This program will prompt the user for a secret (text) and
*    a password.  The program will then prompt the user for the
*    password.  IF the password is correct, the secret will be revealed.
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * MAIN
 * Just a very simple program
 ***********************************************************************/
int main()
{
   // get the secret
   string secret;
   cout << "What is the secret?   ";
   cin  >> secret;

   // get the password
   string password;
   cout << "What is the password? ";
   cin  >> password;

   // now go in a holding pattern until the user provides the correct password
   string prompt;
   do
   {
      cout << "You can get the secret only with the password: ";
      cin  >> prompt;
   }
   while (prompt != password);

   // reveal the secret
   cout << "The secret is " << secret << endl;      
   return 0;
}
