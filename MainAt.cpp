// Tommy Arnzen
// CIS 226
// Final Exam
// Due: Friday, December 13th, 2013 (11:00 PM)

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <Windows.h>
#include <mmstream.h>
#include <time.h>
#include "BinaryTree.h"	// Link to the binarytree class file.
#include "StudentAt.h"	// Link to the Student class file.
using namespace std;

// Foward Declaration of functions.
void pause(int);	// For audio read out of instructions to user.
void fifthSpaceTest(string); // For throw catch error checking.
void checkGPA(float); // For throw catch error checking.

// Main Function.
int main(){

	int werd;	// For display of the program.
	int numberOfLines = 0; // Counts the number of lines in the doc.
	string numLinesTest; // Stores the line values in a string for counting.
	string fileNameInput; // String to store the user input for file location.
	char answer;	// Test to determine if user needs audio assistance.

	// Calls out the title of the program to the user.
	cout << "\t\t\t***************************" << endl;
	cout << "\t\t\t C++ STUDENT SORT SOFTWARE" << endl;
	cout << "\t\t\t***************************" << endl;

	// Spacing.
	cout << endl << endl;

	// Prompts the user to enter in the location of the file they wish to
	// run the program on.
	// Also informs the user how they can find the path to the file if they
	// do not already know how to do so.
	cout << "Please enter the name of the file you wish to run the program on: " <<
		"\n(Do not add double slashes in the place of the left slash symbol): " <<
		"\n(Entries must be exact. For exact file locations on Windows OS" 
		"\nhold down 'shift' key and right click. Select 'copy as path')" << endl;

	// Prompt the user for a need for assistance in reading the instructions.
	cout << "\nDo you need audio assistance for the program directions? (Y/N): ";
	cin >> answer;

	// Error check to make sure that the user input is either 'Y' or 'N.'
	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n'){
		cout << "\nERROR -01: You have made an invalid selection." << endl;
		cout << "Please try again." << endl;
		cout << "\nDo you need audio assistance for the program directions? (Y/N): ";
		cin >> answer;
	}

	// If the user answers 'y' or 'Y' (in the affirmative) play the sound file.
	if (answer == 'y' || answer == 'Y'){
		// Method for playing audio found here:
		// http://stackoverflow.com/questions/1565439/how-to-playsound-in-c-using-windows-api
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\Aduio_Instructions.wav"), NULL, SND_ASYNC);
		int duration = 16000;	// Amount of time needed for audio directions to play to completion.
		pause(duration);	// Send the duration variable to the pause function.
	}
	

	// Prompts the user to enter the location of the file.
	cout << "Enter File Link(I.E. C:\\...\\...): ";
	cin.ignore();
	getline(cin, fileNameInput);
	
	// Declares a new input file stream. Opens an existing file (User specified) and 
	// and reads data from it.
	ifstream inputfile;
	inputfile.open(fileNameInput.c_str());

	// Error check to make sure that the file location entered is valid.
	// I.E. --> there is a file there.
	// Method for error checking a missing file found here:
	// http://stackoverflow.com/questions/890619/prompting-a-user-for-the-filename-or-directory
	while (!inputfile){
		cout << "\nERROR -02: You have entered an invalid file location." << endl;
		cout << "Please try again." << endl;
		inputfile.clear();
		cout << "\nPlease enter the name of the file you wish to run the program on: " <<
		"\n(Do not add '\\' in the place of the '\' symbol): ";
		getline(cin, fileNameInput);

		inputfile.open(fileNameInput.c_str());
	}

	// Spacing.
	cout << endl;

	// Declares a counter to count the number of lines inside the 
	// newely opened file.
	int counterOne = 0;

	// While loop that interates through the newely opened file,
	// and counts the number of lines inside the file.
	// Method for reading the number of lines in a file found at:
	// http://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
	while(getline(inputfile, numLinesTest)){
		++numberOfLines;	// Prefix counter.
		counterOne++;	// Postfi counter.
	}

	// Closes the file once all lines have been counter.
	inputfile.close();

	// Opens the same file again, but this time for the purpose of
	// storing the values inside of the binary tree class.
	ifstream inputfileTwo;

	// No need for error check in this case, since it has already been tested
	// on the first entry (SAME FILE).
	inputfileTwo.open(fileNameInput.c_str());

	// Informs the user that data is being read from the file into 
	// the program.
	cout << "Reading data from file..." << endl << endl;

	// Declare two new templated binary trees.
	// Sends data --> string, string, string, int, float.
	BinaryTree<string, string, string, int, float> Tree;
	BinaryTree<string, string, string, int, float> TreeTwo;

	string studentName;	// Holds the student's full name.
	string firstName;	// Holds the student's first name.
	string lastName;	// Holds the student's last name.
	string studentGrade;// Holds the student's grade.
	int gradYear;	// Holds the student's graduation year.
	float GPA;	// Holds the student's GPA.

	// Holds the line number that the first entry will be found at.
	int firstEntry = 0;

	// Holds the line number that the second entry will be found at.
	int secondEntry = 1;

	// Holds the line number that the third entry will be found at.
	int thirdEntry = 2;

	// Holds the line number that the fourth entry will be found at.
	int fourthEntry = 3;

	// Holds the line number for the try-catch error check for the 
	// file data input.
	int emptySpaceChecker = 4;

	// Holds the full line string entry from the opened file.
	// Will be either used as is, split up, or converted to 
	// nessasary data types for member variables in Student class.
	string cycle;

	// Keeps track of the individual lines read in from the file.
	// Comparison to the individual entry values.
	int counterTwo = 0;

	// Used for the splitting up of the first entry array
	// into first and last name.
	int counterThree = 0;

	// While loops that gets the individual data values from
	// each line inside of the document.
	while (getline(inputfileTwo, cycle)){
		
		// If statement that calls the throw catch error check for empty lines.
		if (counterTwo == emptySpaceChecker){
			// Throw catch error check to make sure that every fifth line
			// has a value of " ".
			try{
				// Sends the value stored in cycle to the
				// function fifthSpaceTest.
				fifthSpaceTest(cycle);
			}
			
			// Catches the returning string value.
			// (From the fifthSpaceTest function.
			catch (string s){
				cout << endl;	// Spacing.
				cout << s << endl;	// Calls out the value in "s."

				// Displays the line where the problem is taking place.
				cout << "PROBLEM AT LINE: " << counterTwo << endl;

				// Calls out the value of the problem.
				cout << "SPECIFIC ENTRY PROBLEM: " << cycle << endl;

				// Informs the user that the program is terminating because
				// they did not input data correctly. 
				cout << "Program now terminating." << endl;
				cout << "Please reformat input file to adhear to given guidlines..." << endl;

				// Pauses the system so they can read the error message.
				system("PAUSE");

				// Terminates the program.
				exit(1);
			}
			emptySpaceChecker += 5;
		}

		// If statement that gets first name entry starting 
		// at line zero at increments of five.
		// Also splits up cycle entry for name into 
		// fist and last names.
		// Method for splitting up a string found at:
		// http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
		if (counterTwo == firstEntry){
			studentName = cycle;	// Sets studentName string = to cycle.

			// Splits the studentName string variable into two 
			// varaibles.
			istringstream split(studentName);

			// Assigns the value for first name into the 
			// firstName variable.
			if (counterThree == 0){
				split >> firstName;
				counterThree++;	// Increments counterThree.
			}

			// Asigns the value for the last name into the
			// lastName variable.
			if (counterThree == 1){
				split >> lastName;
				counterThree = 0; // Set counter to zero for next iteration.
			}

			// increment first entry to a value of +5.
			firstEntry += 5;
		}
		
		// If statement that assigns the value in cycle to studentGrade
		// when counterTwo is equal to secondEntry.
		if (counterTwo == secondEntry){
			studentGrade = cycle;

			// Increment second entry to a value of +5.
			secondEntry += 5;
			
		}

		// If statement that assigns the value in cycle to gradYear
		// when counterTwo is equal to thirdEntry.
		if (counterTwo == thirdEntry){

			// Converts the string value to an int.
			// atoi string to int conversion found here:
			// http://www.cplusplus.com/forum/general/13135/
			gradYear = atoi(cycle.c_str());

			// Increment third entry to a value of +5.
			thirdEntry += 5;
		}

		// If statement that assigns the value in cycle to GPA
		// when counterTwo is equal to fourthEntry.
		if (counterTwo == fourthEntry){

			// Converts the string value to a float.
			// atof string to double conversion found here:
			// http://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
			GPA = (float)atof(cycle.c_str());

			try{
				// Sends the value stored in GPA to the
				// function checkGPA.
				checkGPA(GPA);
			}
			
			// Catches the returning string value.
			// (From the fifthSpaceTest function.
			catch (string s){
				cout << endl;	// Spacing.
				cout << s << endl;	// Calls out the value in "s."

				// Displays the line where the problem is taking place.
				cout << "PROBLEM AT LINE: " << counterTwo << endl;

				// Calls out the value of the problem.
				cout << "SPECIFIC ENTRY PROBLEM: " << GPA << endl;

				// Informs the user that the program is terminating because
				// they did not input data correctly. 
				cout << "Program now terminating." << endl;
				cout << "Please reformat input file to adhear to given guidlines..." << endl;

				// Pauses the system so they can read the error message.
				system("PAUSE");

				// Terminates the program.
				exit(1);
			}

			// Incrments fourth entry to a value of +5.
			fourthEntry += 5;

			// Since this is the last input for every Student object in the tree,
			// insert the node into the tree. 
			Tree.insertNodeAlpha(firstName, lastName, studentGrade, gradYear, GPA);
			TreeTwo.insertNodeGPA(firstName, lastName, studentGrade, gradYear, GPA);
		}
		
		// Increment counterTwo by one.
		// Keeps track of what line the file is currently reading for comparison
		// in the for loops.
		counterTwo++;
	}

	// Inform the user that the program is closing the file.
	cout << "Closing File..." << endl;

	// Spacing.
	cout << endl;

	// Closes the file.
	inputfileTwo.close();

	// Holds the number of Items in tree number one.
	int numItemsTreeOne = 0;

	// Assigns the return value from getNumElements in the 
	// Tree binary tree to numItemsTreeOne variable.
	numItemsTreeOne = Tree.getNumElements();

   // Declares pointers for arrays for five data members.
   string *firstNameArrayOne;	// Holds the first name values.
   string *lastNameArrayOne;	// Holds the last name values.
   string *gradeLevelArrayOne;	// Holds the grade level values.
   int *graduatingYearArrayOne; // Holds the graduating year values.
   float *GPAArrayOne;	// Holds the GPD values.

   // Dynamically allocates memory for the five newly created arrays.
   firstNameArrayOne = new string[numItemsTreeOne];
   lastNameArrayOne = new string[numItemsTreeOne];
   gradeLevelArrayOne = new string[numItemsTreeOne];
   graduatingYearArrayOne = new int[numItemsTreeOne];
   GPAArrayOne = new float[numItemsTreeOne];

   // Calls the create array function in the Tree binary Tree.
   // This dynaically allocates memory for the arrays
   // created inside of the tree.
   Tree.createArray();
   
   // For loop that calls the individual return functions from the 
   // tree class to get the individual values for each object
   // inside of the tree and assigns them to the arrays created in
   // main. (These arrays are coresponding and will be used for 
   // resubmission to another tree.)
   for (int i = 0; i < numItemsTreeOne; i++){
	   firstNameArrayOne[i] = Tree.getFirstElementArray(i);
	   lastNameArrayOne[i] = Tree.getSecondElementArray(i);
	   gradeLevelArrayOne[i] = Tree.getThirdElementArray(i);   
	   graduatingYearArrayOne[i] = Tree.getFourthElementArray(i);
	   GPAArrayOne[i] = Tree.getFifthElementArray(i);
   }

   // Finds the midpoint of the first Tree.
   int midpointOne = (numItemsTreeOne / 2) + 1;

   // string tempMidpoint = firstNameArrayOne[midpointOne - 1];

   // Declare a third tree. (Used for alpha-traversal)
   BinaryTree<string, string, string, int, float> TreeThree;

   // Inserts the midpoint node.
   // Sends data to be inserted at the possition in the array of midpoint - 1. (Since arrays
   // start at zero) This makes this data the root of the tree.
   TreeThree.insertNodeAlpha(firstNameArrayOne[midpointOne - 1], lastNameArrayOne[midpointOne - 1],
		   gradeLevelArrayOne[midpointOne - 1], graduatingYearArrayOne[midpointOne - 1], 
		   GPAArrayOne[midpointOne - 1]);

   // For loop that inserts the remaining data into the binary tree. (In Alpha-Order)
   for (int i = 0; i < numItemsTreeOne; i++){
	   
	   // If statement that functions if i is not equal to the value of midpoint - 1.
	   // That location of the arrays has already been entered into the binary tree.
	   if (i != (midpointOne - 1)){
		 TreeThree.insertNodeAlpha(firstNameArrayOne[i], lastNameArrayOne[i],
		   gradeLevelArrayOne[i], graduatingYearArrayOne[i], GPAArrayOne[i]);
	   }
   }

   // Variable to store the amount of items in tree two.
   int numItemsTreeTwo = 0;

   // Assigns the return value from getNumElements to the
   // numItemsTreeTwo variable.
   numItemsTreeTwo = TreeTwo.getNumElements();
	
   // Declare pointers for five arrays for five data members.
   string *firstNameArrayTwo;	// Holds the Student's first name.
   string *lastNameArrayTwo;	// Holds the Student's last name.
   string *gradeLevelArrayTwo;	// Holds the Student's grade level.
   int *graduatingYearArrayTwo;	// Holds the Student's graduating year.
   float *GPAArrayTwo;	// Holds the Student's GPA.

   // Dynamically allocates memory for the five newly created arrays.
   firstNameArrayTwo = new string[numItemsTreeTwo];
   lastNameArrayTwo = new string[numItemsTreeTwo];
   gradeLevelArrayTwo = new string[numItemsTreeTwo];
   graduatingYearArrayTwo = new int[numItemsTreeTwo];
   GPAArrayTwo = new float[numItemsTreeTwo];

   // Calls the create array function in the TreeTwo binary Tree.
   // This dynaically allocates memory for the arrays
   // created inside of the tree.
   TreeTwo.createArray();

   // For loop that calls the individual return functions from the 
   // tree class to get the individual values for each object
   // inside of the tree and assigns them to the arrays created in
   // main. (These arrays are coresponding and will be used for 
   // resubmission to another tree.)
   for (int i = 0; i < numItemsTreeOne; i++){
	   firstNameArrayTwo[i] = TreeTwo.getFirstElementArray(i);
	   lastNameArrayTwo[i] = TreeTwo.getSecondElementArray(i);
	   gradeLevelArrayTwo[i] = TreeTwo.getThirdElementArray(i);
	   graduatingYearArrayTwo[i] = TreeTwo.getFourthElementArray(i);
	   GPAArrayTwo[i] = TreeTwo.getFifthElementArray(i);
   }


   // Finds the midpoint of the second tree.
   int midpointTwo = (numItemsTreeTwo / 2) + 1;

   // string tempMidpointTwo = firstNameArrayTwo[midpointTwo - 1];

   // Declares a fourth tree to store the contents in order
   // based on GPA.
   BinaryTree<string, string, string, int, float> TreeFour;

   // Inserts the contents located at the location midpoint - 1. (Since arrays start at
   // zero) into the tree first. This makes the data the root of the tree.
   TreeFour.insertNodeGPA(firstNameArrayTwo[midpointTwo - 1], lastNameArrayTwo[midpointTwo - 1],
		   gradeLevelArrayTwo[midpointTwo - 1], graduatingYearArrayTwo[midpointTwo - 1], 
		   GPAArrayTwo[midpointTwo - 1]);

   // For loop to enter the remaining data into the tree.
   for (int i = 0; i < numItemsTreeTwo; i++){

	   // If statement that functions if i is not equal to the value of midpoint - 1.
	   // That location of the arrays has already been entered into the binary tree.
	   if (i != (midpointTwo - 1)){
		 TreeFour.insertNodeGPA(firstNameArrayTwo[i], lastNameArrayTwo[i],
		   gradeLevelArrayTwo[i], graduatingYearArrayTwo[i], GPAArrayTwo[i]);
	   }
   }

   /* The container file output function is simply a gateway to 
      the heavy hitting functions called dataToFileAlpha and 
	  dataToFielGPA. These two functions traverse the trees that
	  they are called on, and output their object's member 
	  varaibles to a specified file. The user need simply
	  enter a non-casesensitive 'a' (for alpha-order) or 'g'
	  (for GPA order). The binary tree container class 
	  takes over from there.*/

   TreeThree.containerFileOutput('A');	// Teest uppercase letter.

   TreeFour.containerFileOutput('g');	// Test lowcase letter.

   TreeFour.containerFileOutput('T');	// Test error check.


   /*********************************************************
   *  * * * *  * * * *  * * * *  * * * *  * * * *  *     *  *
   *  *        *        *     *  *     *  *        *     *  *
   *  * * * *  * * *    * * * *  * * * *  *        * * * *  *
   *        *  *        *     *  *   *    *        *     *  *
   *  * * * *  * * * *  *     *  *     *  * * * *  *     *  *
   *********************************************************/

   // Spacing.
   cout << endl << endl;
   cout << "\t\t\t*******************" << endl;
   cout << "\t\t\t C++ BINARY SEARCH" << endl;
   cout << "\t\t\t*******************" << endl;
   cout << endl;

   /* For binary searches, call the masterSearch function. This function takes 
      two peramaters. First it takes a char that must be 'A' (for alpha-search)
	  or 'G' (for GPA search). The second peramater is a string peramater. both
	  'A' and 'G' take string peramaters. This is because if G is passed as the char
	  the masterSearch function will convert the string to a float. The master
	  Search function also calls out the amount of time that the query took to
	  the user. Each query (if found) will display all known information about
	  student in question. If a query does not result in a match, a message 
	  stating that no result was found will be displayed to the user. The path
	  taken to find the object or attempt to find the obejct is also displayed 
	  to the user.*/

   // Sends a search query to masterSearch.
   TreeThree.masterSearch('A',"Gates");
   
   // Spacing.
   cout << endl;
   cout << endl;
 
   // Sends a search query to masterSearch.
   TreeThree.masterSearch('a',"Zimmer"); // Test with a lower case 'a.'

   // Spacing.
   cout << endl;
   cout << endl;

   // Sends a search query to masterSearch.
   TreeThree.masterSearch('A', "FooBar"); // Test Non-existant name.
   
   // Spacing.
   cout << endl;
   cout << endl;

   // Sends a search query to masterSearch.
   TreeFour.masterSearch('G', ".8");

   // Spacing.
   cout << endl;
   cout << endl;

   // Sends a search query to masterSearch.
   TreeFour.masterSearch('g', "3"); // Test with a lowercase 'g.'

   // Sends a search query to masterSearch.
   TreeFour.masterSearch('G', ".1234"); // Test a value not in the tree.

   // Sends a search query to masterSearch.
   TreeFour.masterSearch('G', "5"); // Test an impossible value.

   // Sends a search query to masterSearch.
   TreeFour.masterSearch('h', "NOT POSSIBLE!!!"); // Test the error check inside masterSearch.

    // Display the program to the user until they deem termination nessasary.
	cin >> werd;
	return 0;
}
// ERROR CHECK LIBRARY...
// ERROR -01: You have made an invalid selection.
// ERROR -02: You have entered an invalid file location.
// ERROR -06: Line should be empty, but is not.

