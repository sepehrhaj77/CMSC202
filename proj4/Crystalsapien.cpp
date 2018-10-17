/*File: Crystalsapien.cpp
Project: CMSC 202 Project 4, Fall 2016
Author: Sepehr Hajbarat
Date: 11/28/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for Crystalsapien.h*/

#include "Crystalsapien.h"
#include "Monster.h"
#include <cstdlib>
using namespace std;

//Attack
//normal attack for Crystalsapien (copy pasted from Ben.cpp), reducing life of target
void Crystalsapien::Attack(Monster* &target){
  cout << m_name << " attacks using his " << m_nameNormal << " attack." << endl;
  double successHit = rand() % 100 + 1; //variable to see if the attack successfully hits

  //if attack is successful
  if(successHit > m_missPercent){
    int damage = rand() % (m_maxDamageNormal + 1 - m_minDamageNormal) + m_minDamageNormal; //random amount of damage for normal attack
    int newHealth = target->GetLife() - damage; //new health value to be set for monster
    target->SetLife(newHealth);
    cout << m_name << " did " << damage << " to " << target->GetName() << "." << endl;
  }

  //if he misses
  else
    cout << m_name << " missed his attack!" << endl;  
}

//Special Attack
//Execute's Crystalsapien's special attack, reducing life of target monster by amount of m_damageSpecial
void Crystalsapien::SpecialAttack(Monster* &target){
  //if Crystal Sapien does not have any special attacks
  if(m_usedSpecial >= m_maxSpecial)
    cout << m_name << " is out of special attacks! " << target->GetName() << " retaliates!" << endl;

  //if he still has special attacks
  else{
    int newHealth = target->GetLife() - m_damageSpecial; //new health value to be set for monster
    target->SetLife(newHealth);
    cout << m_name << " attacks using his " << m_nameSpecial << " attack." << endl;
    cout << m_name << " did " << m_damageSpecial << " to " << target->GetName() << "." << endl;
    //increments his amount of used special attacks to know if he has run out of them for later
    m_usedSpecial += 1;
  }
}

//Ultimate Attack
//Execute Crystalsapien's ultimate attack
void Crystalsapien::UltimateAttack(Monster* &target){
  int damage = 10*m_damageSpecial; //variable to calculate ultimate attack damage by multiplying special attack damage by 10
  int newHealth = target->GetLife() - damage; //new health value to be set for monster
  target->SetLife(newHealth);
  cout << m_name << " attacks using **ULTIMATE** ATTACK!!" << endl;
  cout << m_name << " did " << damage << " to " << target->GetName() << endl;
}
