/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/
#include <vector>
#include <limits>
#include <cstdlib>
#include <iostream>
#include <map>

#include "split.h"
using namespace std;

Node * makeList(std::vector<int> const & content)
{
	Node * head = nullptr;

	if(!content.empty())
	{
		// create head
		head = new Node(content[0], nullptr);

		// create rest of list
		Node * currTail = head;
		std::vector<int>::const_iterator nextValIter(content.cbegin());
		++nextValIter;

		for(; nextValIter != content.cend(); ++nextValIter)
		{
			Node * newNode = new Node(*nextValIter, nullptr);
			currTail->next = newNode;

			currTail = newNode;
		}
	}

	return head;

}

void deleteList(Node * list)
{
	Node * currElement = list;

	while(currElement != nullptr)
	{
		Node * nextElement = currElement->next;

		delete currElement;

		currElement = nextElement;
	}
}


int main(int argc, char* argv[])
{
  cout << "Test 1: Empty List" << endl;
	Node* list = nullptr;
	Node* odds = nullptr;
	Node* evens = nullptr;
	split(list, odds, evens);
	if ((odds == nullptr) && (evens == nullptr)){
		cout << "Test 1 passed!" << endl;
	} else {
		cout << "Test 1 failed: either evens or odds not = nullptr..." << endl;
	}

	cout << "Test 2: Single Even" << endl;
	Node* list2 = makeList({8});
	Node* odds2 = nullptr;
	Node* evens2 = nullptr;
	split(list2, odds2, evens2);
	if (evens2->value == 8){
		cout << "Test 2 passed!" << endl;
	} else {
		cout << "Test 2 failed: evens->value = " << evens2->value << endl;
	}
	deleteList(odds2);
	deleteList(evens2);

	cout << "Test 3: Single Odd" << endl;
	Node* list3 = makeList({5});
	Node* odds3 = nullptr;
	Node* evens3 = nullptr;
	split(list3, odds3, evens3);
	if (odds3->value == 5){
		cout << "Test 3 passed!" << endl;
	} else {
		cout << "Test 3 failed: evens->value = " << odds3->value << endl;
	}
	deleteList(odds3);
	deleteList(evens3);

	cout << "Test 4: Multi Evens" << endl;
	Node* list4 = makeList({0,8});
	Node* odds4 = nullptr;
	Node* evens4 = nullptr;
	split(list4, odds4, evens4);
	if (evens4->value == 0){
		evens4 = evens4->next;
		if (evens4->value == 8){
			cout << "Test 4 passed!" << endl;
		} else {
			cout << "Test 4 failed: evens 2nd value = " << evens4->value << endl;
		}
	} else {
		cout << "Test 4 failed: evens->value = " << evens4->value << endl;
	}
	deleteList(odds4);
	deleteList(evens4);

	cout << "Test 5: Multi Odds" << endl;
	Node* list5 = makeList({1,19});
	Node* odds5 = nullptr;
	Node* evens5 = nullptr;
	split(list5, odds5, evens5);
	if (odds5->value == 1){
		odds5 = odds5->next;
		if (odds5->value == 19){
			cout << "Test 5 passed!" << endl;
		} else {
			cout << "Test 5 failed: odds 2nd value = " << odds5->value << endl;
		}
	} else {
		cout << "Test 5 failed: odds->value = " << odds5->value << endl;
	}
	deleteList(odds5);
	deleteList(evens5);

	cout << "Test 6: Two Mix" << endl;
	Node* list6 = makeList({1,12});
	Node* odds6 = nullptr;
	Node* evens6 = nullptr;
	split(list6, odds6, evens6);
	if (odds6->value != 1){
		cout << "Test 6 failed: odds->value = " << odds6->value << endl;
	} else if (evens6->value != 12) {
		cout << "Test 6 failed: evens->value = " << evens6->value << endl;
	} else {
		cout << "Test 6 passed!" << endl;
	}
	deleteList(odds6);
	deleteList(evens6);

	cout << "Test 7: Four Mix" << endl;
	Node* list7 = makeList({1,4,6,27});
	Node* odds7 = nullptr;
	Node* evens7 = nullptr;
	split(list7, odds7, evens7);
	if ((odds7->value == 1) && (evens7->value == 4)){
		odds7 = odds7->next;
		evens7 = evens7->next;
		if ((odds7->value == 27) && (evens7->value == 6)){
			cout << "Test 7 passed!" << endl;
		} else {
			cout << "Test 7 failed: a 2nd value failed" << endl;
		}
	} else {
		cout << "Test 7 failed: a 1st value failed" << endl;
	}
	deleteList(odds7);
	deleteList(evens7);

	return 1;
}
