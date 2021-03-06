/*File: proj1.cpp
Project: CMSC 202 Project 2, Fall 2016
Author: Sepehr Hajbarat
Date: 10/11/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for project2*/
#include "proj2.h"

using namespace std;

int main(){
  vector<Pokemon> pokeDex;
  vector<MyPokemon> myCollection;
  
  getPokeDex(pokeDex);//fills pokeDex vector with all the pokemon in the pokeDex.txt file
  getMyCollection(myCollection);//fills myCollection vector with all the user's pokemon from myCollection.txt

  mainMenu(pokeDex, myCollection);

  return 0;
}

//creates a main menu that asks the user what they want to do
void mainMenu(vector <Pokemon> & pokeDex, vector<MyPokemon> &myCollection){
  int menuChoice;
  bool exit = 0;

  //menu options are displayed
  do{
    cout << "" << endl;
    cout << "What would you like to do?: " << endl;
    cout << "1. See the PokeDex" << endl;
    cout << "2. See your collection" << endl;
    cout << "3. Search for a new Pokemon" << endl;
    cout << "4. Battle your Pokemon" << endl;
    cout << "5. Train your Pokemon" << endl;
    cout << "6. Exit" << endl;
    
    //validates the users choice to be between 1 and 6
    do{
      cout << "Enter your choice: ";
      cin >> menuChoice;
      cout << "" << endl;
    }while(menuChoice < 1 || menuChoice > 6);
    
    //menu options
    switch(menuChoice){
    case 1://prints the pokeDex
      printPokeDex(pokeDex);
      break;
    case 2://prints the user's collection of Pokemon
      printMyCollection(myCollection);
      break;
    case 3://allows the user to catch a Pokemon
      catchPokemon(pokeDex, myCollection);
      break;
    case 4://allows the user to battle their Pokemon
      battlePokemon(pokeDex, myCollection);
      break;
    case 5://adds 10 CP to the pokemon of the user's choice
      trainPokemon(pokeDex, myCollection);
      break;
    case 6://saves the users collection and exits the menu
      exitPokemon(myCollection);
      exit = 1;
      break;
    }
  }while(exit == 0);
}

//loads all pokemon from a file into a vector pokeDex
void getPokeDex(vector <Pokemon> &pokeDex){
  fstream inputStream;
  inputStream.open(POKEDEX);

  int num, minCP, maxCP, rarity;
  string name;
  //loop to go through the pokeDex.txt file
  for(int i=0; i < POKECOUNT; i++){
    inputStream >> num >> name >> minCP >> maxCP >> rarity;
    Pokemon p(num, name, minCP, maxCP, rarity);
    pokeDex.push_back(p);
  }
  inputStream.close();
}

//loads all pokemon from a user file into a vector myCollection
void getMyCollection(vector<MyPokemon> & myCollection){
  fstream inputStream;
  inputStream.open(MYCOLLECTION);

  while(!inputStream.eof()){
    int num, CP, HP, rarity;
    string name;
    
    inputStream >> num >> name >> CP >> HP >> rarity;
    MyPokemon p(num, name, CP, HP, rarity);
    
    //checks to see if it has reached the end of the file before adding a Pokemon to the vector
    if(!inputStream.eof())
      myCollection.push_back(p);
    
  }
  inputStream.close();
}

//prints the pokemon in the pokeDex
void printPokeDex(vector <Pokemon> & pokeDex){
  for(int i=0; i<POKECOUNT; i++)
    cout << setw(5) << pokeDex.at(i).GetNum() << setw(15) << pokeDex.at(i).GetName() << endl;;
}

//print the pokemon in the users collection
void printMyCollection(vector <MyPokemon> & myCollection){
  int count = 0;
  for(unsigned int i=0; i<myCollection.size(); i++){
    cout << setw(3) << count << ". ";
    cout << setw(5) << myCollection.at(i).GetNum() << " ";
    cout << setw(15) << myCollection.at(i).GetName() << " ";
    cout << setw(5) << myCollection.at(i).GetCP() << " "; 
    cout << setw(5) << myCollection.at(i).GetHP() << " "; 
    cout << setw(3) << myCollection.at(i).GetRarity() << " " << endl;
    count++;
  }
}

