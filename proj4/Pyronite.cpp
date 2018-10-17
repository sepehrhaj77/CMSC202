/*File: Pyronite.cpp
Project: CMSC 202 Project 4, Fall 2016
Author: Sepehr Hajbarat
Date: 11/28/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Pyronite.h*/

#include "Pyronite.h"
#include "Monster.h"
#include <cstdlib>
using namespace std;

//Attack
//normal attack for Pyronite (copy pasted from Ben.cpp), reducing life of target
void Pyronite::Attack(Monster* &target){
  cout << m_name << " attacks using his " << m_nameNormal << " attack." << endl;
  double successHit = rand() % 100 + 1; //variable to see if the attack successfully hits

  //if attack is successful
  if(successHit > m_missPercent){
    int damage = rand() % (m_maxDamageNormal + 1 - m_minDamageNormal) + m_minDamageNormal; //random amount of damage for normal attack
    int newHealth = target->GetLife() - damage; //new health value to be set for monster
    target->SetLife(newHealth);
    cout << m_name << " did " << damage << " to " << target->GetName() << "." << endl;
  }
  //otherwise
  else
    cout << m_name << " missed his attack!" << endl;
}

//Special Attack
//executes Pyronite's special attack, reducing the life of the target
void Pyronite::SpecialAttack(Monster *&target){
  //if Pyronite does not have any special attacks
  if(m_usedSpecial >= m_maxSpecial)
    cout << m_name << " is out of special attacks! " << target->GetName() << " retaliates!" << endl;
  //if attack is successful 
  else{
    int newHealth = target->GetLife() - m_damageSpecial; //new health value to be set for monster
    target->SetLife(newHealth);
    cout << m_name << " attacks using his " << m_nameSpecial << " attack." << endl;
    cout << m_name << " did " << m_damageSpecial << " to " << target->GetName() << "." << endl;
    //increments his amount of used special attacks to know if he has run out of them for later
    m_usedSpecial += 1;
  }
}
