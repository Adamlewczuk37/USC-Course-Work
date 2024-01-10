/* Author: Adam Lewczuk
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians. 
 *    Computes an approximation to sin(x) using an 4th-order Taylor series.
 */
#include <iostream>
#include <cmath>

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
   // Declare any variables you need here
   double input;
   double temp;
   double output = 0;
   
   // Prompt the user
   cout << "Enter x in radians:  " << endl;
   
   // get input
   cin >> input;
   temp = input;
   
   // Do some operations
   for (int i = 0; i < 4; i++){
       input = pow(-1, i) * pow(temp, 2*i + 1) / fact(2*i + 1);
       output += input;
   }
   
   // Print the result to the user
   cout << output << endl;
   
   // You're done
   return 0;
   
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
   int result = 1;
   for (int i = 1; i <= n; i++) {
      result = result * i;
   }
   return result;
}