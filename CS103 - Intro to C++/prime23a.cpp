#include <iostream>
#include <string>

using namespace std;

int main()
{
    int input;
    int twos = 0;
    int threes = 0;
    int noCondition = 0;
    cout << "Enter a positive integer:" << endl;
    cin >> input;
    
    while (input % 2 == 0){
        input = input / 2;
        twos++;
    }
    while (input % 3 == 0){
        input = input / 3;
        threes++;
    }
    if ((input & 2 != 1) || (input & 3 != 1)){
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        cout << "Twos=" << twos << " Threes=" << threes << endl;
    }
}
