#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long array[5] = {};
				unsigned int thirtysix = 1;
				unsigned int letter = 0;
				unsigned int len = k.length();
				unsigned int temp = len - 1;

				int arrAddr = 4;
				unsigned long long res = 0;

				for (unsigned int i = 0; i < len; i++){
					letter = letterDigitToNumber(k[temp]);
					letter *= thirtysix;
					res += letter;
					temp--;
					thirtysix *= 36;
					if (i % 6 == 5){
						thirtysix = 1;
						array[arrAddr] = res;
						res = 0;
						arrAddr--;
					}
				}

				array[arrAddr] = res;

				unsigned long long ret = 0;
				unsigned long long templong = 0;

				for (int i = 0; i < 5; i++){
					templong = array[i] * rValues[i];
					ret += templong;
				}

				return ret;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        char temp = 0;
				if ((letter >= 48) && (letter <= 57)){
					temp = letter - 22;
				} else if ((letter >= 65) && (letter <= 90)){
					temp = letter - 65;
				} else {
					temp = letter - 97;
				}

				unsigned int ret = (int)temp;
				return ret;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
