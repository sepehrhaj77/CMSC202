/*File: Game.cpp
Project: CMSC 202 Project 4, Fall 2016
Author: Sepehr Hajbarat
Date: 11/28/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Game.h
It runs the entire game, creating objects as needed and handling battles and other game aspects*/
#include "Game.h"
using namespace std;

//Game constructor
//Sets the number of levels based on user input, initializes the monsters, and all forms of Ben
Game::Game(){
  //a variable to hold how many levels there will be in the game
  m_levels = NumLevels();

  //Sets current level to 1
  m_level = 1;

  //Starts off by making Ben only have one form available
  m_formsBen = 1;

  //initializes monsters
  InitMonsters();

  //initializes forms of Ben
  InitBen();

  //Starts the game with Ben at 100 life
  Start(100);
}

//Game Destructor
//Deallocates all monsters created and all forms of Ben
Game::~Game(){
  //deallocates all Monsters
  for(unsigned int i=0; i < static_cast<unsigned int>(m_levels); i++){
    delete m_mons[i];
  }
  delete[] m_mons;

  //deallocates all forms of Ben
  for(unsigned int j=0; j < static_cast<unsigned int>(3); j++){
    delete m_ben[j];
  }
  delete[] m_ben;
}

//Init Monsters
//initializes all the monsters required for the game (based on how many max levels there are)
void Game::InitMonsters(){
  //initializing m_mons to hold one monster for each level there will be in the game
  m_mons = new Monster *[m_levels];

  //populates each index of m_mons with a random Monster pointer
  for(unsigned int i=1; i <= static_cast<unsigned int>(m_levels); i++)
    m_mons[i-1] = new Monster(i);
}

//Init Ben
//initializes all forms of Ben
void Game::InitBen(){
  //initializaing m_ben to hold all the forms of Ben
  m_ben = new Ben *[3];

  //making variables for all the stats of Pyro
  string pyroNorm = "fire";
  string pyroSpecial = "flamer";
  double pyroDef = 0.0;
  double pyroMiss = 15.0;
  int pyroUsedSpecial = 0;
  int pyroMaxSpecial = 1;
  int pyroMinDam = 15;
  int pyroMaxDam = 20;
  int pyroDamSpec = 30;

  //making variables for all the stats of Crystalsapien
  string sapienNorm = "energy";
  string sapienSpecial = "laser";
  double sapienDef = 0.25;
  double sapienMiss = 25.0;
  int sapienUsedSpecial = 0;
  int sapienMaxSpecial = 1;
  int sapienMinDam = 25;
  int sapienMaxDam = 30;
  int sapienDamSpec = 10;

  //bens default stats are made in his default constructor
  m_ben[0] = new Ben("Ben", 100);

  //initializing Pyronites's stats
  m_ben[1] = new Pyronite("Pyronite", 100, pyroNorm, pyroSpecial, pyroDef, pyroMiss, pyroUsedSpecial, pyroMaxSpecial, pyroMinDam, pyroMaxDam, pyroDamSpec);

  //initializing Crystalsapien's stats
  m_ben[2] = new Crystalsapien("Crystalsapien", 100, sapienNorm, sapienSpecial, sapienDef, sapienMiss, sapienUsedSpecial, sapienMaxSpecial, sapienMinDam, sapienMaxDam, sapienDamSpec);
}

//Num Levels
//prompts user for number of levels between 1 and 20
int Game::NumLevels(){
  //the number of levels the user wants to play
  int numLevels; 

  //do while loop to validate input
  do{
    cout << "How many levels would you like to try?" << endl;
    cin >> numLevels;
    
    //validates user input for levels fewer than 1
    if(numLevels < 1)
      cout << "You should do at least one level!" << endl;

    //validates user input for levels greater than 20
    else if(numLevels > 20)
      cout << "You should do less than 20 levels!" << endl;

  }while(numLevels < 1 || numLevels > 20); //makes sure input is bettwen 1 and 20

  return numLevels;
}

//Set Ben
//sets Ben's current form based on user choice
void Game::SetBen(int startLife){
  //variable to store user input for which form of Ben they want to play with
  int benChoice;
  cout << "Select one from the available forms of Ben at level " << m_level << " are:" << endl;

  //for loop to display all forms of Ben currently available
  for(unsigned int i = 0; i < static_cast<unsigned int>(m_formsBen); i++){
   cout << i+1 << "." << m_ben[i]->GetName() << endl;
  }

  //do while loop to validate user input for choice of Ben's form
  do{
    cout << "What would you like to do?" << endl;

    //if level is 3+, ben has 3 options
    if(m_level >= 3)
      cout << "Enter 1 to 3:" << endl;

    //otherwise his options are determine by whether he's on level 1 or 2
    else
      cout << "Enter 1 to " << m_level << ":" << endl;
    cin >> benChoice;

    //Error message to display if their input is invalid
    if(benChoice < 1 || benChoice > m_formsBen)
      cout << "Invalid input; please re-enter." << endl;
  }while(benChoice < 1 || benChoice > m_formsBen);

  //sets the current ben for the level to the user's choice
  m_currBen = m_ben[benChoice - 1];
  m_currBen->SetLife(startLife);

}

