#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <vector>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void flInsert(const int& len, const int& fllen, const std::vector<int>& positions, std::vector<int>& temp, const std::set<std::string>& dict, std::string& in, const std::string& floating, std::set<std::string>& ans);
void wordleHelper(const int& len, std::string& in, std::set<std::string>& ans, const std::set<std::string>& dict, int& lentemp);
bool isValid(const std::set<std::string>& dict, const std::string& in);


std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> ret = {};
		if (in == ""){
			return ret;
		}

    std::string temp = in;
    int length = in.length();
		int flolen = floating.length();
		std::vector<int> pos = {};
		std::vector<int> tem = pos;
		
		for (int i = 0; i < length; i++){
			if (in[i] == '-'){
				pos.push_back(i);
			}
		}
		flInsert(length, flolen, pos, tem, dict, temp, floating, ret);

    return ret;
}


void flInsert(const int& len, const int& fllen, const std::vector<int>& positions, std::vector<int>& temp, const std::set<std::string>& dict, std::string& in, const std::string& floating, std::set<std::string>& ans){
		if (fllen == 0){
			int lentemp = 0;
			wordleHelper(len, in, ans, dict, lentemp);
			return;
		}
		
		if ((int)temp.size() == fllen){
			for (unsigned int i = 0; i < temp.size(); i++){
				in[temp[i]] = floating[i];
			}
			int lentemp = 0;
			wordleHelper(len, in, ans, dict, lentemp);

			int val = temp[temp.size()-1];
			in[val] = '-';
			temp.pop_back();
			return;
		}

		for (unsigned int i = 0; i < positions.size(); i++){
			std::vector<int>::iterator it = std::find(temp.begin(), temp.end(), positions[i]);
			if (it == temp.end()){
				temp.push_back(positions[i]);
				flInsert(len, fllen, positions, temp, dict, in, floating, ans);
			}
		}

		int val = temp[temp.size()-1];
		in[val] = '-';
		temp.pop_back();
		return;
}

void wordleHelper(const int& len, std::string& in, std::set<std::string>& ans, const std::set<std::string>& dict, int& lentemp){
		if (lentemp == len){
			if (isValid(dict, in)){
				ans.insert(in);
			}
			lentemp--;
			return;
		}

		if (in[lentemp] != '-'){
			lentemp++;
			wordleHelper(len, in, ans, dict, lentemp);
			lentemp--;
			return;
		} else {
				for (char c = 'a'; c <= 'z'; c++){
					in[lentemp] = c;
					lentemp++;
					wordleHelper(len, in, ans, dict, lentemp);
				}
				in[lentemp] = '-';
		}

		lentemp--;
		return;
}


bool isValid(const std::set<std::string>& dict, const std::string& in){
    std::set<std::string>::iterator it;
    it = dict.find(in);

    if (it != dict.end()){
        return true;
    } else {
        return false;
    }
}