// Tommy Arnzen
// CIS 226
// Final Exam
// Due: Friday, December 13th, 2013 (11:00 PM)

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>	// For cout, cin, ect.
#include <fstream>	// For File output.
#include "StudentAt.h" // For Student class.
#include <time.h>
using namespace std;

// Binary Tree Template Class.
template <class T, class A, class B, class C, class D>
class BinaryTree{

private:

   Student *root;       // Pointer to the root node
   int numElements;		 // Holds the number of elements inputed to the tree.
   int counter;		 	 // Counter for array input.

   // Arrays for data transfer...
   T *firstElementArray;		// Pointer for array to hold first element.
   A *secondElementArray;		// Pointer for array to hold second element.
   B *thirdElementArray;		// Pointer for array to hold third element.
   C *fourthElementArray;		// Pointer for array to hold fourth element.
   D *fifthElementArray;		// Pointer for array to hold fifth element.
   
   // Private member functions
   void insertAlpha(Student *&, Student *&); // Inserts data in alphabetical order.
   void insertGPA(Student *&, Student *&);   // Inserts data in GPA order. (4-0).
   void destroySubTree(Student *);	// Destroys the subtree.
   void deleteNode(T, A, Student *&); // Deletes a selected node from the tree.
   void makeDeletion(Student *&);  // Specifies a deletion.
   void displayTree(Student *) const;	// Displays the contents of the tree.
   void createArray(Student *); // Allocates memory for the element arrays.
   void dataToFileAlpha(Student *, ostream &) const; // Sends data in alpha-order to file.
   void dataToFileGPA(Student *, ostream &) const; // Sends data in GPA-order to file.
   
public:
   // Constructor -> Sets roots to NULL, numelement counter to zero
   // and counter to zero.
   BinaryTree()
      { root = NULL;
		numElements = 0;
		counter = 0;
      }
      
   // Destructor (Binary Tree Class)
   ~BinaryTree()
      { destroySubTree(root); // Destroys the tree. Passes the root as a peramater.
	    delete []firstElementArray;	// Deletes the firstElementArray.
		delete []secondElementArray;// Deletes the secondElementArray.
	    delete []thirdElementArray; // Deletes the thirdElementArray.
		delete []fourthElementArray;// Deletes the fourthElementArray.
	    delete []fifthElementArray; // Deletes the fifthElementArray.
   }
      
   // Binary tree operations
   void insertNodeAlpha(T, A, B, C, D);	// Inserts Nodes in alpha-order.
   void insertNodeGPA(T, A, B, C, D);	// Inserts Nodes in GPA-order.
   void masterSearch(char, string);
   bool searchNodeLastName(T);	// Searches Tree based on last name query.
   bool searchNodeGPA(D);	// Searches Tree based on GPA query.
   void remove(T, A);	// Removes an element from the tree.
   void testArray();	// Test the input to the array through output.
   
   // Returns the value stored in numElements.
   int getNumElements() const{
	   return numElements;
   }

   /***************************************************
   * NAME: CREATEARRAY.	   						      *
   * PURPOSE: Creates an array for each individual	  *
   *		  variable that holds data from file	  *
   *		  input (In this case five - See Student  *
   *		  class in StudentAt.h for variable		  *
   *		  names). Number of spaces allocated for  *
   *		  each array is based on the numElements  *
   *		  counter (Incremented based on input to  *
   *		  binary tree from main). Passes root to  *
   *		  the overloaded createArray function	  *
   *		  which in turn inserts all nessasary	  *
   *		  data into the five element arrays.	  *
   * INPUT: NONE.									  *
   * OUTPUT: NONE.									  *
   ***************************************************/
   void createArray(){
	   firstElementArray = new T[numElements];
	   secondElementArray = new A[numElements];
	   thirdElementArray = new B[numElements];
	   fourthElementArray = new C[numElements];
	   fifthElementArray = new D[numElements];
	   createArray(root);
   }

