#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

typedef long long int UT;
UT Subfact(UT n) {
    UT res = n?n*Subfact(n-1)+(n&1LL?-1LL:1LL):1;
    cout << '!' << n << '=' << res << endl;
    return res;
}

int main(void) {
    string p;
    UT num;
    do {
        cout <<"Enter a number N: ";
        cin>>num;
        if(num>12) cerr<<"N is too big ("<<num<<">12)"<<endl;
        else if(num<0) cerr<<"N is too small ("<<num<<"<0)"<<endl;
        else {
            cout <<"The first "<<num+1<<" subfactorials are:"<<endl;
            Subfact(num);
        }
        cout <<"Enter Y/y to continue or enter any key to exit... ";
        cin>>p;
    }while(p=="y"||p=="Y");
    cout<<"Bye"<<endl;
    return 0;
}
