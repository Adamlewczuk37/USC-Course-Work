#include "ulliststr.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

//Use this file to test your ulliststr implementation before running the test suite
ULListStr * makeList(std::vector<std::string> const & values, bool pushBack)
{
	// circular list is not copyable so we have to pass it by pointer
	ULListStr * list = new ULListStr();

	if(pushBack)
	{
		for(std::vector<std::string>::const_iterator valuesIter = values.cbegin(); valuesIter != values.cend(); ++valuesIter)
		{
			list->push_back(*valuesIter);
		}
	}
	else
	{
		// push values in reverse from the front
		for(std::vector<std::string>::const_reverse_iterator valuesIter = values.crbegin(); valuesIter != values.crend(); ++valuesIter)
		{
			list->push_front(*valuesIter);
		}
	}

	return list;
}

ULListStr * makeList(std::vector<std::string> const & values)
{
    return makeList(values, true);
}

int main(int argc, char* argv[])
{
  cout << "Test 1: Empty List" << endl;
	ULListStr list;
	if (list.empty()){
		cout << "Test 1 passed!" << endl;
	} else {
		cout << "Test 1 failed" << endl;
	}

	cout << "Test 2: Add+Remove One Element" << endl;
	ULListStr list2;
	list2.push_back("s");
	if ((list2.size() == 1) && (list2.get(0) == "s")){
		list2.pop_back();
		if (list2.size() == 0){
			cout << "Test 2 passed!" << endl;
		} else {
			cout << "Test 2 failed: could not remove element" << endl;
		}
	} else {
		cout << "Test 2 failed: could not add element" << endl;
	}

	cout << "Test 3: Push Back 2 Elements" << endl;
	std::vector<std::string> contents{"abc", "15896"};
	ULListStr * list3 = makeList(contents);
	int temp = 1;
	for(size_t index = 0; index < list3->size(); ++index)
	{
		if(list3->get(index) != contents[index])
		{
			cout << "Expected value at index " << index << " was " << contents[index] << ", but element was actually " << list3->get(index) << std::endl;
			temp = 0;
		}
	}
	if (temp == 1){
		cout << "Test 3 passed!" << endl;
	}
	delete list3;

	cout << "Test 4: Push Front 2 Elements" << endl;
	std::vector<std::string> contents1{"abc", "15896"};
	ULListStr * list4 = makeList(contents1, false);
	temp = 1;
	for(size_t index = 0; index < list4->size(); ++index)
	{
		if(list4->get(index) != contents1[index])
		{
			cout << "Expected value at index " << index << " was " << contents1[index] << ", but element was actually " << list4->get(index) << std::endl;
			temp = 0;
		}
	}
	if (temp == 1){
		cout << "Test 4 passed!" << endl;
	}
	delete list4;

	cout << "Test 5: Push Back 11 Elements" << endl;
	std::vector<std::string> contents2{"abc", "15896", "b", "dufhu", "y", "47h", "6", "875", "you", "ufy", "zx5"};
	ULListStr * list5 = makeList(contents2);
	temp = 1;
	for(size_t index = 0; index < list5->size(); ++index)
	{
		if(list5->get(index) != contents2[index])
		{
			cout << "Expected value at index " << index << " was " << contents2[index] << ", but element was actually " << list5->get(index) << std::endl;
			temp = 0;
		}
	}
	if (temp == 1){
		cout << "Test 5 passed!" << endl;
	}
	delete list5;

	cout << "Test 6: Push Front 11 Elements" << endl;
	std::vector<std::string> contents3{"abc", "15896", "b", "dufhu", "y", "47h", "6", "875", "you", "ufy", "zx5"};
	ULListStr * list6 = makeList(contents3, false);
	temp = 1;
	for(size_t index = 0; index < list6->size(); ++index)
	{
		if(list6->get(index) != contents3[index])
		{
			cout << "Expected value at index " << index << " was " << contents3[index] << ", but element was actually " << list6->get(index) << std::endl;
			temp = 0;
		}
	}
	if (temp == 1){
		cout << "Test 6 passed!" << endl;
	}
	delete list6;

	cout << "Test 7: Push Back and Front" << endl;
	ULListStr list7;
	list7.push_back("ty");
	list7.push_front("tv");
	if ((list7.get(0) == "tv") && (list7.get(1) == "ty")){
		cout << "Test 7 passed!" << endl;
	} else {
		cout << "Test 7 failed for at least one value" << endl;
	}

	cout << "Test 8: Remove One Element - Pop Front" << endl;
	ULListStr list8;
	list8.push_back("ty");
	list8.pop_front();
	if (list8.size() == 0){
		cout << "Test 8 passed!" << endl;
	} else {
		cout << "Test 8 failed to pop element" << endl;
	}

	cout << "Test 9: Remove One Element - Pop Back" << endl;
	ULListStr list9;
	list9.push_front("ty");
	list9.pop_back();
	if (list9.size() == 0){
		cout << "Test 9 passed!" << endl;
	} else {
		cout << "Test 9 failed to pop element" << endl;
	}

	cout << "Test 10: Remove 11th Element - Pop Back" << endl;
	std::vector<std::string> contents4{"abc", "15896", "b", "dufhu", "y", "47h", "6", "875", "you", "ufy", "zx5"};
	ULListStr * list10 = makeList(contents4, false);
	list10->pop_back();
	if (list10->get(9) == "ufy"){
		cout << "Test 10 passed!" << endl;
	} else {
		cout << "Test 10 failed to pop element" << endl;
	}


	cout << "Test 11: Remove Front Element - Pop Front" << endl;
	ULListStr list11;
	list11.push_back("ty");
	list11.push_front("tv");
	list11.pop_front();
	if (list11.get(0) == "ty"){
		cout << "Test 11 passed!" << endl;
	} else {
		cout << "Test 11 failed to pop element" << endl;
	}

	cout << "Test 12: Find Front Element" << endl;
	ULListStr list12;
	list12.push_back("ty");
	list12.push_back("vt");
	if (list12.front() == "ty"){
		cout << "Test 12 passed!" << endl;
	} else {
		cout << "Test 12 failed to find front element" << endl;
	}

	cout << "Test 13: Find Back Element" << endl;
	ULListStr list13;
	list13.push_back("ty");
	list13.push_back("vt");
	if (list13.back() == "vt"){
		cout << "Test 13 passed!" << endl;
	} else {
		cout << "Test 13 failed to find front element" << endl;
	}


  return 1;
}
