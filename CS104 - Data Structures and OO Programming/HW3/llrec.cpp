#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void moveThrough(Node*& input);

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
	if (larger != nullptr){
    if (larger == larger->next){
      larger = nullptr;
    }
  }
  if (smaller != nullptr){
    if (smaller == smaller->next){
      smaller = nullptr;
    }
  }

  if (head == nullptr){
    return;
  } else if (head->val <= pivot){
    if (smaller == nullptr){
      smaller = head;
      head = head->next;
      smaller->next = nullptr;
    } else {
      Node* temp = smaller;
      moveThrough(temp);
      temp->next = head;
      head = head->next;
      temp = temp->next;
      temp->next = nullptr;
    }
  } else {
    if (larger == nullptr){
      larger = head;
      head = head->next;
      larger->next = nullptr;
    } else {
      Node* temp = larger;
      moveThrough(temp);
      temp->next = head;
      head = head->next;
      temp = temp->next;
      temp->next = nullptr;
    }
  }

  llpivot(head, smaller, larger, pivot);
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