// File: proj1.cpp
// Project: CMSC 202 Project 1, Fall 2016
// Author: Sepehr Hajbarat
// Date: 9/21/2016
// Section 1, 6
// Email: sepehr1@umbc.edu
// This file contains the body information for project 1.
#include "proj1.h"
#include <fstream>

int main(){

  string fName, lName; //variables allowing for a new User Profile 
  double age, balance;

  const char FILE_NAME[15] = "proj1.txt";

  int start = menuStart(); //start menu option

  fstream profile; //variable to allow file reading 

  cout.setf(ios::fixed); //formats cout to display currency correctly
  cout.setf(ios::showpoint);
  cout.precision(2);

  //START MENU
  switch (start)
   {
   case 1:
     profile.open(FILE_NAME);
     profile >> fName >> lName >> age >> balance;
     profile.close();
     cout << "" << endl;
     break;
   case 2:
     cout << "Please enter the following: " << endl << "First Name: " << endl;
     cin >> fName;
     cout << "Last Name: " << endl;
     cin >> lName;
     cout << "Age: " << endl;
     cin >> age;
     cout << "Initial Deposit: " << endl;
     cin >> balance;
     cout << "$" << balance << " deposited" << endl;
     break;
   case 3: 
     cout << "Goodbye!" << endl;
     return 0;
     break;
   default: 
     cout << "That is not a valid option" << endl;
   }
  
  //MAIN MENU
  int mainMenu = menuMain(); //main menu option
  double amountTransac;
  string saveChoice;

  cout << "" << endl;

  while(mainMenu !=5){
    switch(mainMenu)
      {
      case 1:
	cout << "Account Balance: $" << balance << endl;
	break;
      case 2:
	cout << "Please enter the amount to be deposited" << endl;
	cin >> amountTransac;
	if(amountTransac >= 0){
	  balance += amountTransac;
	  cout << "$" << amountTransac << " deposited to your account" << endl;
	}
	else
	  cout << "Amount should be greater than 0" << endl;
	break;
      case 3:
	cout << "Please enter the amount to be withdrawn" << endl;
	cin >> amountTransac;
	if(amountTransac >= 0){
	  if(amountTransac > balance)
	    cout << "Amount withdrawn cannot be greater than balance" << endl;
	  else{
	    balance -= amountTransac;
	    cout << "$" << amountTransac << " withdrawn from your account." << endl;
	  }
	}
	else
	  cout << "Amount can not be less than 0" << endl;
	break;
      case 4:
	cout << "First Name: " << fName << endl;
	cout << "Last Name: " << lName << endl;
	cout << "Age: " << age << endl;
	cout << "Account Balance: $" << balance << endl;
	break;
      default: 
	cout << "That is not a valid option" << endl;
	break;
      }

    cout << "" << endl;
    cout << "********Please choose option from the menu********" << endl;
    cout << "1. Account Balance" << endl;
    cout << "2. Deposit money" << endl;
    cout << "3. Withdraw money" << endl;
    cout << "4. Display your account details" << endl;
    cout << "5. Exit" << endl << "Enter your choice: " << endl;
    cin >> mainMenu;
    cout << "" << endl;
  }
  
  cout << "Would you like to save your account information?:" << endl;
  cout << "yes or no" << endl;
  cin >> saveChoice;
  if(saveChoice == "yes"){
    profile.open(FILE_NAME);
    profile << fName << " " <<  lName << " " <<  age << " " << balance;
    profile.close();
    cout << "File Saved" << endl;
    cout << "Thank you for using the UMBC ATM" << endl;
  }
  else{
    cout << "Thank you for using the UMBC ATM" << endl;
  }

  return 0;
}

int menuStart(){
  int startOption;
  cout << "Welcome to the UMBC ATM" << endl << "Choose from below: " << endl;
  cout << "1. Load a User Profile from File" << endl << "2. Enter a new User Profile" << endl;
  cout << "3. Exit" << endl << "Enter your choice: " << endl;
  cin >> startOption;
  return startOption;
}

int menuMain(){
  int mainOption;
  cout << "********Please choose option from the menu********" << endl;
  cout << "1. Account Balance" << endl;
  cout << "2. Deposit money" << endl;
  cout << "3. Withdraw money" << endl;
  cout << "4. Display your account details" << endl;
  cout << "5. Exit" << endl << "Enter your choice: " << endl;
  cin >> mainOption;
  return mainOption;
}
