/*File: ReadySupply.cpp
Project: CMSC 202 Project 5, Fall 2016
Author: Sepehr Hajbarat
Date: 12/10/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for ReadySupply.h*/
#include "ReadySupply.h"
using namespace std;

//ReadySupply default constructor
//default constructor in case no arguments are passed. Sets file names to blank
ReadySupply::ReadySupply(){
  m_shipFile = "";
  m_cargoFile = "";
}

//ReadySupply constructor
//populates two spaceship vectors based on ship file and cargo file passed in parameters
ReadySupply::ReadySupply(string shipFile, string cargoFile){
  m_shipFile = shipFile;
  m_cargoFile = cargoFile;
  LoadShips();
  LoadCargo();
}

//LoadShips
//builds a vector for people ships and a vector for cargo ships
void ReadySupply::LoadShips(){
  //turns file name into c-string to be able to be read by stream
  const char *SHIPS = m_shipFile.c_str();

  //creates a stream to read in the file
  fstream stream;

  //variables to hold information of ship
  string typeShip;
  string name;
  double capacity;

  //opens and reads shipFile first
  stream.open(SHIPS);

  //reads file until it reaches the end
  while(!stream.eof()){
    //reads in the data
    stream >> typeShip >> name >> capacity;
    
    //checks to see if it has reached the end of the file before creating a ship
    if(!stream.eof()){      
      //if spaceship is item type in the file
      if(typeShip == "Item"){
	//creates a new spaceship of type Item and pushes it into m_itemShips
	Spaceship<Item> s(name, typeShip, capacity);
	m_itemShips.push_back(s);
      }
      
      //if spaceship is person type in the file
      else{
	//creates a new spaceship of type Person and pushes it into m_personShips
	Spaceship<Person> p(name, typeShip, capacity);
	m_personShips.push_back(p);
      }
    }
  }

  //closes the stream
  stream.close();
}

//LoadCargo
//builds a vector for person cargos and item cargos
void ReadySupply::LoadCargo(){
  //turns file name into c-string to be able to be read by stream
  //  const char CARGO[16] = m_cargoFile;
  const char *CARGO = m_cargoFile.c_str();
  //creates a stream to read in the file
  fstream stream;

  //variables to hold information of cargo 
  string type;
  int id;
  string itemName;
  float itemWeight;

  //person specific variables
  string fName;
  string lName;
  double personWeight;
  int age;

  //opens and reads cargoFile next
  stream.open(CARGO);

  //reads file until it reachs the end
  while(!stream.eof()){
    //reads in the type
    stream >> type;

    //sees if the type is an item, and reads in information accordingly
    if(type == "i"){
      //stores the item's info into appropriate variables
      stream >> id >> itemName >> itemWeight;

      //checks to see if it has reached the end of the file before creating an item
      if(!stream.eof()){
	//creates an item and pushes it into the vector m_itemCargo
	Item i(id, itemName, itemWeight);
	m_itemCargo.push_back(i);
      }
    }

    //if the type is a person, read in information accordingly
    else{
      //stores the person's info into appropriate variables
      stream >> fName >> lName >> personWeight >> age >> id;

      //checks to see if it has reached the end of the file before creating a person
      if(!stream.eof()){	
	//creates a person and pushes it into the vector m_personCargo
	Person p(fName, lName, personWeight, age, id);
	m_personCargo.push_back(p);
      }
    }
  }

  //closes the stream
  stream.close();   
}

//GetItemShips
//returns a vector of all the item ships
vector< Spaceship<Item> > ReadySupply::GetItemShips(){
 return m_itemShips;
}

//GetPersonShips
//returns a vector of all the person ships
vector< Spaceship<Person> > ReadySupply::GetPersonShips(){
  return m_personShips;
}

//GetItemCargo
//returns a vector of all the items
vector< Item > ReadySupply::GetItemCargo(){
  return m_itemCargo;
}

//GetPersonCargo()
//returns a vector of all the people
vector< Person > ReadySupply::GetPersonCargo(){
  return m_personCargo;
}