/***************************************************
* NAME: PAUSE									   *
* PURPOSE: Pauses the program until the audio	   *
*		   directions have been fully read to the  *
*		   user. This makes sure that the user	   *
*		   does not prematurly enter into the	   *
*		   program without knowing what to		   *
*		   enter. (In terms of file location)	   *
* INPUT: int.									   *
* OUTPUT: NONE.									   *
***************************************************/
void pause(int duration){

		// clock_t variable that holds the value of duration plus
		// current system time. (Whenever the function was called
		// from main)
		clock_t secondTracker = duration + clock();

		// While loop that holds the program idle while the audio
		// directions are playing for the user.
		while (secondTracker > clock());
}

/***************************************************
* NAME: FIFTHSPACETEST.							   *
* PURPOSE: Tests to make sure that the line has no *
*		   value stored in it. (As per the		   *
*		   governing rules of the exam)			   *
* INPUT: string									   *
* OUTPUT: (Potiential) Throw. (Of string)		   *
***************************************************/
void fifthSpaceTest(string lineInput){

	if (!lineInput.empty()){
		throw string("ERROR -06: Line should be empty, but is not.");
	}

}

/***************************************************
* NAME: CHECKGPA.								   *
* PURPOSE: Test to make sure that the GPA being	   *
*		   entered into the binary tree is between *
*		   the allowed spectrum. (0-4)			   *
* INPUT: string									   *
* OUTPUT: (Potiential) Throw. (Of string)		   *
***************************************************/
void checkGPA(float GPA){

	if (GPA < 0 || GPA > 4){
		throw string("ERROR -07: GPA out of bounds! Must be between 0-4.");
	}
}

// Inform bartley that he has to change the file location of the sound file. If he does not, he will have to
// pause 14 seconds to continue (or press n to the audio directions). Also tell him the libraries needed.

// Error checks displayed to the screen are intentional. Test cases were given inside of the program.

// Throw catch error exceptions will terminate the program do to inability to enter in credible data.
// This is because there will have been a breach in the governing rule of the exam for file format.
// They are not intentional.