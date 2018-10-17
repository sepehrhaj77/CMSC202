/*File: Person.cpp
Project: CMSC 202 Project 5, Fall 2016
Author: Sepehr Hajbarat
Date: 12/10/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Person.h*/
#include "Person.h"
using namespace std;

//Person default constructor
//Creates a Person with no values for their variables
Person::Person(){
  m_id = 0;
  m_fName = "";
  m_lName = "";
  m_age = 0;
  m_weight = 0;
}

//Person constructor
//Creates a person and sets its variables to the parameters
Person::Person(string infName, string inlName, double inWeight, int inAge, int inId){;
  m_fName = infName;
  m_lName = inlName;
  m_weight = inWeight;
  m_age = inAge;
  m_id = inId;
}

//GetId
//returns the ID of the Person, but does not allow manipulation
int Person::GetId() const{
  return m_id;
}

//GetFName
//returns the first name of the Person, but does not allow manipulation
string Person::GetFName() const{
  return m_fName;
}

//GetLName
//returns the last name of the Person, but does not allow manipulation
string Person::GetLName() const{
  return m_lName;
}

//GetAge
//returns the age of the Person, but does not allow manipulation
int Person::GetAge() const{
  return m_age;
}

//GetWeight
//returns the weight of the Person, but does not allow manipulation
double Person::GetWeight() const{
  return m_weight;
}

//ToString
//creates a single string for output using a Person object
string Person::ToString() const{
  //variable to hold concactenated string which adds numbers as well
  ostringstream stream; 
  //adds all the info to the stream, to make it one long string with non string data types
  stream << "First Name: " << m_fName << "\nLast Name: " << m_lName << "\nAge: " << m_age << "\nWeight: " << m_weight;
  //returns the single stream which holds all the information
  return stream.str();
}

