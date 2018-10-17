/*File: LinkedList.cpp
Project: CMSC 202 Project 3, Fall 2016
Author: Sepehr Hajbarat
Date: 10/22/16
Section 4
Email: sepehr1@umbc.edu
This file contains the implementation for LinkedList.h*/
#include "LinkedList.h"

LinkedList::LinkedList(){
  m_head = NULL;
  m_tail = NULL;
}

LinkedList::~LinkedList(){
  Clear();//calls clear() for desconstructor to prevent typing code twice
}

Node* LinkedList::CreateNode(int newInt, string newPayload){
  Node *newNode = new Node;
  //sets variables of the new node
  newNode->m_int = newInt;
  newNode->m_payload = newPayload;
  newNode->m_next = NULL;

  return newNode;
}

void LinkedList::InsertEnd(int newInt, string newPayload){
  Node *newNode = CreateNode(newInt, newPayload);
  //if list is empty, simply sets head to the new node
  if(IsEmpty()){
    m_head = newNode;
    m_tail = newNode;
  }
  //otherwise sets the current tails next node to the added node, and sets tail to the added node
  else{
    m_tail->m_next = newNode;
    m_tail = newNode;
  }
}

void LinkedList:: Display(){
  cout << "Payload of list are: " << endl;
  //traversing through the list with a for loop
  for(Node *current = m_head; current != NULL; current = current->m_next){
    cout << current->m_payload << "->";
    if(current->m_next == NULL)
      cout << "END" << endl;
  }
}

void LinkedList::Sort(){
  //sorting done by a bubble sort
  bool done = false;

  //do while loop that keeps starting the the beginning of the list until the list is in order
  do{
    Node *beforeCurrent = NULL;//keeps track of the node before the current one. NULL at beginning since m_head has nothing before it
    for(Node *current = m_head; current != NULL; current = current->m_next){
      if(current->m_next != NULL && current->m_int > current->m_next->m_int){//if the next node is not NULL, and is smaller than the current node
	if(current == m_head){//case where the current node is at the start (or the head)
	  Node *temp = current->m_next;
	  current->m_next = current->m_next->m_next;
	  temp->m_next = current;
	  current = temp;
	  m_head = current;
	}
	else{
	  Node *temp = current->m_next;
	  current->m_next = current->m_next->m_next;
	  temp->m_next = current;
	  current = temp;
	  beforeCurrent->m_next = temp;
	}
      }
      
      //decides how to increment beforeCurrent based on whether the iterator is currently at the head of the list or not
      if(current == m_head)
	beforeCurrent = m_head;
      else
	beforeCurrent = beforeCurrent->m_next;
     
    }
    done = true;

    //iterates through the list to see if it is sorted
    for(Node *current = m_head; current!= NULL; current = current->m_next){
      m_tail = current;
      //if anything is out of order the list is not done and must start from the beginning of the list again by re-entering the for loop above this one
      if(current->m_next != NULL && (current->m_int > current->m_next->m_int) )
	done = false;
    }
  }while(done == false);
}

bool LinkedList::IsEmpty(){
  if(m_head== NULL)
    return true;
  else
    return false;
}

LinkedList LinkedList::Decrypt(){
  LinkedList newList;
  Node *prev;
  //iterates through the existing list
  for(Node *i = m_head; i!= NULL; i = i->m_next){
    int num = i->m_int;
    string payload = i->m_payload;
    //the node is a perfect square
    if(IsPerfectSquare(num)){
      newList.InsertEnd(sqrt(num), payload);
    }
    //the node is a perfect cube
    else if(IsPerfectCube(num)){
      newList.InsertEnd(cbrt(num), payload);
    }
    prev = i;
  }
  return newList;
}

bool LinkedList::IsPerfectSquare(int n){
  //makes sure the number isnt a negative to avoid crashing
  if(n < 0)
    return false;
  int root = round(sqrt(n));//rounds the sqaure root to make it an int and disregard compiler precision issues
  return n == root * root;
}

bool LinkedList:: IsPerfectCube(int n){
  int root = round(cbrt(n));
  return n == root * root * root;
}

void LinkedList::Clear(){
  if(!IsEmpty()){
    Node *current = m_head;
    //deallocates the variables and then goes to the next node
    while(current != NULL){
      current->m_int = 0;
      current->m_payload = "";
      Node *nextNode = current->m_next;
      delete current;
      current = nextNode;
    }
  }
  m_head = NULL;
  m_tail = NULL;
}
