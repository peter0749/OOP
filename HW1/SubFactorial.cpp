#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;
using std::stringstream;
using std::runtime_error;

#ifdef LLVERSION
#define UBOND 20
typedef long long int UT;
#else
#define UBOND 12
typedef int UT;
#endif
UT Subfact(UT n) {
    UT res = n?n*Subfact(n-1)+(n&1LL?-1LL:1LL):1;
    cout << '!' << n << '=' << res << endl;
    return res;
}

int main(void) {
    string p;
    UT num;
    do {
        try {
            cout <<"Enter a number N: ";
            cin>>num;
            if(num>UBOND || num<0) {
                stringstream msg;
                bool errt=(num>UBOND);
                msg<<"N is too "<<(errt?"big":"small")<<" ("<<\
                num<<(errt?">":"<")<<(errt?UBOND:0)<<')';
                throw runtime_error(msg.str());
            } else {
                cout <<"The first "<<num+1<<" subfactorials are:"<<endl;
                Subfact(num);
            }
        } catch (runtime_error err) {
            cerr<<err.what()<<endl<<"Please try again."<<endl;
        }
        cout <<"Enter Y/y to continue or enter any key to exit... ";
        cin>>p;
    } while(p=="y"||p=="Y");
    cout<<"Bye"<<endl;
    return 0;
}
