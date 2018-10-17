#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Item.h"
#include "Person.h"

#include <vector>
#include <sstream> //Used to concatenate a string that includes numbers
#include <iomanip> //Used to format weights to make more sense
#include <iterator>

#include <iostream>
using namespace std;

template <class T>
class Spaceship
{
 public:
  //Name: Spaceship
  //Default constructor 
  Spaceship();
  
  //Name: Spaceship(string, string, double) Overloaded constructor.
  //Precondition: Requires ship file has been loaded
  //Postcondition: Builds a new templated ship
  Spaceship(string inName, string inType, double inCapacity);

  //Name: GetCargo
  //Precondition: Requires that the ship's cargo has been populated
  //Postcondition: Templated accessor for this ship's cargo
  vector<T> GetCargo() const;

  //Name: GetCargoAt
  //Precondition: Requires that the ship's cargo has been populated
  //Postcondition: Templated accessor for this ship's cargo at a specific location
  const T& GetCargoAt(int index) const;

  //Name: AddCargo
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Adds an item into this ship
  void AddCargo(T inputObject);
  //Name: ToString
  //Precondition: Requires that the ships and cargo have been loaded
  //Postcondition: Used to output information about a specific ship
  string ToString() const;
  //Name: GetCapacity
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Used to access the capacity of a ship
  double GetCapacity() const;
  //Name: GetName
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Used to access the name of a ship
  string GetName() const;

  //Name: operator> (Overloaded) Both ships are templated!
  //Precondition: Requires two ships
  //Postcondition: Returns which ship heavier including cargo
  template <class U>
    bool operator>( Spaceship<U> &otherShip) ;

  //Name: operator< (Overloaded) Both ships are templated!
  //Precondition: Requires two ships
  //Postcondition: Returns which ship lighter including cargo
  template <class U>
  bool operator<( Spaceship<U> &otherShip) ;

private:
  string m_name;
  string m_type;
  double m_capacity;
  vector<T> m_cargo;	
};
//*************************************************************
//You need to implement all of this code - it is templated so we can't split the file

/*File: Spaceship.h
Project: CMSC 202 Project 5, Fall 2016
Author: Sepehr Hajbarat
Date: 12/10/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Spaceship.h, done in the .h file because a templated class cannot be split*/

//Spaceship default constructor
//Creates a Spaceship with no values for its variables
template <class T>
Spaceship<T>::Spaceship(){
  m_name = "";
  m_type = "";
  m_capacity = 0.0;
}

//Spaceship constructor
//Creates a spaceship and sets its variables to the parameters
template <class T>
Spaceship<T>::Spaceship(string inName, string inType, double inCapacity){
  m_name = inName;
  m_type = inType;
  m_capacity = inCapacity;
}

//GetCargo
//Requires the ship's cargo to be populated beforehand, and then returns a vector of the ship's cargo
template <class T>
vector<T> Spaceship<T>::GetCargo() const{
  return m_cargo;
}

//GetCargoAt
//Requires the ship's cargo to be populated beforehand, and then accesses the cargo at a specific location
template <class T>
const T& Spaceship<T>::GetCargoAt(int index) const{
  return m_cargo.at(index);
}

//AddCargo
//Adds an item into this ship
template <class T>
void Spaceship<T>::AddCargo(T inputObject){
  //adds the object being passed into the m_cargo vector without checks, as that is done in another file
  m_cargo.push_back(inputObject);
}

//ToString
//outputs information about the ship as a single string
template <class T>
string Spaceship<T>::ToString() const{
  //variable to hold information about the weight of the current ship
  float weight = 0.0;

  //variable to allow for concactenation of strings and number type variables
  ostringstream stream;

  //for loop to iterate through the ship and add up the weight of the cargo components
  for(typename vector<T>::const_iterator it = m_cargo.begin(); it !=m_cargo.end(); ++it){
    weight += it->GetWeight();
  }

  //inserting all the information into a single variable as a string
  stream << "Ship Type: " << m_type << "\nShip Name: " << m_name << "\nTotal Weight: " << weight << "\nTotal Capacity: " << m_capacity << endl;

  //returning the single string with all the information
  return stream.str();
}

//GetCapacity
//returns capacity of the ship
template <class T>
double Spaceship<T>::GetCapacity() const{
  return m_capacity;
}

//GetName
//returns name of the ship
template <class T>
string Spaceship<T>::GetName() const{
  return m_name;
}

//operator >
//returns which ship is heavier including the cargo
template<class T> template<class U> 
bool Spaceship<T>::operator> ( Spaceship<U> &otherShip){
  //two float variables to hold the weight of each ship
  float weight1 = 0.0;
  float weight2 = 0.0;
  
  //calculates weight of ship on left hand side by iterating through its cargo and adding up the weight of each
  for(typename vector<T>::const_iterator it = m_cargo.begin(); it !=m_cargo.end(); ++it){
    weight1 += it->GetWeight();
  }
  
  //calculates weight of ship on right hand side by iterating through its cargo and adding up the weight of each
  for(typename vector<U>::const_iterator it = otherShip.GetCargo().begin(); it !=otherShip.GetCargo().end(); ++it){
    weight2 += it->GetWeight();
  }

  //checks to see if the ship on the left hand side of the operator is heavier than the right hand side and returns true or false respectively
  if(weight1 > weight2)
    return true;
  else
    return false;
}

//operator <
//returns which ship is lighter including the cargo
template <class T> template <class U>
bool Spaceship<T>::operator<( Spaceship<U> &otherShip){
  //two float variables to hold the weight of each ship 
  float weight1 = 0.0;
  float weight2 = 0.0;

  //calculates weight of ship on left hand side by iterating through its cargo and adding up the weight of each
  for(typename vector<T>::const_iterator it = m_cargo.begin(); it !=m_cargo.end(); ++it){
    weight1 += it->GetWeight();
  }

  //calculates weight of ship on right hand side by iterating through its cargo and adding up the weight of each
  for(typename vector<U>::const_iterator it = otherShip.GetCargo().begin(); it !=otherShip.GetCargo().end(); ++it){
    weight2 += it->GetWeight();
  }

  //checks to see if the ship on the left hand side of the operator is lighter than the right hand side and returns true or false respectively
  if(weight1 < weight2)
    return true;
  else
    return false;
}

#endif
