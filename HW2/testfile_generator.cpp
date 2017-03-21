/*
*   Author: 404410030 - Kuang-Yu Jeng
*   2017/03/21
*   All Rights Reserved
*/
#include <bits/stdc++.h>
using namespace std;

inline string getRandString(int len=32) {
    string str;
    for(int i=0; i<len; ++i) {
        str.push_back( (char)(rand()%94 + 0x21) );
    }
    return str;
}

int main(void) {
    srand(time(NULL));
    //srand(time(NULL));
    const string fileName("testfile.txt");
    const int termLim=JUDGE_SCALE;
    ofstream f;
    f.open(fileName.c_str());
    if(!f.good()) return -1;
    for(int i=0; i<termLim; ++i) {
        int c=rand()%5;
        switch (c) {
            case 1: case 2:
                f << c << endl;
                if(rand()%6) {
                    if(rand()%6) {
                        f << rand()%1000 << endl;
                    } else {
                        f << getRandString( rand()%40+1 ) << endl;
                    }
                } else {
                    f << getRandString( rand()%40+1 ) << endl;
                }
                break;
            case 3: {
                        int N; N=rand()%30;
                        f << c << endl;
                        if(rand()%6) {
                            f << N << endl;
                            if(rand()%6) {
                                for(int i=0; i<N; ++i) {
                                    if(rand()%100)
                                        f << rand()%10000 << endl;
                                    else
                                        f << getRandString( rand()%40+1 ) << endl;
                                }
                            } else {
                                f << getRandString( rand()%40+1 ) << endl;
                            }
                        } else {
                            f << getRandString( rand()%40+1 ) << endl;
                        }
                    }break;
            case 4:
                    f << c << endl;
                    if(rand()%7)
                        f << rand()%50 << endl;
                    else
                        f << getRandString( rand()%40+1 ) << endl;
            default:
                    if(!rand()%8) {
                        f << getRandString( rand()%60 + 1)  << endl;
                    }
        }
    }
    f << 0 << endl;
    f.close(); f.clear();
    return 0;
}
