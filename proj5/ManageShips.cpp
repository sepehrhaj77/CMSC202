/*File: ManageShips.cpp
Project: CMSC 202 Project 5, Fall 2016
Author: Sepehr Hajbarat
Date: 12/10/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for ManageShips.h*/
#include "ManageShips.h"
using namespace std;

//ManageShips
//used to manage all functions regarding ships after the data has been imported from 2 files
ManageShips::ManageShips(vector< Spaceship <Item> > itemShip, vector< Spaceship <Person> > personShip,
			 vector< Item > itemCargo, vector< Person > personCargo){
  m_itemShips = itemShip;
  m_personShips = personShip;
  m_items = itemCargo;
  m_person = personCargo;

  cout << "Item Ships Loaded: " << m_itemShips.size() << endl;
  cout << "Person Ships Loaded: " << m_personShips.size() << endl;
  cout << "Persons Loaded: " << personCargo.size() << endl;
  cout << "Items Loaded: " << itemCargo.size() << endl;
  LoadPersonShip();
  LoadItemShip();
}

//LoadItemShip
//loads items into each ship, but can not load more than the capacity of each ship
//all items may not be loaded
void ManageShips::LoadItemShip(){

  //for loop to go through each item and find which ship they fit in
  for(int i=0; i < m_items.size(); ++i){

    //for loop to go through each ship and find first available one
    for(unsigned int j=0; j < m_itemShips.size(); ++j){
      //variable to store weight of current ship
      float weight = 0.0;

      //for loop to calculate weight of current ship
      for(unsigned int k=0; k < m_itemShips.at(j).GetCargo().size(); ++k){
	weight += m_itemShips.at(j).GetCargoAt(k).GetWeight();
      }

      //checks to see if current item can be added without going over capacity
      if(m_items.at(i).GetWeight() + weight <= m_itemShips.at(j).GetCapacity()){
	//adds current item to the current ship
	m_itemShips.at(j).AddCargo(m_items.at(i));

	//erases current item from itemCargo for purposes of seeing which items were not added
	m_items.erase(m_items.begin() + i);

	//decrements i since we erased the added item
	--i;

	//stops checking ships for an available one
	break;
      }

    }

  }
}

//LoadPersonShip
//loads people into each ship, but can not load more people than the capcity for each ship
//all people may not be loaded
void ManageShips::LoadPersonShip(){
  //for loop to go through each ship and fill them with people until capacity
  for(unsigned int i=0; i < m_personShips.size(); ++i){
    //while loop to add people from personCargo until ship is full
    while(m_personShips.at(i).GetCargo().size() < m_personShips.at(i).GetCapacity()){
      //checks to make sure there is still someone to add to the ship
      if(!m_person.empty()){
	//adds the first person waiting to be loaded to the ship
	m_personShips.at(i).AddCargo(m_person.at(0));
	
	//deletes the person who was added for purposes of seeing who was not added to any ship
	m_person.erase(m_person.begin());
      }

      //if personCargo is empty, (no more people are left to add)
      else
	break;
    }
  }
}

//DisplayItemLeft
//prints out each item that has not been loaded to a ship
void ManageShips::DisplayItemLeft(){
  //if there are no unadded items
  if(m_items.empty())
    cout << "None" << endl;

  //if there are unadded items
  else{
    //for loop to go through the unadded item cargo and print each one out
    for(unsigned int i=0; i < m_items.size(); ++i)
      cout << "Item " << i << " - Name: " << m_items.at(i).GetName() << endl;
  }
}

//DisplayPersonLeft
//prints out each person that has not been loaded to a ship
void ManageShips::DisplayPersonLeft(){
  //if there are no unadded people
  if(m_person.empty())
    cout << "None" << endl;

  //if there are unadded people
  else{
    //for loop to go through the unadded people cargo and print each one out
    for(unsigned int i=0; i < m_person.size(); ++i)
      cout << "Person " << i+1 << " - Name: " << m_person.at(i).GetFName() << endl;
  }

}

//OutputShips
//writes out all the ships and their cargo to a specific output file, proj5_output.txt
void ManageShips::OutputShips(){
  fstream stream;
  const char OUTPUT[17] = "proj5_output.txt";
  stream.open(OUTPUT);
  
  stream << "**Personnel Ships**" << endl;

  //for loop to go through m_personShips and output each ship  
  for(unsigned int i=0; i < m_personShips.size(); ++i){
    stream << "**Ship Name: " << m_personShips.at(i).GetName() << "**" << endl;
    
    //if ship is empty
    if(m_personShips.at(i).GetCargo().empty())
      stream << "Empty" << endl;
    
    else{
      //for loop to print each person
      for(unsigned int j=0; j < m_personShips.at(i).GetCargo().size(); ++j){
	stream << m_personShips.at(i).GetCargoAt(j).GetFName() << " " 
	       << m_personShips.at(i).GetCargoAt(j).GetLName() << endl;
      } 
    }
    
  }  
  //for loop to go through m_itemShips and output each ship
  for(unsigned int i=0; i < m_itemShips.size(); ++i){
    stream << "**Ship Name: " << m_itemShips.at(i).GetName() << "**" << endl;
    
    //if ship is empty
    if(m_itemShips.at(i).GetCargo().empty())
      stream << "Empty" << endl;
    
    else{
      //for loop to print each item
      for(unsigned int j=0; j < m_itemShips.at(i).GetCargo().size(); ++j){
	stream << m_itemShips.at(i).GetCargoAt(j).GetName() << endl;
      }
    }
  }
  
  stream.close();
}

