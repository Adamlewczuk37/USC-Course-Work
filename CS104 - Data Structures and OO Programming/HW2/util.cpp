#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
	std::set<std::string> st;
	int len = rawWords.length();
	int itr = 0;
	int str_itr = 0;
	string temp;
	while (itr <= len){
		if (((char)rawWords[itr] == 38) || ((char)rawWords[itr] == 32) || ((char)rawWords[itr] == 39) || (((char)rawWords[itr] > 43) && ((char)rawWords[itr] < 48))){
			if (str_itr > 1){
				for (unsigned int i = 0; i < temp.length(); i++){
					temp[i] = tolower(temp[i]);
				}
				st.insert(temp);
			} else if ((char)rawWords[itr] == 38){
				temp = "and";
				st.insert(temp);
			}
			temp.clear();
			str_itr = 0;
		} else {
			temp += rawWords[itr];
			str_itr++;
		}
		itr++;
		if (itr == len){
			for (unsigned int i = 0; i < temp.length(); i++){
				temp[i] = tolower(temp[i]);
			}
			st.insert(temp);
		}
	}

  return st;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
