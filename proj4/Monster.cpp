/*File: Monster.cpp
Project: CMSC 202 Project 4, Fall 2016
Author: Sepehr Hajbarat
Date: 11/28/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Monster.h*/

#include "Monster.h"
#include <cmath>

using namespace std;

//Monster constructor
//Instantiates a monster with stats appropriate to the current level which is passes as a parameter. 
//Name is randomly chosen from a .txt file with 29 different names
Monster::Monster(int level){
  m_name = SummonMonster();
  
  //sets appropriate stats for current level
  if(level == 1){
    m_life = rand() % 31 + 20; //random life value from 20-50
    m_attack = rand() % 5 + 1; //random damage value from 1-5
  }
  else if(level == 2){
    m_life = rand() % 31 + 30; // 30-60
    m_attack = rand() % 8 + 3; // 3-10
  }
  else{
    m_life = rand() % 31 + 40; // 40-70
    m_attack = rand() % 11 + 5; // 5-15
  }
}

//Monster destructor
//Doesn't do anything as nothing is created dynamically
Monster::~Monster(){
  
}

//Summon Monster
//randomly chooses a name for the monster to be fought against
string Monster::SummonMonster(){
  LoadMonster();
  int num = rand() % 29; //random number from 0 to 28
  return m_monster.at(num);
}

//Load Monster
//loads all the monster names from the monster.txt file into a vector
void Monster::LoadMonster(){
  fstream stream;
  string name;

  //converting monster.txt into a c-string
  const char MONSTER[12] = "monster.txt";
  
  //reads in file and opens it
  stream.open(MONSTER);

  //makes sure file opened successfully
  if(stream.is_open()){
    while( getline(stream, name) ){//reads file until it reaches the end
      m_monster.push_back(name);//adds the random monster name to the game
    }
  }

  //closes stream
  stream.close();
}

//Attack
//executes monster's attack and reduces Ben's life
void Monster::Attack(Ben* &target){
  cout << m_name << " attacks " << target->GetName() << " using a normal attack." << endl;

  //accounts for defense bonus of Ben
  int actualDamage = round(static_cast<double>(m_attack) * (1.0 - target->GetDefenseBonus()) );

  //new health value of Ben after being attacked
  int newHealth = target->GetLife() - actualDamage;
  target->SetLife(newHealth);
  cout << m_name << " did " << actualDamage << " to " << target->GetName() << "." << endl;
}

//Set Life
//sets life of monster to a new value (used after Ben attacks the monster)
void Monster::SetLife(int life){
  m_life = life;
}

//Get Life
//returns life value of monster
int Monster::GetLife(){
  return m_life;
}

//Get Name
//returns name of monster
string Monster::GetName(){
  return m_name;
}
