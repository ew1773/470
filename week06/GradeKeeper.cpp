/***********************************************************************
 * Program:
 *    Week 06, Data Flow Diagram
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will keep track of a student's grades in a given class
 *    The data will be stored in a file so potentially the grades for many
 *    classes can be tracked at the same time.
 ************************************************************************/

#include <iostream>    // for CIN and COUT
#include <fstream>     // for IFSTREAM and OFSTREAM
#include <cassert>     // because I am paranoid
#include <iomanip>     // for SETW
using namespace std;

// maximum number of grades
#define MAX 100

// prototypes
char getOption        ();
void getName          (char *fileName);
int  readFile         (char *fileName,
                       char descriptions[][256],   int points[], int scores[]);
bool writeFile        (char *fileName,             int num,
                       char descriptions[][256],   int points[], int scores[]);
int  newFile          (char descriptions[][256],   int points[], int scores[]);
void interact         (char descriptions[][256],   int points[], int scores[],
                       int num);
void display          (char descriptions[][256],   int points[],
                       int scores[],               int num);
bool changeDescription(char descriptions[][256],   int num);
bool changePoints     (int points[],               int num);
bool changeScore      (int scores[],               int num);
bool clearScore       (int scores[],               int num);
int  getIndex         (int num);
int  computeAverage   (int points[], int scores[], int num);
char computeLetter    (int average);
char computeSign      (int average);

/**********************************************************************
 * MAIN
 * create/open the file, let the user interact with the data, then write
 * the results when finished.
 ***********************************************************************/
int main()
{
   // get the filename
   char fileName[256];
   getName(fileName);

   // read the file
   int  points[MAX];
   int  score[MAX];
   char description[MAX][256];
   int  num = readFile(fileName, description, points, score);
   if (0 == num)
      num = newFile(description, points, score);

   // allow the user to interact with the grades data
   interact(description, points, score, num);

   // write the new data to the disk
   if (!writeFile(fileName, num, description, points, score))
      cout << "Error writing to file " << fileName << endl;

   return 0;
}

/******************************************************************
 * GET NAME
 * Prompt the user for the filename
 *****************************************************************/
void getName(char *fileName)
{
   assert(NULL != fileName);
   cout << "What is the filename of the grades file? ";
   cin  >> fileName;

   assert(*fileName != '\0');
   return;
}

/******************************************************************
 * READ FILE
 * Read the file as specified by the user.  The format is:
 *    <numItems>
 *    <name1> <points1> <score1>
 *    <name2> <points2> <score2>
 *******************************************************************/
int readFile( char *fileName,
              char descriptions[][256], int points[], int scores[])
{
   // open the file
   int num = 0;
   assert(fileName && *fileName);
   ifstream fin(fileName);
   if (fin.fail())
      return 0;

   // read the number of records
   fin >> num;
   assert(num > 0 && num < MAX);
   if (fin.fail())
      return 0;

   // read each record
   int i;
   for (i = 0; i < num && !fin.eof(); i++)
      fin >> descriptions[i] >> points[i] >> scores[i];

   // bail if there are not the expected number of items in the file.
   if (i != num)
      return 0;

   // close the file
   fin.close();
   return num;
}

/***********************************************************
 * WRITE FILE
 * Write the data to the file in the same format as readFile:
 *    <numItems>
 *    <name1> <points1> <score1>
 *    <name2> <points2> <score2>
 **********************************************************/
bool writeFile(char *fileName, int num,
               char descriptions[][256], int points[], int scores[])
{
   assert(fileName && *fileName);
   assert(num > 0 && num < MAX);

   // open the file for writing
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   // write the number of records
   fout << num << endl;

   // write each record out in the file
   for (int i = 0; i < num; i++)
      fout << setw(10)
           << descriptions[i] << " \t"
           << points[i]       << " \t"
           << scores[i]       << endl;

   // close the file
   fout.close();

   cout << "File saves successfully\n";
   return true;
}

/***************************************************************
 * NEW FILE
 * create a new score file from scratch
 ***************************************************************/
int  newFile(  char descriptions[][256], int points[], int scores[])
{
   // prompt for number of scores
   int num;
      do
      {
         cout << "How many records are in the file? ";
         cin  >> num;
      }
      while (num <= 0 || num >= MAX);
      assert(num > 0 && num < MAX);

      // loop through all the records
      for (int i = 0; i < num; i++)
      {
         cout << "Description for #" << i + 1 << ": ";
         cin  >> descriptions[i];
         points[i] = 100;
         scores[i] = -1;
      }

      // return the number saved
      return num;
}

/*********************************************************************
 * GET OPTION
 * Give the user a menu of options and prompt him for his selection.
 * Make sure the results is lowercase
 ********************************************************************/
char getOption()
{
   // display all the options
   cout << "Options:\n";
   cout << "\t(n) : Change the name of an item\n";
   cout << "\t(p) : Change the number of points an item is worth\n";
   cout << "\t(s) : Change the earned score on an item\n";
   cout << "\t(c) : Clear the score on an item\n";
   cout << "\t(d) : Display the grade list again\n";
   cout << "\t(q) : Quit\n";

   // prompt for option
   char option;
   cout << "> ";
   cin  >> option;

   return tolower(option);
}

/*******************************************************************
 * INTERACT
 * User Interface.  Display the options and prompt the user for his
 * choice.  Based on his choice, select one of many operations.  Keep
 * going until the use selects 'quit'
 ******************************************************************/