//allows the user to try to catch a Pokemon
void catchPokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection){
  int rarity;
  do{//loop to verify the user picks a valid rarity for the pokemon they want to catch
    cout << "What type of Pokemon would you like to try and catch?:" << endl;
    cout << "1. Very Common (Very High Probability)" << endl;
    cout << "2. Common (High Probability)" << endl;
    cout << "3. Uncommon (Normal Probability)" << endl;
    cout << "4. Rare (Low Probability)" << endl;
    cout << "5. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> rarity;
    }while(rarity < 1 || rarity > 5);

  cout << "You start to search." << endl;

  int randNum=1; //variable to store randomly generated number
  srand(time(NULL));//seeds the randomizer with time to create a random probability of catching a Pokemon
  randNum = rand() % 100 + 1;//random number from 1-100
  switch(rarity){
  case 1://User selects very common
    if(randNum <= 65)
      foundPokemon(rarity, pokeDex, myCollection);
    else
      cout << "You were unsuccessful in finding a Pokemon" << endl;
    break;
  case 2://User selects common
    if(randNum <= 45)
      foundPokemon(rarity, pokeDex, myCollection);
    else
      cout << "You were unsuccessful in finding a Pokemon" << endl;
    break;
  case 3://User selects uncommon
    if(randNum <= 25)
      foundPokemon(rarity, pokeDex, myCollection);
    else
      cout << "You were unsuccessful in finding a Pokemon" << endl;
    break;
  case 4://User selects rare
    if(randNum <= 10)
      foundPokemon(rarity, pokeDex, myCollection);
    else
      cout << "You were unsuccessful in finding a Pokemon" << endl;
    break;
  case 5://User selects ultra rare
    if(randNum <= 1)
      foundPokemon(rarity, pokeDex, myCollection);
    else
      cout << "You were unsuccessful in finding a Pokemon" << endl;
    break;
  }
}

void foundPokemon(int rarity,vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection ){
  Pokemon p;
  int pokemonNum;
  srand(time(NULL));
  
  //keeps searching pokeDex until a random Pokemon with a matching rarity is found
  do{
    pokemonNum = rand() % 151;
  }while(pokeDex.at(pokemonNum).GetRarity() != rarity);
  p=pokeDex.at(pokemonNum);
  cout << "Congrats! You found a " << p.GetName();
  cout << "" << endl;

  //adds Pokemon to user's collection
  srand(time(NULL));
  int randCP = rand() % (p.GetCPMax() - p.GetCPMin() + 1) + p.GetCPMin();
  MyPokemon myP(p.GetNum(), p.GetName(), randCP, randCP / 10, rarity);
  myCollection.push_back(myP);
}


//saves the current user's collection to the myCollection.txt file
void saveMyCollection(vector<MyPokemon> & myCollection){
  fstream inputStream;
  inputStream.open(MYCOLLECTION);
  for(unsigned int i=0; i < myCollection.size(); i++){
    MyPokemon p = myCollection.at(i);
    inputStream << p.GetNum() << " " <<  p.GetName() << " " << p.GetCP() << " " << p.GetHP() << " " << p.GetRarity() << " " << endl;
  }
  inputStream.close();
}

//saves the users collection and lets them know the program is exiting
void exitPokemon(vector<MyPokemon> & myCollection){
  saveMyCollection(myCollection);
  cout << "File Saved" << endl;
  cout << "Thank you for playing Pokemon UMBC" << endl;
}

//adds 10 CP to the specified Pokemon
void trainPokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection){
  unsigned int pokeChoice;
  //makes sure the user has Pokemon before trying to train them
  if(myCollection.size() == 0){
    cout << "You do not have any Pokemon! Go catch some!" << endl;
    return;
  }
  
  //verifies a valid Pokemon is selected
    do{
      cout << "Which of your Pokemon would you like to use?: " << endl;
      printMyCollection(myCollection);
      cin >> pokeChoice;
    }while(pokeChoice < 0 || pokeChoice > myCollection.size());
  
    if( (myCollection.at(pokeChoice).GetCP() + 10) > pokeDex.at(myCollection.at(pokeChoice).GetNum() - 1).GetCPMax() ){
    cout << "Your pokemon is at the max CP! It can not train any further." << endl;
  }
  else{
    myCollection.at(pokeChoice).Train();
    cout << "Your " << myCollection.at(pokeChoice).GetName() << " trained." << endl;
    cout << "Your CP is now " << myCollection.at(pokeChoice).GetCP() << "." << endl;
  }
}

void battlePokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection){
  int pokeNumber;
  //makes sure the user has Pokemon before trying to train them
  if(myCollection.size() == 0){
    cout << "You do not have any Pokemon! Go catch some!" << endl;
    return;
  }
  srand(time(NULL));

  //randomly selects a Pokemon from the pokeDex
  pokeNumber = rand() % 151;
  Pokemon p1 = pokeDex.at(pokeNumber);
  
  //randomly sets the CP of the wild Pokemon to a value between its min and max CP values
  srand(time(NULL));
  int randCP = rand() % p1.GetCPMax() + p1.GetCPMin();
  p1.SetCP(randCP);

  unsigned int battleChoice;
  printMyCollection(myCollection);
  cout << "You are going to fight a " << p1.GetName() << endl;
  cout << "The enemy has a CP of " << p1.GetCPMax() << endl;

  //makes sure the user selects a valid Pokemon from their collection
  do{
    cout << "Which of your Pokemon would you like to use?: " << endl;
    cin >> battleChoice;
  }while(battleChoice < 0 || battleChoice > myCollection.size());
  
  //checks to see whether the user won or lost the battle
  MyPokemon p2 = myCollection.at(battleChoice);

  //if they won
  if(p2.GetCP() > p1.GetCPMax()){
    cout << "You won!!" << endl;
    return;
  }
  //if they lost
  else{
    cout << "You lost!!" << endl;
    return;
  }
}

