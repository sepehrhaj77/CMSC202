/*File: MyPokemon.cpp
Project: CMSC 202 Project 2, Fall 2016
Author: Sepehr Hajbarat
Date: 10/11/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for MyPokemon*/

#include "MyPokemon.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

//constructor without arguements
MyPokemon::MyPokemon(){
  m_Num = 1;
  m_Name = " ";
  m_CP = 1;
  m_HP = 1;
  m_Rarity = 1;
}

//constructor with arguments
MyPokemon::MyPokemon(int num, string name, int cp, int hp, int rarity){
  m_Num = num;
  m_Name = name;
  m_CP = cp;
  m_HP = hp;
  m_Rarity = rarity;
}

//returns cp
int MyPokemon::GetCP(){
  return m_CP;
}

//returns hp
int MyPokemon::GetHP(){
  return m_HP;
}

//returns rarity
int MyPokemon::GetRarity(){
  return m_Rarity;
}

//returns name
string MyPokemon::GetName(){
  return m_Name;
}

//returns number
int MyPokemon::GetNum(){
  return m_Num;
}

//sets rarity
void MyPokemon::SetRarity(int newRarity){
  m_Rarity = newRarity;
}

//sets name
void MyPokemon::SetName(string newName){
  m_Name = newName;
}

//sets cp
void MyPokemon::SetCP(int newCP){
  m_CP = newCP;
}

//sets hp
void MyPokemon::SetHP(int newHP){
  m_HP = newHP;
}

//adds 10 cp to the pokemon
void MyPokemon::Train(){
  m_CP += 10;
}