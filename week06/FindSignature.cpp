/***********************************************************************
* Program:
*    Week 06, Find Signature
*    Brother Helfrich, CS470
* Author:
*    Br. Helfrich
* Summary: 
*    This program opens a file and looks for a special key word
*    which will indicate whether it was written by a certain author.
*    The key word is ciphered using the Caesar Cipher
************************************************************************/

#include <iostream>  // to display the message on the screen
#include <fstream>   // to read the file
#include <string>    // a convenient way to read a word from the file
using namespace std; // for convenience

/****************************************************************
 * GET SECRET WORD
 * Return the secret word
 ***************************************************************/
string getSecretWord(int key)
{
   // appears random and unimportant if the binary is searched
   string word = "S#4T!";

   // translate
   for (string::iterator it = word.begin(); it != word.end(); ++it)
      *it += key;

   return word;   
}

/****************************************************************
 * IS AUTHENTIC
 * This function will return TRUE if the file contains the secret
 * keyword and is thus authentic, and will return FALSE otherwise
 ****************************************************************/
bool isAuthentic(const char * fileName)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return false;

   // read the file, one word at a time. Stop if found
   string wordRead;
   string wordCheck = getSecretWord(15);
   bool found = false;
   while (!found && fin >> wordRead)
      found = (wordRead == wordCheck);

   // return and report
   fin.close();
   return found;
}

/******************************************************************
 * MAIN
 * The elaborate UI
 ******************************************************************/
int main(int argc, char ** argv)
{
   // parse the commandline
   if (argc != 1)
   {
      cerr << "Usage:\n\t" << argv[0] << " fileName\n";
      return 1;
   }

   // display the message
   cout << "The file " << argv[1]
        << (isAuthentic(argv[1]) ? "is" : "is not")
        << " authentic\n";
   return 0;
}
