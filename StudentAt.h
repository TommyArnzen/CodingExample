// Tommy Arnzen
// CIS 226
// Final Exam
// Due: Friday, December 13th, 2013 (11:00 PM)

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

// Student Test Class for binary tree input.
class Student{
private:
	  string firstName;		// Holds the student's first name.
	  string lastName;		// Holds the student's last name.
	  string gradeLevel;	// Holds the student's grade level.
	  int gradYear;			// Holds the year the student will gradulate.
	  float GPA;			// Holds the student's GPA.	

public:

	// Constructor.
	Student(){
		firstName = " ";
		lastName = " ";
		gradeLevel = " ";
		gradYear = 0;
		GPA = 0.0;
	}

	// Mutator Functions.
	// Sets the first name.
	void setFirstName(string fName){
		firstName = fName;
	}

	// Sets the last name.
	void setLastName(string lName){
		lastName = lName;
	}

	// Sets the grade level.
	void setGradeLevel(string GL){
		gradeLevel = GL;
	}

	// Sets the graduation year.
	void setGradYear(int GY){
		gradYear = GY;
	}

	// Sets the grade point average.
	void setGPA(float GradePAvg){
		GPA = GradePAvg;
	}

	// Returns the first name.
	string getFirstName() const{
		return firstName;
	}

	// Returns the last name.
	string getLastName() const{
		return lastName;
	}

	// Retursn the grade level.
	string getGradeLevel() const{
		return gradeLevel;
	}

	// Returns the graduation year.
	int getGradYear() const{
		return gradYear;
	}

	// Returns the grade point average.
	float getGPA() const{
		return GPA;
	}


      Student *left;    // Pointer to left child node.
      Student *right;   // Pointer to right child node.

};

#endif STUDENT_H