void interact( char descriptions[][256], int points[],
               int scores[], int num)
{
   // display the scores the first time
   display(descriptions, points, scores, num);

   // continue looping until the user indicates he is finished
   bool done = false;
   while (!done)
   {
      bool success = true;   // default success.  We are optimistic
      switch (getOption())
      {
         case 'n':
            success = changeDescription(descriptions, num);
            break;
         case 'p':
            success = changePoints(points, num);
            break;
         case 's':
            success = changeScore(scores, num);
            break;
         case 'c':
            success = clearScore(scores, num);
            break;
         case 'd':
            display(descriptions, points, scores, num);
            break;
         case 'q':
            done = true;    // time to quit
            break;
         default:
            success = false;   // unknown command
      }

      // if an error occured, inform the user
      if (!success)
         cout << "Error processing that command\n";
   }

   return;
}

/***********************************************************
 * CHANGE DESCRIPTION
 * Change the description on a grade item
 **********************************************************/
bool changeDescription(char descriptions[][256], int num)
{
   // get the index
   int i = getIndex(num);
   if (i == -1)
      return false;

   //   get the data
   cout << "What is the new name: ";
   cin  >> descriptions[i];

   return true;
}


/***********************************************************
 * CHANGE POINTS
 * Change the points on a grade item
 **********************************************************/
bool changePoints(int points[], int num)
{
   // get the index
   int i = getIndex(num);
   if (i == -1)
      return false;

   // get the data
   int tmp;
   cout << "What is the new points: ";
   cin  >> tmp;

   // validate the score
   if (tmp >= 0)
   {
      points[i] = tmp;
      return true;
   }
   return false;
}

/***********************************************************
 * CHANGE SCORE
 * Change the score on a grade item
 *********************************************************/
bool changeScore(int scores[], int num)
{
   // get the index
   int i = getIndex(num);
   if (i == -1)
      return false;

   // get the data
   int tmp;
   cout << "What is the new score: ";
   cin  >> tmp;

   // validate the score
   if (tmp >= 0 && tmp <= 100)
   {
      scores[i] = tmp;
      return true;
   }
   return false;
}

/********************************************************
 * CLEAR SCORE
 * Remove the score earned for a given record.  Set it to -1
 *******************************************************/
bool clearScore(int scores[], int num)
{
   int i = getIndex(num);
   if (i == -1)
      return false;

   scores[i] = -1;
   return true;
}


/****************************************************************
 * GET INDEX
 * Prompt the user for an index and validate it
 ****************************************************************/
int getIndex(int num)
{
   // get the index
   int index;
   cout << "Which item do you want to edit? ";
   cin  >> index;

   // convert to 0 base
   index--;

   // validate
   return (index < 0 || index >= num) ? -1 : index;
}

/*********************************************************************
 * DISPLAY
 * Display the list of records to the user
 *******************************************************************/
void display(char descriptions[][256], int points[], int scores[], int num)
{
   assert(num > 0 && num < MAX);

   // instructions
   cout << "Your grades are:\n";

   // header
   cout << "\tNumber            Name Points Score\n";
   cout << "\t====== =============== ====== =====\n";

   // loop through all the recoreds
   for (int i = 0; i < num; i++)
   {
      cout << "\t"
           << setw(6)  << i + 1
           << setw(16) << descriptions[i]
           << setw(7)  << points[i];
      if (scores[i] != -1)
         cout << setw(5) << scores[i]
              << "%\n";
      else
         cout << "    --\n";
   }

   // trailing row
   int average = computeAverage(points, scores, num);
   cout << "\t====== =============== ====== =====\n";
   cout << "\t       Total                   ";

   // grade
   if (average != -1)
   {
      char letter = computeLetter(average);
      char sign   = computeSign(  average);

      cout << setw(3) << average << "% "
           << letter;
      if (sign != '*')
         cout << sign;
      cout << endl;
   }
   else
      cout << "  --\n";
}

/*****************************************************************
 * COMPUTE AVERAGE
 * Compute the average taking -1s into account
 *****************************************************************/
int computeAverage(int points[], int scores[], int num)
{
   int sum = 0;
   int total = 0;

   assert(num > 0 && num < MAX);

   // loop through all the tiems
   for (int i = 0; i < num; i++)
      if (scores[i] != -1)
      {
         assert(points[i] >= 0);
         assert(scores[i] >= 0 && scores[i] <= 100);

         sum   += points[i] * scores[i];
         total += points[i];
      }

   // make the final computation
   return (total == 0) ? -1 : sum / total;
}

/********************************************************************
 * COMPUTE LETTER
 * Determine the letter grade from the number grade
 *******************************************************************/
char computeLetter(int average)
{
   //                0%  10%  20%  30%  40%  50%  60%  70%  80%  90% 100%
   char grades[] = {'F', 'F', 'F', 'F', 'F', 'F', 'D', 'C', 'B', 'A', 'A'};

   assert(average >= 0 && average <= 100);

   return grades[average / 10];
}

/********************************************************************
 * COMPUTE SIGN
 * Determine the sign associated with a grade
 *******************************************************************/
char computeSign(int average)
{
   //             ?0%  ?1%  ?2%  ?3%  ?4%  ?5%  ?6%  ?7%  ?8%  ?9%
   char sign[] = {'-', '-', '-', '*', '*', '*', '*', '+', '+', '+'};
   assert(average >= 0 && average <= 100);

   return (average >= 60 && average <= 93) ? sign[average % 10] : '*';
}

