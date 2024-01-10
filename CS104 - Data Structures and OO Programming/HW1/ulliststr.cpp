#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>

using namespace std;

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if ((loc < 0) ||(loc > size_)){
    return NULL;
  }

  unsigned int index = 0;
  Item* temp = head_;
  int fir = temp->first;
  int las = temp->last;
  while (index < loc){
    while (fir < las){
      if (index == loc){
        break;
      }
      fir++;
      index++;
    }
    if (fir == las){
      temp = temp->next;
      fir = temp->first;
      las = temp->last;
    }
  }

  std::string* ans = &(temp->val[fir]);
  return ans;
}

std::string const & ULListStr::back() const{
  std::string* ans = getValAtLoc(size_-1);
  return* ans;
}

std::string const & ULListStr::front() const{
  std::string* ans = getValAtLoc(0);
  return* ans;
}

void ULListStr::push_back(const std::string& val){
  Item* temp = head_;
  
  if(temp != NULL){
    while(temp->next != NULL){
      temp = temp->next;
    }
    int las = temp->last;
    if (las != ARRSIZE){
      temp->val[las] = val;
      las++;
      temp->last = las;
    }
    else {
      Item* next = new Item;
      next->first = 0;
      next->last = 1;
      next->val[0] = val;
      next->next = NULL;

      Item* fin = head_;
      while(fin->next != NULL){
        fin = fin->next;
      }
      fin->next = next;
      next->prev = fin;
      tail_ = next;
    }
  } else {
    Item* next = new Item;
    next->first = 0;
    next->last = 1;
    next->val[0] = val;
    next->next = NULL;
    next->prev = NULL;
    tail_ = next;
    head_ = next;
  }
  size_++;
}

void ULListStr::pop_back(){
  Item* temp = tail_;
  int fir = temp->first;
  int las = temp->last;

  if (fir != las-1){
		las--;
		temp->last = las;
  }
  else {
    if (head_ == tail_){
			delete tail_;
      head_ = NULL;
      tail_ = NULL;
    } else {
      Item *temp = tail_->prev;
      delete tail_;
      tail_ = temp;
			tail_->next = NULL;
    }
  }
  size_--;
}

void ULListStr::push_front(const std::string& val){
  if (head_ != NULL){
    int fir = head_->first;
    if (fir != 0){
      fir--;
      head_->val[fir] = val;
      head_->first = fir;
    } else {
      Item* before = new Item;
      before->last = ARRSIZE;
      before->first = ARRSIZE-1;
      before->val[ARRSIZE-1] = val;
      before->prev = NULL;
      Item* beg = tail_;
      while(beg->prev != NULL){
        beg = beg->prev;
      }
      beg->prev = before;
      before->next = beg;
      head_ = before;
    }
  } else {
    Item* next = new Item;
    next->first = ARRSIZE-1;
    next->last = ARRSIZE;
    next->val[ARRSIZE-1] = val;
    next->next = NULL;
    next->prev = NULL;
    tail_ = next;
    head_ = next;
  }
  size_++;
}

void ULListStr::pop_front(){
  unsigned int val = head_->first;
  if (val != head_->last-1){
    val++;
    head_->first = val;
  } else {
    if (head_ == tail_){
      delete tail_;
      head_ = NULL;
      tail_ = NULL;
    } else {
      Item *temp = head_->next;
      delete head_;
      head_ = temp;
			head_->prev = NULL;
    }
  }
  size_--;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
