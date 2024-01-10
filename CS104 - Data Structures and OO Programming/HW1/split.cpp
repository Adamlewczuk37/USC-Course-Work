/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

void moveThrough(Node*& input);

void split(Node*& in, Node*& odds, Node*& evens)
{
  if (in == nullptr){
    return;
  } else if (in->value % 2 == 0){
    if (evens == nullptr){
      evens = in;
      in = in->next;
      evens->next = nullptr;
    } else {
      Node* temp = evens;
      moveThrough(temp);
      temp->next = in;
      in = in->next;
      temp = temp->next;
      temp->next = nullptr;
    }
  } else {
    if (odds == nullptr){
      odds = in;
      in = in->next;
      odds->next = nullptr;
    } else {
      Node* temp = odds;
      moveThrough(temp);
      temp->next = in;
      in = in->next;
      temp = temp->next;
      temp->next = nullptr;
    }
  }

  split(in, odds, evens);
}


void moveThrough(Node*& input)
{
  if (input->next == nullptr){
    return;
  } else {
    input = input->next;
    moveThrough(input);
  }
}