   // Calls the displayTree function with the
   // root as a peramater through a const function.
   void displayTree() const
      {  displayTree(root); }

   // Function to determine which method to output data to the
   // files based on user input.
   void containerFileOutput(char choice){

	   if (choice == 'a' || choice == 'A'){
		   dataToFileAlpha();
	   }

	   else if (choice == 'g' || choice == 'G'){
		   dataToFileGPA();
	   }

	   else{
		   cout << "\nERROR -05: You have made an invalid selection for " <<
				"containerFileOutput." << endl;
		   cout << "Please go back to main and enter a differnt charector." << endl;
	   }


   }

   /***************************************************
   * NAME: DATATOFILEALPHA.							  *
   * PURPOSE: Establishes a new file, calls out the   *
   *			  heading (inside of the file), and	  *
   *		  recursivly sends the data to the file	  *
   *		  through traversal of the tree. Calls	  *
   *		  the dataToFileApla private member		  *
   *		  function and sends it peramaters		  *
   *		  root (of the tree), and AlphaOutput.    *
   * INPUT: NONE.									  *
   * OUTPUT: Data Sent to File.						  *
   ***************************************************/
   void dataToFileAlpha() const {
	   // Method for recursive data output to file found at:
	   // stackoverflow.com/questions/2239607/can-a-recursive-function
	   // -write-to-a-file-in-c

	    // Declares and opens a new file.
        ofstream AlphaOutput;
		AlphaOutput.open("FinalExam1_TA.txt");
		cout << "Now Writting data to the file(FinalExam1_TA.txt)." << endl;

		// Calls out the heading of the file.
		AlphaOutput << "\t\t\t********************" << endl;
		AlphaOutput << "\t\t\t Alphabetical Order" << endl;
		AlphaOutput << "\t\t\t********************" << endl;

		// Spacing.
		AlphaOutput << endl;
		cout << endl;

		// Sends the root amd the file reference to the
		// dataToFileAlpha private member function.
		dataToFileAlpha(root, AlphaOutput); 

		// Closes the fiel.
		AlphaOutput.close();

		cout << endl;	// Spacing.

		// Informs the user that the file has been closed.
		cout << "Finished sending data to file." << endl;
		cout << endl;
      }

   /***************************************************
   * NAME: DATATOFILEGPA.							  *
   * PURPOSE: Establishes a new file, calls out the   *
   *			  heading (inside of the file), and	  *
   *		  recursivly sends the data to the file	  *
   *		  through traversal of the tree. Calls	  *
   *		  the dataToFileApla private member		  *
   *		  function and sends it peramaters		  *
   *		  root (of the tree), and GPAOutput.      *
   * INPUT: NONE.									  *
   * OUTPUT: Data Sent to File.						  *
   ***************************************************/
   void dataToFileGPA() const {

	    // Declares and opens a new file.
	    ofstream GPAOutput;
        GPAOutput.open("FinalExam2_TA.txt");

		// Informs the user that data is being written to the file.
		cout << "Now writting data to the file(FinalExam2_TA.txt)." << endl;

		// Calls out the heading inside of the file.
		GPAOutput << "\t\t\t***********" << endl;
		GPAOutput << "\t\t\t GPA Order" << endl;
		GPAOutput << "\t\t\t***********" << endl;

		// Spacing.
		GPAOutput << endl;
		cout << endl;

		// Sends the peramaters root (of the tree), and 
		// GPAOutput to the dataToFileGPA function.
		dataToFileGPA(root, GPAOutput);

		// Closes the file.
		GPAOutput.close();
		cout << endl;	// Spacing.

		// Informs the user that the program has finished
		// sending data to the file.
		cout << "Finished sending data to file." << endl; 
		cout << endl;
      }

   // Sends the data in individual memory locations of the 
   // respective function to main when called upon.
   T getFirstElementArray(int) const;
   A getSecondElementArray(int) const;
   B getThirdElementArray(int) const;
   C getFourthElementArray(int) const;
   D getFifthElementArray(int) const;
      
};

