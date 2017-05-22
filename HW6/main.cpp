#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "Number.h"
#include "TestNumbers.h"
using namespace std;

int Rabin_Karp (const string &s) {
    long long int sum=0;
    const long long int P=11; // whatever
    const long long int Q=1e9+7;
    for (int i=0; i<s.length(); ++i) {
        sum = sum*P%Q;
        sum = (sum+(long long int)s[i])%Q;
    }
    return (int)(sum%Q);
}

int main(void) {
    srand(Rabin_Karp("The quick brown fox jumps over the lazy dog."));
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
    cout << "==== Press ENTER to test TestNumbers::genNums() and Polymorphism ====" << endl;
    getchar();
    Number **arr = TestNumbers::genNums(); // default is 100 instnaces of Number
    for (int i=0; i<100; ++i) {
        cout << setw(3) << i+1 << "-th Number(" << setw(3) << arr[i]->toString() << ") says: ";
        arr[i]->guessWho();
    }
    cout << "Average of 100 random Numbers in [0-999] (only compute ThreeDigitNumber):\n" << TestNumbers::printAvg(arr) << endl;
    delete[] arr; arr=NULL;
    return 0;
}

