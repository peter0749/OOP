#include <iostream>
#include <string>
#include "Number.h"
#include "TestNumbers.h"
using namespace std;

int main(void) {
    srand(3);
    Number **arr = TestNumbers::genNums();
    cout << "Average of 100 random Numbers in [0-999] (only compute ThreeDigitNumber):\n" << TestNumbers::printAvg(arr) << endl;
    delete[] arr;
    Number n1(3), n2(6);
    TwoDigitNumber n3(n1, n2);
    ThreeDigitNumber n4(n1, n3);
    cout << "Number: " << n1.toString() << endl;
    cout << "Number: " << n2.toString() << endl;
    cout << "TwoDigitNumber: " << n3.toString() << endl;
    cout << "ThreeDigitNumber: " << n4.toString() << endl;
    int testDigit=875;
    cout << "Test getFirstDigit() and getSecondDigit(): \n" << testDigit << endl << "First: " << TestNumbers::getFirstDigit(testDigit).toString() << endl << "Second: " << TestNumbers::getSecondDigit(testDigit).toString() << endl;
    ThreeDigitNumber *arr2[7];
    for (int i=0; i<7; ++i) {
        n1=Number(i); n2=Number(i); n3=TwoDigitNumber(n1,n2);
        arr2[i] = new ThreeDigitNumber(n1,n3);
        cout << "ThreeDigitNumber in array[" << i << "] :" << arr2[i]->toString() << endl;
    }
    cout << "Average: " << TestNumbers::printAvg((Number**)arr2,7) << endl;

    return 0;
}

