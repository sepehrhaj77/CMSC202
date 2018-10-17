/*File: Item.cpp
Project: CMSC 202 Project 5, Fall 2016
Author: Sepehr Hajbarat
Date: 12/10/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Item.h*/
#include "Item.h"
using namespace std;

//Item default constructor
//Creates an item with no values for their variables
Item::Item(){
  m_id = 0;
  m_name = "";
  m_weight = 0.0;
}

//Item constructor
//Creates an Item and sets its variables to the parameters
Item::Item(int inId, string inName, float inWeight){
  m_id = inId;
  m_name = inName;
  m_weight = inWeight;
}

//GetID
//returns the ID of the item
int Item::GetId() const{
  return m_id;
}

//GetName
//returns the name of the item
string Item::GetName() const{
  return m_name;
}

//GetWeight
//returns the weight of the item
float Item::GetWeight() const{
  return m_weight;
}

//ToString
//creates a single string for output using an Item object
string Item::ToString() const{
  //variable to hold concactenated string which adds numbers as well
  ostringstream stream;
  //adds all the info to the stream, to make it one long string with non-string data types
  stream << "Item Name: " << m_name << "\nID: " << m_id << "\nWeight: " << m_weight;
  //returns the single stream which holds all the information 
  return stream.str();
}