/***************************************************
* NAME: INSERTALPHA.							   *
* PURPOSE: This function recursivly inserts the	   *
*		   node into the tree pointed to by the    *
*		   Student nodePtr pointer.	Uses the "<"   *
*		   comparison operator for entry.		   *
* INPUT: Student, Student						   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::insertAlpha(Student *&nodePtr, Student *&newNode){
   
   // If statement that functions if nodePtr is equal to NULL.
   if (nodePtr == NULL)
      nodePtr = newNode;                  // Insert the node.

   // If statement that functions if the value in newPtr->lastName
   // is less than the value stored in nodePtr->value.
   else if (newNode->getLastName() < nodePtr->getLastName())
	   insertAlpha(nodePtr->left, newNode);     // Search the left branch

   // If statement that functions if the previous two if statements
   // resulted in false.
   else 
      insertAlpha(nodePtr->right, newNode);    // Search the right branch

}

/***************************************************
* NAME: INSERTNODEALPHA.						   *
* PURPOSE: Creates a Student node called "newNode" *
*           to hold the the peramaters passed -	   *
*		   inside its data members. It then		   *
*		   passes it to the insert function.	   *
* INPUT: T, A, B, C, D							   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::insertNodeAlpha(T SfirstName, A SlastName,
										   B SstudentGrade, C Sgradyear, D SGPA){

   Student *newNode;      // Pointer to a new node.

   // Create a new node and store the peramater being passes
   // inside of  it.
   newNode = new Student;	// Allocate Space.
   newNode->setFirstName(SfirstName);	// Store First Name.
   newNode->setLastName(SlastName);	// Store Last Name.
   newNode->setGradeLevel(SstudentGrade);	// Store Grade Level.
   newNode->setGradYear(Sgradyear);	// Store Graduation Year.
   newNode->setGPA(SGPA);	// Store GPA.
   newNode->left = newNode->right = NULL;	// Set the left and right nodes to NULL.
   
   // Insert the node.
   // Sends the node to the insert Alpha Function.
   insertAlpha(root, newNode);

   // Increment numElements by one for each newNode entered
   // into the tree.
   numElements++;
}

/***************************************************
* NAME: INSERTGPA.								   *
* PURPOSE: This function recursivly inserts the	   *
*		   node into the tree pointed to by the    *
*		   Student nodePtr pointer.	Uses the ">"   *
*		   comparison operator for entry.		   *
* INPUT: TreeNode, TreeNode.					   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::insertGPA(Student *&nodePtr, Student *&newNode){
   
   // If statement that functions if nodePtr is equal to NULL.
   if (nodePtr == NULL)
      nodePtr = newNode;                  // Inserts the node.

   // If statement that functions if the value in newPtr->GPA
   // is greater than the value stored in nodePtr->GPA.
   else if (newNode->getGPA() > nodePtr->getGPA()){
      insertGPA(nodePtr->left, newNode);     // Search the left branch
   }

   // If statement that functions if the previous two if statements
   // resulted in false.
   else 
      insertGPA(nodePtr->right, newNode);    // Search the right branch

}

/***************************************************
* NAME: INSERTNODEGPA							   *
* PURPOSE: Creates a Student node called "newNode" *
*           to hold the the peramaters passed -	   *
*		   inside its data members. It then		   *
*		   passes it to the insert function.	   *
* INPUT: T, A, B, C, D.							   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::insertNodeGPA(T SfirstName, A SlastName,
										   B SstudentGrade, C Sgradyear, D SGPA){

   Student *newNode;      // Pointer to a new node.

   // Create a new node and store the peramater being passes
   // inside of  it.
   newNode = new Student;	// Allocate memory for a new Student node.
   newNode->setFirstName(SfirstName);	// Store the first name.
   newNode->setLastName(SlastName);	// Store the last name.
   newNode->setGradeLevel(SstudentGrade); // Store the grade level.
   newNode->setGradYear(Sgradyear);	// Store the graduation year.
   newNode->setGPA(SGPA);	// Store the GPA.
   newNode->left = newNode->right = NULL; // Set right and left pointers to NULL.
   
   // Insert the node.
   // Pass the newly created node to the insertGPA function.
   insertGPA(root, newNode);

   // Increment numElements by one for each newNode entered
   // into the tree.
   numElements++;
}

/***************************************************
* NAME: DESTROYSUBTREE.							   *
* PURPOSE: Called by the destructor... This		   *
*		   fucntion destroys all nodes in the	   *
*		   tree upon termination.				   *
* INPUT: TreeNode.								   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::destroySubTree(Student *nodePtr){

   // If nodePointer points to something...
   if (nodePtr){

      // If nodePtr->Left points to something...
	  // Destroy nodePtr->Left by recursivly 
	  // calling the destroySubTree function.
      if (nodePtr->left)
         destroySubTree(nodePtr->left);

	  // If nodePtr->Right points to something...
	  // Destroy nodePtr->Right by recursivly 
	  // calling the destroySubTree function.
      if (nodePtr->right)
         destroySubTree(nodePtr->right);

	  // Deletes the nodePtr.
      delete nodePtr;
   }
}

/***************************************************
* NAME: SEARCHNODELASTNAME.						   *
* PURPOSE: Determins if the value passed from main *
*		   (A string value in the case of name) is *
*		   present in the current state of the	   *
*		   tree. Displays the path taken to find   *
*		   the object. If the object is not found, *
*		   all elements that are searched are      *
*		   displayed, and the user is notified	   *
*		   that the query was not found.		   *
* INPUT: T.										   *
* OUTPUT: Bool.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
bool BinaryTree<T, A, B, C, D>::searchNodeLastName(T item){
   
	// Create a new nodePtr and set it equal to the
	// root of the tree.
	Student *nodePtr = root;

   // While nodePtr points to something...
   while (nodePtr){

	  // If the nodePtr->lastName is equal to the query,
	  // return true, and display that the result was 
	  // found.
      if (nodePtr->getLastName() == item){
		  if (nodePtr == root){
			  cout << "Root Node --> ";
		  }

		 // Calls out that the result was found.
		 // It then calls out the contents associated with that result.
		 cout << "RESULT FOUND: ";
		 cout << nodePtr->getLastName() << endl;
		 cout << endl;
		 cout << "---------------------------" << endl;
		 cout << "Student Information:" << endl;
		 cout << "First Name: " << nodePtr->getFirstName() << endl;
		 cout << "Last Name: " << nodePtr->getLastName() << endl;
		 cout << "Grade Level: " << nodePtr->getGradeLevel() << endl;
		 cout << "Graduation Year: " << nodePtr->getGradYear() << endl;
		 cout << "GPA: " << nodePtr->getGPA() << endl;
		 cout << endl;
         return true;	// Returns True.
	  }

	  // If the query is higher in order than 
	  // nodePtr->lastName, nodePtr = nodePtr->left.
      else if (item < nodePtr->getLastName()){
		  if (nodePtr == root){
			  cout << "Root Node: " << nodePtr->getLastName() << endl;
			  nodePtr = nodePtr->left;
		  }
			 cout << "Left: " << nodePtr->getLastName() << endl;
			 nodePtr = nodePtr->right;
	  }

	  // If the query is lower in rder than 
	  // nodePtr->value, nodePtr = nodePtr->right.
      else{
		 if (nodePtr == root){
			  cout << "Root Node: " << nodePtr->getLastName() << endl;
			  nodePtr = nodePtr->right;
		 }

			cout << "Right: " << nodePtr->getLastName() << endl;
			nodePtr = nodePtr->right;
	  }
   }

   // If the value is not found, return false.
   // Also display the origional query for user 
   // reference.
   cout << "--------------------------------------" << endl;
   cout << "Sorry that student is not in the tree." << endl;
   cout << "Query: " << item << endl;
   cout << "--------------------------------------" << endl;
   cout << endl;
   return false;	// Returns false.
}

/***************************************************
* NAME: SEARCHNODEGPA.							   *
* PURPOSE: Determins if the value passed from main *
*		   (A float value in the case of GPA) is   *
*		   present in the current state of the	   *
*		   tree. Displays the path taken to find   *
*		   the object. If the object is not found, *
*		   all elements that are searched are      *
*		   displayed, and the user is notified	   *
*		   that the query was not found.		   *
* INPUT: D.										   *
* OUTPUT: Bool.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
bool BinaryTree<T, A, B, C, D>::searchNodeGPA(D item){
   
	// Create a new nodePtr and set it equal to the
	// root of the tree.
	Student *nodePtr = root;

   // While nodePtr points to something...
   while (nodePtr){

	  // If the nodePtr->GPA is equal to the query,
	  // return true, and display that the result was 
	  // found.
      if (nodePtr->getGPA() == item){
		  if (nodePtr == root){
			  cout << "Root Node -->";
		  }

		 // Informs the user that a result was found.
		 // Then calls out all data associated with that result.
		 cout << "RESULT FOUND: ";
		 cout << nodePtr->getGPA() << endl;
		 cout << endl;
		 cout << "---------------------------" << endl;
		 cout << "Student Information:" << endl;
		 cout << "First Name: " << nodePtr->getFirstName() << endl;
		 cout << "Last Name: " << nodePtr->getLastName() << endl;
		 cout << "Grade Level: " << nodePtr->getGradeLevel() << endl;
		 cout << "Graduation Year: " << nodePtr->getGradYear() << endl;
		 cout << "GPA: " << nodePtr->getGPA() << endl;
		 cout << endl;
         return true;	// Returns true.
	  }

	  // If the query is greater than the value inside of
	  // nodePtr->GPA, nodePtr = nodePtr->left.
      else if (item > nodePtr->getGPA()){
		  if (nodePtr == root){
			  cout << "Root Node: " << nodePtr->getGPA() << endl;
			  nodePtr = nodePtr->left;
		  }
		  cout << "Left: " << nodePtr->getGPA() << endl;
          nodePtr = nodePtr->right;
	  }

	  // If the query is less than the value in nodePtr->GPA,
	  // nodePtr = nodePtr->right.
      else{
		 if (nodePtr == root){
			  cout << "Root Node: " << nodePtr->getGPA() << endl;
			  nodePtr = nodePtr->right;
		 }
		 cout << "Right: " << nodePtr->getGPA() << endl;
         nodePtr = nodePtr->right;
	  }
   }

   // If the value is not found, return false.
   // Also display the origional query for user reference.
   cout << "----------------------------------" << endl;
   cout << "Sorry that GPA is not in the tree." << endl;
   cout << "Query: " << item << endl;
   cout << "----------------------------------" << endl;
   cout << endl;
   return false;	// Returns false.
}

/***************************************************
* NAME: MASTERSEARCH.							   *
* PURPOSE: Accepts a char and a string as its	   *
*		   peramaters. Uses the char to determine  *
*		   what function to call, and uses the	   *
*		   string as the query. (Sends the string  *
*		   to the search function) If char is	   *
*		   equal to "G", function converts string  *
*		   to a float and then comences search.    *
*		   If char is equal to "A", function sends *
*		   the string as is to the Alpha search.   *
* INPUT: T, TreeNode.							   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T,A,B,C,D>::masterSearch(char searchType, string search){

	// If statement that functions if searchType equal 'a' or 'A.'
	if (searchType == 'a' || searchType == 'A'){
		  bool returnValue;	// Holds the return value.
		  clock_t startTime = clock();	// Stores the time of search.
		  
		  // Calls the searchNodeLastName function and stores returning bool in returnValue.
		  returnValue = searchNodeLastName(search);

		  // If return value equals true, display the successful query time.
		  if (returnValue == true){
			  cout << "Query Time: " << clock() - startTime << " Milliseconds" << endl;
			  cout << "---------------------------" << endl;
			  cout << endl;
		  }
	}

	// If Statement the functions if searchType equals 'g' or 'G.'
	else if (searchType == 'g' || searchType == 'G'){
		bool returnValue;	// Holds the return value.
		clock_t startTime = clock(); // Stores the time of the search.
		float stringTofloat; // Variable that holds the converted string as a float.
		
		// Converts the string to a float.
		stringTofloat = (float)atof(search.c_str());
		
		// Error check to make sure that the float entered for GPA is
		// not outside the allowed spectrum of 0-4.
		if(stringTofloat > 4 || stringTofloat < 0){
			cout << "\n\nERROR -04: GPA query not within possible realm of allowance (0-4)." << endl;
			cout << "Please go back to main function and update search query to a value between 0-4." << endl;
		}

		// If statement that function if stringToflaot is a valid entry (Between 0-4).
		else if (stringTofloat <= 4 && stringTofloat >= 0){
			returnValue = searchNodeGPA(stringTofloat);

			// If the return value is true, display the successfull query time.
			if (returnValue == true){
				cout << "Query Time: " << clock() - startTime << " Milliseconds" << endl;
				cout << "---------------------------" << endl;
				cout << endl;
			}
		}
	}

	// Error check that functions if an invalid char is entered in a search
	// query (Anything that is not uppercase or lowercase 'a' or 'g.').
	if (searchType != 'g' && searchType != 'G' && searchType != 'a' &&
		searchType != 'A'){
			cout << "\n\nERROR -03: You have not entered an invalid entry for searchType." << endl;
			cout << "It must either be uppercase or lowercase version of 'g' or 'a.'" << endl;
			cout << "Please go back to main function and alter your query." << endl;
	}
}

/***************************************************
* NAME: REMOVE.									   *
* PURPOSE: Calls the deleteNode function, with     *
*		   peramaters item and root. Ment only to  *
*		   be called by last name.				   *
* INPUT: A.										   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::remove(T fName, A lName){

   // Send user input to the deleteNode function
   // along with the root.
   deleteNode(fName, lName, root);
}

/***************************************************
* NAME: DELETENODE								   *
* PURPOSE: Deletes the node who has a value member *
*		   that is the same as the number passed   *
*		   to it. For the case of same last names, *
*		   the first name is tested.			   *
* INPUT: A, TreeNode.							   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::deleteNode(T fName, A lName, Student *&nodePtr){

   // If item is less than nodePtr->value,
   // recursivly call deleteNode with peramaters
   // item, and nodePtr->left.
	if (lName < nodePtr->getLastName() && fName != nodePtr->getFirstName())
		deleteNode(fName, lName, nodePtr->left);

   // If item is greater than nodePtr->value,
   // recursivly call deleteNode with peramaters
   // item, and nodePtr->right.
	else if (lName > nodePtr->getLastName() && fName != nodePtr->getFirstName())
		deleteNode(fName, lName, nodePtr->right);

   // Else send the nodePtr to the makeDeletion function.
   else
       makeDeletion(nodePtr);
}

/***************************************************
* NAME: MAKEDELETION.							   *
* PURPOSE: Recieves a reference to a pointer to a  *
*		   node that is to be deleted. It then     *
*		   removes the node and the branches of    *
*		   the tree below the node are reattached. *
* INPUT: Student.								   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::makeDeletion(Student *&nodePtr)
{
   // Declare a temporary pointer.
   Student *tempNodePtr;

   // If nodePtr == "NULL" inform the user that they cannot 
   // delete an empty node.
   if (nodePtr == NULL)
      cout << "Cannot delete empty node.\n";

   // If nodePtr->right == "NULL," reattach the 
   // left child.
   else if (nodePtr->right == NULL){
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->left;
      delete tempNodePtr;
   }

   // If nodePtr->right == "NULL," reattach the 
   // left child.
   else if (nodePtr->left == NULL){
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->right;
      delete tempNodePtr;
   }


   // If the node in question has no children.
   else{

      // Move one node the right.
      tempNodePtr = nodePtr->right;
      // Go to the end left node.
      while (tempNodePtr->left)
         tempNodePtr = tempNodePtr->left;
      // Reattach the left subtree.
      tempNodePtr->left = nodePtr->left;
      tempNodePtr = nodePtr;
      // Reattach the right subtree.
      nodePtr = nodePtr->right;
      delete tempNodePtr;
   }
}

/***************************************************
* NAME: DISPLAYTREE.							   *
* PURPOSE: Displays the values in the subtree	   *
*          using inorder traversal.				   *
* INPUT: Student const.						   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::displayTree(Student *nodePtr) const{

   // If nodePtr points to something...
   if (nodePtr){
	  
	  // Recursivly calls displayTree function with peramater
	  // nodePtr->left.
      displayTree(nodePtr->left);

	  // Calls out the contents stored in nodePtr.
      cout << nodePtr->getFirstName() << " " << nodePtr->getLastName() << endl;
	  cout << nodePtr->getGradeLevel()  << endl;
	  cout << nodePtr->getGradYear() << endl;
	  cout << nodePtr->getGPA() << endl;
	  cout << endl;

	  // Recursivly calls displayTree with peramater
	  // nodePtr->right.
      displayTree(nodePtr->right);
   }
}

/***************************************************
* NAME: DATATOFILEGPA							   *
* PURPOSE: Uses the process of inorder traversal   *
*		   to traverse the tree. For each location *
		   (Node) visits, this function outputs    *
		   the contents of all the data members	   *
		   being stored in that node to a		   *
		   document.							   *
* INPUT: Student *, ostream &.					   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::dataToFileGPA(Student *nodePtr, ostream &GPAOutput) const{


   // If nodePtr points to something...
   if (nodePtr){
	  
	  // Recursivly calls datToFileGPA with peramaters
	  // nodePtr->left, and GPAOutput.
	  dataToFileGPA(nodePtr->left, GPAOutput);

	  // Calls out the values being stored in each
	  // object that nodePtr is pointing to.
      GPAOutput << nodePtr->getFirstName() << " " << nodePtr->getLastName() << endl;
	  GPAOutput << nodePtr->getGradeLevel()  << endl;
	  GPAOutput << nodePtr->getGradYear() << endl;
	  GPAOutput << nodePtr->getGPA() << endl;
	  GPAOutput << endl;

	  // Recursivly calls dataToFileGPA with peramaters
	  // nodePtr->right, and GPAOutput.
	  dataToFileGPA(nodePtr->right, GPAOutput);
   }
}

/***************************************************
* NAME: DISPLAYINORDER.							   *
* PURPOSE: Uses the process of inorder traversal   *
*		   to traverse the tree. For each location *
*		   (Node) visits, this function outputs    *
*		   the contents of all the data members	   *
*		   being stored in that node to a		   *
*		   document.							   *
* INPUT: Student *, ostream &.					   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::dataToFileAlpha(Student *nodePtr, ostream &AlphaOutput) const{


   // If nodePtr points to something...
   if (nodePtr){
	  
	  // Recursivly calls displayInOrder with peramater
	  // nodePtr->left.
	  dataToFileAlpha(nodePtr->left, AlphaOutput);

	  // Calls out the nodePtr->value.
      AlphaOutput << nodePtr->getFirstName() << " " << nodePtr->getLastName() << endl;
	  AlphaOutput << nodePtr->getGradeLevel()  << endl;
	  AlphaOutput << nodePtr->getGradYear() << endl;
	  AlphaOutput << nodePtr->getGPA() << endl;
	  AlphaOutput << endl;

	  // Recursivly calls displayInOrder with peramater
	  // nodePtr->right.
	  dataToFileAlpha(nodePtr->right, AlphaOutput);
   }
}

/***************************************************
* NAME: CREATEARRAY.							   *
* PURPOSE: Inserts the values stored in the		   *
*		   objects being stored in the tree into   *
*		   their respective counters.			   *
* INPUT: Student *.								   *
* OUTPUT: NONE.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
void BinaryTree<T, A, B, C, D>::createArray(Student *nodePtr){

	// If nodePtr points to something...
	if (nodePtr){

		// Traverse the left side of the tree recursivly.
		createArray(nodePtr->left);

		// Assign the various data members to their respective 
		// arrays.
		firstElementArray[counter] = nodePtr->getFirstName();
		secondElementArray[counter] = nodePtr->getLastName();
		thirdElementArray[counter] = nodePtr->getGradeLevel();
		fourthElementArray[counter] = nodePtr->getGradYear();
		fifthElementArray[counter] = nodePtr->getGPA();

		// Increment counter (By one) to the next location.
		counter++;

		// Traverse the right side of the tree recursivly.
		createArray(nodePtr->right);
	}
}

/***************************************************
* NAME: GETFIRSTELEMENTARRAY.					   *
* PURPOSE: Returns the value stored in the         *
*		   array at the location of the value      *
*		   sent to the function.				   *
* INPUT: int.									   *
* OUTPUT: T.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
T BinaryTree<T, A, B, C, D>::getFirstElementArray(int i) const{

	// Return the value stored in elementArray at the
	// location equal to the peramater.
	return firstElementArray[i];
}

/***************************************************
* NAME: getSecondElementArray.					   *
* PURPOSE: Returns the value stored in the         *
*		   array at the location of the value      *
*		   sent to the function.				   *
* INPUT: int.									   *
* OUTPUT: A.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
A BinaryTree<T, A, B, C, D>::getSecondElementArray(int i) const{

	// Return the value stored in elementArray at the
	// location equal to the peramater.
	return secondElementArray[i];
}

/***************************************************
* NAME: getThirdElementArray.					   *
* PURPOSE: Returns the value stored in the         *
*		   array at the location of the value      *
*		   sent to the function.				   *
* INPUT: int.									   *
* OUTPUT: B.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
B BinaryTree<T, A, B, C, D>::getThirdElementArray(int i) const{

	// Return the value stored in elementArray at the
	// location equal to the peramater.
	return thirdElementArray[i];
}

/***************************************************
* NAME: getFourthElementArray.					   *
* PURPOSE: Returns the value stored in the         *
*		   array at the location of the value      *
*		   sent to the function.				   *
* INPUT: int.									   *
* OUTPUT: C.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
C BinaryTree<T, A, B, C, D>::getFourthElementArray(int i) const{

	// Return the value stored in elementArray at the
	// location equal to the peramater.
	return fourthElementArray[i];
}

/***************************************************
* NAME: getFifthElementArray.					   *
* PURPOSE: Returns the value stored in the         *
*		   array at the location of the value      *
*		   sent to the function.				   *
* INPUT: int.									   *
* OUTPUT: D.									   *
***************************************************/
template <class T, class A, class B, class C, class D>
D BinaryTree<T, A, B, C, D>::getFifthElementArray(int i) const{

	// Return the value stored in elementArray at the
	// location equal to the peramater.
	return fifthElementArray[i];
}

#endif BINARYTREE_H
// ERROR CHECK LIBRARY...
// ERROR -03: You have not entered an invalid entry for searchType.
// ERROR -04: GPA query not within possible realm of allowance (0-4).
// ERROR -05: You have made an invalid selection for containerFileOutput.

// TODO
// Create a secondary search function that searches the rest of the list once
//			a search is found. OR USE DELETE.
// Create a copy constructor.
// File input errors.