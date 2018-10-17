/*File: Ben.cpp
Project: CMSC 202 Project 4, Fall 2016
Author: Sepehr Hajbarat
Date: 11/28/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Ben.h*/
#include "Ben.h"
#include "Monster.h"
#include <cstdlib>

using namespace std;

//Ben constructor
//default constructor for Ben
Ben::Ben(string name, int life){
  m_name = name;
  m_life = life;
  m_nameNormal = "hand-to-hand";
  m_nameSpecial = "kick";
  m_defenseBonus = 0.0;
  m_missPercent = 10.0;
  m_usedSpecial = 0;
  m_minDamageNormal = 10;
  m_maxDamageNormal = 20;
  m_damageSpecial = 25;
  m_maxSpecial = 2;
}

//Ben overloaded constructor
//Creates a specific version of Ben, such as Pyronite or Crsytalsapien
Ben::Ben(string name, int life, string nameNorm, string nameSpecial, double defenseBonus, double missPercent, 
	 int usedSpecial, int maxSpecial, int minDamNorm, int maxDamNorm, int damSpec){
  m_name = name;
  m_life = life;
  m_nameNormal = nameNorm;
  m_nameSpecial = nameSpecial;
  m_defenseBonus = defenseBonus;
  m_missPercent = missPercent;
  m_usedSpecial = usedSpecial;
  m_maxSpecial = maxSpecial;
  m_minDamageNormal = minDamNorm;
  m_maxDamageNormal = maxDamNorm;
  m_damageSpecial = damSpec;
}

//Ben destructor
//Deallocates memory for Ben (there is nothing specific to be done here)
Ben::~Ben(){
}

//Set Life
//sets life of Ben to a new value
void Ben::SetLife(int life){
  m_life = life;
}

//Get Name
//returns name of Ben object
string Ben::GetName(){
  return m_name;
}

//Get Life
//returns current life value
int Ben::GetLife(){
  return m_life;
}

//Get Defense Bonus
//returns defense bonus (only Crystalsapien form will have a defense bonus)
double Ben::GetDefenseBonus(){
  return m_defenseBonus;
}

//Attack
//normal attack for any form of Ben, reducing life of target
void Ben:: Attack(Monster* &target){
  cout << m_name << " attacks using his " << m_nameNormal << " attack." << endl;
  double successHit = rand() % 100 + 1; //variable to see if the attack successfully hits

  //if attack is successful
  if(successHit > m_missPercent){
    int damage = rand() % (m_maxDamageNormal + 1 - m_minDamageNormal) + m_minDamageNormal; //random amount of damage for normal attack
    int newHealth = target->GetLife() - damage; //new health value to be set for monster
    target->SetLife(newHealth);//sets the monsters health to a new value after being hit
    cout << m_name << " did " << damage << " to " << target->GetName() << "." << endl;
  }

  //otherwise
  else
    cout << m_name << " missed his attack!" << endl;
}

//Special Attack
//executes Ben's current form's special attack, reducing life of target
void Ben::SpecialAttack(Monster *&target){
  //if Ben does not have any special attacks
  if(m_usedSpecial >= m_maxSpecial)
    cout << m_name << " is out of special attacks! " << target->GetName() << " retaliates!" << endl;

  //executes Ben's special attack if he has one
  else{
    int newHealth = target->GetLife() - m_damageSpecial; //new health value to be set for monster
    target->SetLife(newHealth);
    cout << m_name << " attacks using his " << m_nameSpecial << " attack." << endl;
    cout << m_name << " did " << m_damageSpecial << " to " << target->GetName() << "." << endl;
    //increments his amount of used special attacks to know if he has run out of them for later
    m_usedSpecial += 1;
  }
}

//Ultimate Attack (only Crystalsapien can actually implement this method)
//displays that ben has no ultimate attack, since only Crystal Sapien does
void Ben::UltimateAttack(Monster *&target){
  cout << m_name << " has no ultimate attack! " << target->GetName() << " retaliates!" << endl;
}
