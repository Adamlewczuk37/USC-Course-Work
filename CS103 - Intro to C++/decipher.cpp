#include "bigint.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

  char* filename = argv[1];

  ifstream ifile(filename);
  if (ifile.fail()){
    return -1;
  }

  int base;
  string exp, mod;
  ifile >> base >> exp >> mod;
    
 try{
  BigInt exponent(exp, base);
  BigInt modulus(mod, base);

  string temp;
  BigInt result("0", base);
  int integer;
  char ch;
  while (!ifile.fail()){
    ifile >> temp;
    BigInt character(temp, base);
    result = modPow(character, exponent, modulus);
    integer = result.to_int();
    ch = (char)integer;
    if (ifile.fail()){
      break;
    }
    cout << ch; 
  } 
 }
 catch(const exception& e){
    cout<<e.what()<<endl;
    return -1;
}

  cout << endl;

  ifile.close();

	return 0;
}