//Start
//Main driver of the game. May exit if Ben dies or wins the game
void Game::Start(int startLife){ 

  //checks to see if all levels have been defeated
  //each iteration of the while loop runs one level until it is over (Ben is dead or monster is dead)
  while(m_level <= m_levels){

      cout << "\t\t\t The game starts.... " << endl;
      cout << "\t\t\t LEVEL " << m_level << " of " << m_levels << endl;
      
      //Sets Ben to the form the user wants to use for that level
      SetBen(startLife);
      
      //Sets monster to the current level (m_level-1 because array index starts at 0, but level starts at 1)
      m_currMons = m_mons[m_level - 1];
      
      //displays the names and starting life values of Ben and the monster
      cout << "BEN: " << m_currBen->GetName() << endl;;
      cout << "MONSTER: " << m_currMons->GetName() << endl;
      cout << "The start life of " << m_currBen->GetName() << " is: " << m_currBen->GetLife() << endl;
      cout << "The start life of " << m_currMons->GetName() << " is: " << m_currMons->GetLife() << endl;
      
      //first battle of the level
      bool keepFighting = Input();
      
      //while loop to see if after the attacks either fighter is dead. Input will return false when one of them is dead 
      //If neither are dead, keeps having Ben and the mosnter attack each other
      while(keepFighting == true){
	keepFighting = Input();
      }
      
   //these next lines see who has died

      //if the monster died
      if(m_currMons->GetLife() <= 0){
	cout << "Congrats! " << m_currBen->GetName() << " won that level." << endl;

	//sets startLife to Ben's current health after battle for Ben's future battles
	startLife = m_currBen->GetLife();

	//increments the current level
	m_level++;

    //sees how many forms of Ben should now be available

	//if player will be going to level 2, gives Ben two forms, Ben and Pyronite
	if(m_level == 2)
	  m_formsBen = 2;

	//if player will be going to level 3 or higher, gives Ben three forms, Ben, Pyronite, and Crystalsapien
	else
	  m_formsBen = 3;
      }

      //if Ben died
      else{
	cout << "Game Over! Ben has been defeated..." << endl;
	return;
      }

      //states that Ben has won the game if all levels have been defeated
      if(m_level > m_levels){
	cout << "Congrats! You won the game." << endl;
      }
    
  }
}

//Input
//Controls the attacks between Ben and the monster. Returns true if after both attacks nobody dies
bool Game::Input(){
  //prints out Ben's current life and the monster's current life
  cout << m_currBen->GetName() << ": " << m_currBen->GetLife() << "\t" << m_currMons->GetName() << ": "
       << m_currMons->GetLife() << endl;

  //variable to store the user's choice for their choice of attack
  int attackChoice;
  //do while loop to validate user input to be between 1 and 3 for the menu options
  do{
    cout << "What would you like to do?" << endl;
    cout << "1. Normal Attack" << endl;
    cout << "2. Special Attack" << endl;
    cout << "3. Ultimate Attack" << endl;
    cout << "Enter 1 to 3: " << endl;

    //takes in the users choice into the variable attackChoice
    cin >> attackChoice;

    //error message to display if input is not valid
    if(attackChoice < 1 || attackChoice > 3)
      cout << "Invalid input; please re-enter." << endl;
  }while(attackChoice < 1 || attackChoice > 3);

  //decides which attack to initiate
  switch(attackChoice){

    //normal attack
  case 1:
    m_currBen->Attack(m_currMons);
    break;

    //special attack
  case 2:
    m_currBen->SpecialAttack(m_currMons);
    break;

    //ultimate attack
  case 3:
    m_currBen->UltimateAttack(m_currMons);
    break;
  }

  //checks to see if monster has died, if it has, false is returned and the battle is over
  if(m_currMons->GetLife() <= 0){
    return false;
  }

  //if monster is not dead, it retaliates
  else{
    m_currMons->Attack(m_currBen);

    //sees if Ben has died, if he has, false is returned and the battle is over
    if(m_currBen->GetLife() <= 0){
      return false;
    }
  }

  //if neither has died
  return true;
}
