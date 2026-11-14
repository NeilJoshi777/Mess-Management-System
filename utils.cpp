#include "utils.h"
#include <iostream>
#include <limits>
using namespace std;

int readInt(const string& prompt, int lo, int hi) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= lo && value <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return value;
        }
        cin.clear();                                              
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}