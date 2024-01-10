#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    int xVal;
    double xDoub;
    double theta; 
    cout << "Enter the angle theta in degrees:" << endl;
    cin >> theta;

    theta = theta * (M_PI / 180);
    cout << endl;
    for (int i = 0; i < 31; i++){
        xDoub = i * tan(theta);
        if ((xDoub >= 20) && (xDoub <= 30)){
            xVal = 20;
        } else {
            xVal = floor(xDoub); 
        }
        for (int j = 0; j < xVal; j++){
            cout << "*";
        }
        cout << endl;
    }
}
