/*File: proj3.cpp
Project: CMSC 202 Project 3, Fall 2016
Author: Sepehr Hajbarat
Date: 10/22/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for project3.h*/
#include "LinkedList.h"
#include "proj3.h"

int main () {
  LinkedList list;
  mainMenu(list);
  return 0;
}

void readFile(LinkedList &list){
  fstream iStream;
  char FILENAME[12];
  int num;
  string payload;

  //if no file has been loaded yet
  if(list.IsEmpty()){
    cout << "What is the file name?: " << endl;
    cin >> FILENAME;
    iStream.open(FILENAME);
    //sees if file succesffuly opened
    if(iStream.is_open()){
      while(!iStream.eof()){//reads file until it reached the end
	iStream >> num >> payload;
	//checks to see if it has reached the end of the file before adding a Node
	if(!iStream.eof())
	  list.InsertEnd(num, payload);
      }
      cout << "New message loaded" << endl;
      iStream.close();
    }
    //if file could not be opened
    else{
      cout << "Message load failed " << endl;
      iStream.close();
    }
  }
  //if a file has already been loaded
  else{
    int choice = 0;
    do{
      cout << "Do you want to: " << endl;
      cout << "1. Overwrite the message" << endl;
      cout << "2. Append the message" << endl;
      cout << "3. Cancel" << endl;
      cin >> choice;
    }while(choice < 1 || choice >3);
    
    switch(choice){
    case 1://overwriting the message
      list.Clear();
      cout << "Previous message cleared" << endl;
      cout << "What is the file name?: " << endl;
      cin >> FILENAME;
      iStream.open(FILENAME);
      //sees if file succesffuly opened
      if(iStream.is_open()){
	while(!iStream.eof()){//reads file until it reached the end
	  iStream >> num >> payload;
	  //checks to see if it has reached the end of the file before adding a Node
	  if(!iStream.eof())
	    list.InsertEnd(num, payload);
	}
	cout << "New message loaded" << endl;
	iStream.close();
      }
      //if file could not be opened
      else{
	cout << "Message load failed " << endl;
	iStream.close();
      }
      break;
    case 2://appending the message
      cout << "What is the file name?: " << endl;
      cin >> FILENAME;
      iStream.open(FILENAME);
      //sees if file succesffuly opened
      if(iStream.is_open()){
	while(!iStream.eof()){//reads file until it reached the end
	  iStream >> num >> payload;
	  //checks to see if it has reached the end of the file before adding a Node
	  if(!iStream.eof())
	    list.InsertEnd(num, payload);
	}
	cout << "New message loaded" << endl;
	iStream.close();
      }
      //if file could not be opened
      else{
	cout << "Message load failed" << endl;
	iStream.close();
      }
      break;
    case 3://doing neither, and cancelling
      cout << "Cancelled" << endl;
      break;
    }
  }
}

void mainMenu(LinkedList &list){
  int option = 0;
  bool isExit = 0;
  do {
    do {
      cout << "What would you like to do?: " << endl;
      cout << "1. Load a new encrypted message" << endl;
      cout << "2. Display a raw message" << endl;
      cout << "3. Display an encrypted message" << endl;
      cout << "4. Exit" << endl;
      cin >> option;
    }while(option < 1 || option > 4);

    switch(option){
    case 1://reads in a text file
      readFile(list);
      break;
    case 2://displays a unsorted message, sorts it, and displays it again
      displayMessage(list);
      break;
    case 3://decrypts a message, sorts it, and then displays it
      displayEncrypt(list);
      break;
    case 4://exits the program
      exitLinked(list);
      isExit = 1;
    }
  }while(isExit == 0);
}

void displayMessage(LinkedList &list){
  //if the list contains nodes
  if(!list.IsEmpty()){
    list.Display();
    list.Sort();
    list.Display();
  }
  else
    cout << "You haven't loaded an encrypted message yet" << endl;
}

void exitLinked(LinkedList &list){
  list.Clear();
  cout << "Have a nice day!" << endl;
}

void displayEncrypt(LinkedList &list){
  if(!list.IsEmpty()){
    LinkedList list2 = list.Decrypt();
    list2.Sort();
    list2.Display();
  }
  else
    cout << "You haven't loaded an encrypted message yet" << endl;
}
