/***********************************************************************
* Program:
*    Week 05, Memory Injection
*    Brother Helfrich, CS470
* Author:
*    your name
* Summary: 
*    This program is designed to illustrate weaknesses in the stack.
*
************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;


void partOne();    // Find the qaddress of the stack, heap, and code segments
void partTwo();    // Manipulate the stack to find a weakness
void partThree();  // Demonstrate a variety of vulnerabilities

/******************************************************
 * MAIN
 * This function will only take you to one of the three parts
 * of Assignment 10
 *****************************************************/
int main()
{
   // prompt
   cout << "Please select an option:\n";
   cout << "  1.  Find the address\n";
   cout << "  2.  Manipulate the stack\n";
   cout << "  3.  Demonstrate vulnerabilities\n";
   cout << "> ";
   int selection;
   cin >> selection;

   // highly complex menu system
   switch (selection)
   {
      case 1:
         partOne();
         break;
      case 2:
         partTwo();
         break;
      case 3:
         partThree();
         break;
      default:
         cout << "Unknown option\n";
         return 1;
   }

   return 0;
}

/**************************************************************
 **************************************************************
 **************************** PART 1 **************************
 **************************************************************
 **************************************************************/

/**********************************************
 * Part 1
 *
 * Find the address of the stack, heap, and code.
 * Note that it will be in a different location with
 * every execution
 **********************************************/
void partOne()
{

	int *ptr = new int;
	void* p = NULL;
	/*printf("%p", (void*)&p);*/

	//cout << "Stack: ";
	//sprintf("Stack: ", "%p", (void*)&p);
	for (int i = -10;  i < 10;  i++)
	{
		cout << i << "Heap: " << *ptr + i << endl;
	}

	cout << "Heap: " << &ptr +20 << endl;
	cout << "Code: " << ptr << endl;
   return;
}


/**************************************************************
 **************************************************************
 **************************** PART 2 **************************
 **************************************************************
 **************************************************************/

void fail(char grade);
void pass(char grade);


/**********************************************************************
 * All your code needs to exist in this function below the comment
 *********************************************************************/
void readStack()
{
   int   number = 0;
   char  text[16];
   
   ////////////////////////////////////////////////
   // put your magic code between here...


   // ... and here
   ////////////////////////////////////////////////

   // output the goods
   cout << "\tnumber: "
        << number
        << endl;
   cout << "\ttext:   "
        << text
        << endl;

   return;
}

/*******************************************************************
 * Part 2
 *
 * This function contains the data that you are trying to manipulate.
 * Please don't modify partTwo() in any way
 ********************************************************************/
void partTwo()
{
   int   number;   // first local variable that you need to read
   char  text[16]; // second

   char  letterGrade;
   void (*pointerFunction)(char);

   // compilers are annoying.
   // If we don't get the address of these two variables, our
   // compiler will optimize them away and they will not appear
   // on the stack.  To get around this, I use the address-of
   // operator which forces the compiler to put them in the stack.
   &letterGrade;
   &pointerFunction;

   // get the values
   cout << "number: ";
   cin  >> number;
   cout << "text:   ";
   cin  >> text;


   // Call the function and display the results.
   pointerFunction = fail;
   letterGrade = 'B';
   readStack();            // vulnerability is here 
   (*pointerFunction)(letterGrade);

   return;
}


/**********************************************************************
 * The failure case. Don't touch this function
 *********************************************************************/
void fail(char grade)
{
   cout << "\tI am sorry, but you got a 'C'\n";
}

/**********************************************************************
 * I think you would really rather call this function.  This
 * is read-only also
 *********************************************************************/
void pass(char grade)
{
   cout << "\tGood job, you got a(n) '" << grade << "'\n";
}


/**************************************************************
 **************************************************************
 **************************** PART 3 **************************
 **************************************************************
 **************************************************************/

/****************************************
 * Pointer Subterfuge Vulnerability --- EXAMPLE CODE
 * 1. There must be a pointer used in the code.
 * 2. There must be a way to overwrite the pointer
 * 3. After the pointer is overwritten, the pointer is dereferenced
 ****************************************/
void subterfugeVulnerability(long * array, int size)
{
   long int buffer[2];
   const char * message = "Safe";  // 1. Pointer

   for (int i = 0; i < size; i++)  // 2. Overwrite
      buffer[i] = array[i];

   cout << "Message is: \""
        << message                 // 3. Dereference
        << "\".\n";
}

/****************************************
 * Pointer Subterfuge Exploitation -- EXAMPLE CODE
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 *    referring to data altering the normal flow of the program
 ****************************************/
void subterfugeExploit()
{
   // an attacker's array
   long int array[3] =             // 1. Exploit
   {
      1,
      1,
      (long int)"Dangerous"        // 2. Provide pointer
   };

   // exploit it
   subterfugeVulnerability(array, 3);
}



/*************************************
 * Part 3
 *
 * partThree() will call four functions to
 * demonstrate Stack, Heap, ArrayIndex, and Arc
 * vulnerabilities.  You should
 *   * Write the functions with code defects
 *     that represent the various vulnerabilities
 *   * Create input that will cause the vulnerabilities
 *     to be exploited
 *   * Create a simple menu system similar to main()
 *     so the user can witness the vulnerability
 *     of his choice
 *************************************/
void partThree()
{ 
   cout << "  1. Stack smashing\n"
        << "  2. Heap spraying\n"
        << "  3. Array index\n"
        << "  4. Arc vulnerability\n"
        << "  4. Pointer Subterfuge\n"
        << "> ";

   int select;
   cin >> select;

   switch (select)
   {
      case 1:
//         stackExploit();
         break;
      case 2:
//         heapExploit();
         break;
      case 3:
//         arrayExploit();
         break;
      case 4:
//         arcExploit();
         break;
      case 5:
         subterfugeExploit(); // example code
      default:
         cout << "Unknown option " << select << endl;
   }
   return;
}