//GetHeaviestShip
//checks both item and person ships and prints out the heaviest ship
string ManageShips::GetHeaviestShip(){
  //variable to store heaviest person ship
  Spaceship<Person> maxP = m_personShips.at(0);

  //variable to store heaviest item ship
  Spaceship<Item> maxI = m_itemShips.at(0);

  //for loop to find heaviest person ship
  for(unsigned int i=1; i < m_personShips.size(); ++i){
    //if the current person ship is heavier than the heaviest person ship
    if(m_personShips.at(i) > maxP)
      maxP = m_personShips.at(i);
  }

  //for loop to find heaviest item ship
  for(unsigned int i=1; i < m_itemShips.size(); ++i){
    //if the current item ship is heavier than the heaviest item ship
    if(m_itemShips.at(i) > maxI)
      maxI = m_itemShips.at(i);
  }

  //if the heaviest person ship is heavier than the heaviest item ship
  if(maxP > maxI)
    return maxP.ToString();

  //if the opposite is true
  else
    return maxI.ToString();  
}

//GetLighestShip
//checks both item and person ships and prints out the lightest ship
string ManageShips::GetLightestShip(){
  //variable to store heaviest person ship
  Spaceship<Person> minP = m_personShips.at(0);

  //variable to store heaviest item ship
  Spaceship<Item> minI = m_itemShips.at(0);

  //for loop to find lightest person ship
  for(unsigned int i=1; i < m_personShips.size(); ++i){
    //if the current person ship is heavier than the heaviest person ship
    if(m_personShips.at(i) < minP)
      minP = m_personShips.at(i);
  }

  //for loop to find lightest item ship
  for(unsigned int i=1; i < m_itemShips.size(); ++i){
    //if the current item ship is heavier than the heaviest item ship
    if(m_itemShips.at(i) < minI)
      minI = m_itemShips.at(i);
  }

  //if the lightest person ship is lighter than the lightest item ship
  if(minP < minI)
    return minP.ToString();

  //if the opposite is true
  else
    return minI.ToString();
}

//GetLightestItem
//prints out the lightest item on a ship
string ManageShips::GetLightestItem(){
  //sets first item on first ship as lightest item
  Item lightest = m_itemShips.at(0).GetCargoAt(0);

  //variable to hold lighest weight, set to weight of first item on first ship
  double minWeight = lightest.GetWeight();

  //for loop to go through each item ship
  for(unsigned int i=0; i < m_itemShips.size(); ++i){
    //for loop to go through current ship and find lightest item
    for(unsigned int j=0; j < m_itemShips.at(i).GetCargo().size(); ++j){
      //if the current item is the lightest
      if(m_itemShips.at(i).GetCargoAt(j).GetWeight() < minWeight){
	lightest = m_itemShips.at(i).GetCargoAt(j);
	minWeight = lightest.GetWeight();
      }
    }
  }

  return lightest.ToString();
}

//GetHeaviestItem
//prints out the heaviest item on a ship
string ManageShips::GetHeaviestItem(){
  //sets first item on first ship as heaviest item
  Item heaviest = m_itemShips.at(0).GetCargoAt(0);

  //variable to hold heaviest weight, set to weight of first item on first ship
  double maxWeight = heaviest.GetWeight();

  //for loop to go through each item ship
  for(unsigned int i=0; i < m_itemShips.size(); ++i){
    //for loop to go through current ship and find heaviest item
    for(unsigned int j=0; j < m_itemShips.at(i).GetCargo().size(); ++j){
      //if the current item is the heaviest
      if(m_itemShips.at(i).GetCargoAt(j).GetWeight() > maxWeight){
        heaviest = m_itemShips.at(i).GetCargoAt(j);
        maxWeight = heaviest.GetWeight();
      }
    }
  }

  return heaviest.ToString();
}

//GetOldestPerson
//prints out the oldest person on a ship
string ManageShips::GetOldestPerson(){
  //sets first person on first ship as oldest
  Person oldest = m_personShips.at(0).GetCargoAt(0);

  //variable to hold highest age
  int maxAge = oldest.GetAge();

  //for loop to go through each person ship
  for(unsigned int i=0; i < m_personShips.size(); ++i){
    //for loop to go through current ship and find oldest person
    for(unsigned int j=0; j < m_personShips.at(i).GetCargo().size(); ++j){
      //if the current person is the oldest
      if(m_personShips.at(i).GetCargoAt(j).GetAge() > maxAge){
        oldest = m_personShips.at(i).GetCargoAt(j);
        maxAge = oldest.GetAge();
      }
    }
  }
  return oldest.ToString();
}

//GetYoungestPerson
//prints out the oldest person on a ship
string ManageShips::GetYoungestPerson(){
  //sets first person on first ship as youngest
  Person youngest = m_personShips.at(0).GetCargoAt(0);

  //variable to hold lowest age
  int minAge = youngest.GetAge();

  //for loop to go through each person ship
  for(unsigned int i=0; i < m_personShips.size(); ++i){
    //for loop to go through current ship and find youngest person
    for(unsigned int j=0; j < m_personShips.at(i).GetCargo().size(); ++j){
      //if the current person is the youngest
      if(m_personShips.at(i).GetCargoAt(j).GetAge() < minAge){
        youngest = m_personShips.at(i).GetCargoAt(j);
        minAge = youngest.GetAge();
      }
    }
  }
  return youngest.ToString();
}
