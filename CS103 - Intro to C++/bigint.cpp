#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    string str = s;
    int len = str.length();
    int digit;
    if (str[0] == '-'){
      isPositive = false;
      for (int i = len - 1; i > 0; i--){
        if ((int)(str[i]) < 58){
          digit = (int)(str[i]) - 48;
        } else {
          digit = (int)(str[i]) - 55;
        }
        vec.push_back(digit);
      }
    } else {
      isPositive = true;
      for (int i = len - 1; i > -1; i--){
        if ((int)(str[i]) < 58){
          digit = (int)(str[i]) - 48;
        } else {
          digit = (int)(str[i]) - 55;
        }
        vec.push_back(digit);
      }
    }
}


/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    if (input == 0){
      vec.push_back(0);
    }
    base = setbase;
    if (input < 0){
      isPositive = false;
      input *= -1;
    } else {
      isPositive = true;
    }
    int spots = 0;
    int temp = input;
    int digit;
    double exp;
    while (temp != 0){
      spots++;
      temp /= base;
    }
    for (int i = 0; i < spots; i++){
      digit = input;
      exp = pow(base, i);
      digit /= exp;
      digit %= base;
      vec.push_back(digit);
    }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){
    vector<int> vect = b.vec;
    int len = vect.size();
    int digit;
    for (int i = 0; i < len; i++){
      digit = vect[i];
      vec.push_back(digit);
    }
    bool pos = b.isPositive;
    isPositive = pos;
    int ba = b.base;
    base = ba;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){
    vector<int> vect = b.vec;
    int len = vect.size();
    int digit;
    int temp = vec.size();
    for (int i = 0; i < temp; i++){
      vec.pop_back();
    }
    for (int i = 0; i < len; i++){
      digit = vect[i];
      vec.push_back(digit);
    }
    bool pos = b.isPositive;
    isPositive = pos;
    int ba = b.base;
    base = ba;
    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){
  int len = vec.size();
  int digit;
  char d;
  string str;
  if(isPositive == false){
    str.push_back('-');
  }
  for (int i = len - 1; i > -1; i--){
    digit = vec[i];
    if (digit > 9){
      digit += 55;
      d = (char)digit;
    } else {
      digit += 48;
      d = (char)digit;
    }
    str.push_back(d);
  }
  return str;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{
  int integer = 0;
  int temp;
  int power;
  int notZero = false;

  int length = vec.size();
  for (int i = 0; i < length; i++){
    temp = vec[i];
    if (temp != 0){
      notZero = true;
    }
    power = pow(base, i);
    power *= temp;
    integer += power;
    if ((isPositive == true) && (integer <= 0) && (notZero == true)){
      return INT_MAX;
    } else if ((isPositive == false) && (integer <= 0) && (notZero == true)){
      return INT_MIN;
    }
  } 

  if (isPositive == false){
    integer *= -1;
  }
 
  return integer;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    if ((isPositive == false) && (b.isPositive == true)){
      return -1;
    } else if ((isPositive == true) && (b.isPositive == false)){
      return 1;
    }

    int lenA = vec.size();
    int lenB = b.vec.size();

    if (isPositive == true){
      if (lenB > lenA){
        return -1;
      } else if (lenB < lenA){
        return 1;
      } else {
        for (int i = lenA - 1; i > -1; i--){
          if (vec[i] > b.vec[i]){
            return 1;
          } else if (vec[i] < b.vec[i]){
            return -1;
          }
        }
      }
    } else if (isPositive == false){
      if (lenB > lenA){
        return 1;
      } else if (lenB < lenA){
        return -1;
      } else {
        for (int i = lenA - 1; i > -1; i--){
          if (vec[i] > b.vec[i]){
            return -1;
          } else if (vec[i] < b.vec[i]){
            return 1;
          }
        }
      }
    }
  return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  if(a.compare(b) != 0){
    return false;
  } else {
    return true;
  }
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  if(a.compare(b) != 0){
    return true;
  } else {
    return false;
  }
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  if(a.compare(b) == 1){
    return false;
  } else {
    return true;
  }
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  if(a.compare(b) == -1){
    return false;
  } else {
    return true;
  }
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  if(a.compare(b) != 1){
    return false;
  } else {
    return true;
  }
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  if(a.compare(b) != -1){
    return false;
  } else {
    return true;
  }
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c += b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    bool temp = b.isPositive;
    
    if (isPositive != temp){
      vector<int> numB = b.vec;
      if (isPositive == true){
        isPositive = false;
      } else {
        isPositive = true;
      }
      if (((b > *this) && isPositive == true) || ((b < *this) && isPositive == false)){
        vector<int> tempV = vec;
        vec = numB;
        numB = tempV;
        if (isPositive == true){
          isPositive = false;
        } else {
          isPositive = true;
        }
      }
      if (isPositive == true){
        isPositive = false;
      } else {
        isPositive = true;
      }

      int len = vec.size();
      int lenB = numB.size();
      int sub = 0;
      int carried = 0;

      if ((vec[0] == 0) && (len == 1)){
        if (isPositive == true){
          isPositive = false;
        } else {
          isPositive = true;
        }
        return *this; 
      }
      if ((numB[0] == 0) && (lenB == 1)){
        return *this;
      }

      for (int i = 0; i < lenB; i++){
        sub = vec[i] - numB[i] + carried;
        if (sub < 0){
          sub += base;
          carried = -1;
        } else {
          carried = 0;
        }
        vec[i] = sub;
      }
      if (len > lenB){
        for (int i = lenB; i < len; i++){
          sub = vec[i] + carried;
          if (sub < 0){
            sub += base;
            carried = -1;
          } else {
            carried = 0;
          }
          vec[i] = sub;
        }
      }

      for (int i = len - 1; i > 0; i--){
        if (vec[i] == 0){
          vec.pop_back();
        } else {
          break;
        }
      }

      len = vec.size();
      if ((vec[0] == 0) && (len == 1)){
        isPositive = true;
      }
      
    return *this;
    } else {
      vector<int> numB = b.vec;
      if (((b > *this) && isPositive == true) || ((b < *this) && isPositive == false)){
        vector<int> tempV = vec;
        vec = numB;
        numB = tempV;
      }
      int len = vec.size();
      int lenB = numB.size();
      int add = 0;
      int carried = 0;
      for (int i = 0; i < lenB; i++){
        add = vec[i] + numB[i] + carried;
        if (add > base - 1){
          carried = 1;
          add -= base;
        } else {
          carried = 0;
        }
        vec[i] = add;
      }
      if (len > lenB){
        for (int i = lenB; i < len; i++){
          add = vec[i] + carried;
          if (add > base - 1){
            carried = 1;
            add -= base;
          } else {
            carried = 0;
          }
          vec[i] = add;
        }
      }
      if (carried == 1){
        vec.push_back(carried);
      }
      
    return *this;
  }

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c -= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

    bool temp = b.isPositive;
    
    if (isPositive != temp){
      vector<int> numB = b.vec;
      if (isPositive == true){
        isPositive = false;
      } else {
        isPositive = true;
      }
      if (((b > *this) && isPositive == true) || ((b < *this) && isPositive == false)){
        vector<int> tempV = vec;
        vec = numB;
        numB = tempV;
      }
      if (isPositive == true){
        isPositive = false;
      } else {
        isPositive = true;
      }
      int len = vec.size();
      int lenB = numB.size();
      int add = 0;
      int carried = 0;
      for (int i = 0; i < lenB; i++){
        add = vec[i] + numB[i] + carried;
        if (add > base - 1){
          carried = 1;
          add -= base;
        } else {
          carried = 0;
        }
        vec[i] = add;
      }
      if (len > lenB){
        for (int i = lenB; i < len; i++){
          add = vec[i] + carried;
          if (add > base - 1){
            carried = 1;
            add -= base;
          } else {
            carried = 0;
          }
          vec[i] = add;
        }
      }
      if (carried == 1){
        vec.push_back(carried);
      }
      
    return *this;
    } else {
      vector<int> numB = b.vec;
      if (((b > *this) && isPositive == true) || ((b < *this) && isPositive == false)){
        vector<int> tempV = vec;
        vec = numB;
        numB = tempV;
        if (isPositive == true){
          isPositive = false;
        } else {
          isPositive = true;
        }
      }

      int len = vec.size();
      int lenB = numB.size();
      int sub = 0;
      int carried = 0;

      if ((numB[0] == 0) && (lenB == 1)){
        return *this;
      }

      for (int i = 0; i < lenB; i++){
        sub = vec[i] - numB[i] + carried;
        if (sub < 0){
          sub += base;
          carried = -1;
        } else {
          carried = 0;
        }
        vec[i] = sub;
      }
      if (len > lenB){
        for (int i = lenB; i < len; i++){
          sub = vec[i] + carried;
          if (sub < 0){
            sub += base;
            carried = -1;
          } else {
            carried = 0;
          }
          vec[i] = sub;
        }
      }

      for (int i = len - 1; i > 0; i--){
        if (vec[i] == 0){
          vec.pop_back();
        } else {
          break;
        }
      }

      len = vec.size();
      if ((vec[0] == 0) && (len == 1)){
        isPositive = true;
      }

      for (int i = len - 1; i > 0; i--){
        if (vec[i] == 0){
          vec.pop_back();
        } else {
          break;
        }
      }

      len = vec.size();
      if ((vec[0] == 0) && (len == 1)){
        isPositive = true;
      }
      
    return *this;
    }

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c *= b;
  return c;
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

    vector<int> numB = b.vec;

    BigInt c = b;
    if (b.isPositive == true){
      c.isPositive = false;
    } else {
      c.isPositive = true;
    }
    if (((b > *this) || (c > *this)) && (numB[0] > 0)){
      vector<int> tempV = vec;
      vec = numB;
      numB = tempV;
    }

    bool temp = b.isPositive;
  
    if (isPositive != temp){
      isPositive = false;
    } else {
      isPositive = true;
    }

    int len = vec.size();
    int lenB = numB.size();
  
    if (((numB[0] == 0) && (lenB == 1)) || ((vec[0] == 0) && (len == 1))){
      for (int i = 0; i < len - 1; i++){
        vec.pop_back();
      }
      vec[0] = 0;
      isPositive = true;
      return *this;
    } else if ((numB[0] == 1) && (lenB == 1)){
      return *this;
    } 
    
    BigInt total (0, base);
    BigInt add (0, base);
    total.isPositive = isPositive;
    add.isPositive = isPositive;
    int carry;
    int digit = 0;

    for (int i = 0; i < lenB; i++){
      carry = 0;
      for (int k = 0; k < i; k++){
        add.vec.push_back(0);
      }
      for (int j = 0; j < len; j++){
        digit = numB[i] * vec[j] + carry;
        if (digit > base - 1){
          carry = digit / base;
          digit %= base;
        } else {
          carry = 0;
        }
        if ((i == 0) && (j == 0)){
          add.vec[0] = digit;
        } else {
          add.vec.push_back(digit);
        }
      }
      if (carry > 0){
        add.vec.push_back(carry);
      }

      total += add;

      int si = add.vec.size();
      for (int l = 0; l < si; l++){
        add.vec.pop_back();
      }
    }

    *this = total;
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c /= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    
    BigInt quotient(0, base);
    BigInt remainder(0, base);
    divisionMain(b, quotient, remainder);

    *this = quotient;
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c %= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    
    BigInt quotient(0, base);
    BigInt remainder(0, base);
    divisionMain(b, quotient, remainder);

    *this = remainder;
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){
  if(base != b.base){
      throw DiffBaseException();
  }
  if(b.vec.size() == 1 && b.vec[0] == 0){
      throw DivByZeroException();
  }

  vector<int> numB = b.vec;

  int len = vec.size();
  BigInt c(0, base);
  if (b.isPositive == false){
    c.isPositive = true;
  }
  vector<int> numC = numB;
  int cLen = numB.size();
  for (int i = 0; i < cLen; i++){
    numC[i] = numB[cLen - i - 1];
  }
  bool tempj = isPositive;

  BigInt temp(0, base);
  bool start = false;
  int digit;
  BigInt multiplier(0, base);
  BigInt subtract(0, base);
  quotient.isPositive = isPositive;
  bool t = false;
  BigInt d(0, base);
  bool selected;

  for (int i = 0; i < len; i++){
    digit = vec[len - i - 1];
    if (i == 0){
      temp.vec[0] = digit;
    } else {
      temp.vec.push_back(digit);
    }

    BigInt c = b;
    if (b.isPositive == false){
      c.isPositive = true;
    }
    d = temp;
    vector<int> numD = temp.vec;
    int dLen = temp.vec.size();
    for (int i = 0; i < dLen; i++){
      d.vec[i] = numD[dLen - i - 1];
    }

    if ((start == false) && (((b <= d) && (b.isPositive == true)) || ((c <= d) && (b.isPositive == false)))){
      start = true;
    }
    if (start == true){
      selected = false;
      multiplier = c;
      multiplier -= c;
      for (int j = 0; j < base; j++){
        subtract = d;
        subtract -= multiplier;
        int subtLen = subtract.vec.size();
        if (subtract.vec[subtLen - 1] == 0){
          subtract.vec.pop_back();
        }

        if (subtract < c){
          selected = true;
          if (t == false){
            quotient.vec[0] = j;
            t = true;
          } else {
            quotient.vec.push_back(j);
          }

          int tempLen = temp.vec.size();
          for (int i = 0; i < tempLen; i++){
            temp.vec[i] = subtract.vec[dLen - i - 1];
          }
          
          break;
        }
        multiplier += c;
      }
      if (selected == false){
        quotient.vec.push_back(0);
      }
    }
  }

  if ((tempj == true) && (b.isPositive == true)){
    quotient.isPositive = true;
  } else if ((tempj == false) && (b.isPositive == false)) {
    quotient.isPositive = true;
  } else {
    quotient.isPositive = false;
  }

  if ((quotient.vec[0] == 0) && (quotient.vec.size() == 1)){
    quotient.isPositive = true;
  }

    BigInt quoTemp = quotient;
    int quolen = quotient.vec.size();
    for (int i = 0; i < quolen; i++){
      quoTemp.vec[i] = quotient.vec[quolen - i - 1];
    }
  quotient = quoTemp;

  remainder = temp;


  int Rlen = remainder.vec.size();

  if (tempj == true){
    remainder.isPositive = true;
  } else {
    remainder.isPositive = false;
  }

  Rlen = remainder.vec.size();
  BigInt rTemp = remainder;
  for (int i = 0; i < Rlen; i++){
    rTemp.vec[i] = remainder.vec[Rlen - i - 1];
  }

  remainder = rTemp;
  
  for (int i = Rlen - 1; i > 0; i--){
    if (remainder.vec[i] == 0){
      remainder.vec.pop_back();
    } else {
      break;
    }
  }

  if ((remainder.vec[0] == 0) && (remainder.vec.size() == 1)){
    remainder.isPositive = true;
  }
}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){
  BigInt c = a;
  c.exponentiation(b);
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }

    BigInt eve = b;
    BigInt one("10", base);
    one /= one;
    BigInt two("2", base);
    eve %= two;
    int even = eve.vec[0];

    if((isPositive == false) && (even == 0)){
      isPositive = true;
    }

    int lenA = vec.size();
    int lenB = b.vec.size();

    if ((b.vec[0] == 0) && (lenB == 1) && (vec[0] == 0) && (lenA == 1)){
      *this = one;
      return *this;
    }

    if ((b.vec[0] == 0) && (lenB == 1)){
      *this = one;
      return *this;
    } else if ((b.vec[0] == 1) && (lenB == 1)) {
      return *this;
    }

    if ((vec[0] == 0) && (lenA == 1)){
      *this -= *this;
      return *this;
    } else if ((vec[0] == 1) && (lenA == 1)) {
      return *this;
    }

    BigInt exp = b;
    BigInt base = *this;
    BigInt outer = one;

    while (exp != one){
      eve = exp;
      eve %= two;
      even = eve.vec[0];
      if (even == 0){
        exp /= two;
        base *= base;
      } else {
        exp -= one;
        exp /= two;
        outer *= base;
        base *= base;
      }
    }

    base *= outer;
    *this = base;

    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){
  BigInt c = a;
  c.modulusExp(b, m);
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    
    BigInt eve = b;
    BigInt one("10", base);
    one /= one;
    BigInt two("2", base);
    eve %= two;
    int even = eve.vec[0];

    if((isPositive == false) && (even == 0)){
      isPositive = true;
    }

    int lenA = vec.size();
    int lenB = b.vec.size();

    if ((b.vec[0] == 0) && (lenB == 1) && (vec[0] == 0) && (lenA == 1)){
      *this = one;
      return *this;
    }

    if ((b.vec[0] == 0) && (lenB == 1)){
      *this = one;
      return *this;
    } else if ((b.vec[0] == 1) && (lenB == 1)) {
      return *this;
    }

    if ((vec[0] == 0) && (lenA == 1)){
      *this -= *this;
      return *this;
    } else if ((vec[0] == 1) && (lenA == 1)) {
      return *this;
    }

    BigInt exp = b;
    BigInt base = *this;
    BigInt outer = one;
    BigInt mod = m;

    while (exp != one){
      eve = exp;
      eve %= two;
      even = eve.vec[0];
      if (even == 0){
        exp /= two;
        base *= base;
      } else {
        exp -= one;
        exp /= two;
        outer *= base;
        base *= base;
      }
      base %= mod;
      outer %= mod;
    }

    base *= outer;
    base %= mod;
    *this = base;

    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************2