#ifndef _PAS_UI
#ifdef _PASCAL_CLASS
// Require Pascal Class
#define _PAS_UI
// Require once

namespace Pascal {
    class UserInterface:public Pascal {
        public:
            inline void prt(const list<UT>&);
            inline void prtll(const LOL &);
            inline void showMenu(void);
            bool selectFunc(const int);
            void pascalMainLoop(void);
    };

    /* All Public Section */

    inline void UserInterface::prt(const list<UT> &l) {
        for(const UT& u: l) cout<<u<<' '; //C++11 auto loop
    }
    inline void UserInterface::prtll(const LOL &p) {
        int i=0;
        for(const list<UT>& v: p) { //C++11 auto loop
            prt(v);
            cout<<endl;
        }
    }

    inline void UserInterface::showMenu(void) {
        cout << "Choose:" << endl;
        cout << "1. Pascal_Triangle(n), " << endl;
        cout << "   display [0,n] rows of pascal triangle" << endl;
        cout << "2. Pascal_Row(n), " << endl;
        cout << "   display (n+1)-th rows of pascal triangle" << endl;
        cout << "3. Eval_Polynomial(x, [list])" << endl;
        cout << "4. Eval_(X+1)^n (n, x)" << endl;
        cout << "0. Quit" << endl;
    }

    bool UserInterface::selectFunc(const int sig) {
        switch(sig) {
            case 1: {
                        int n(0);
                        cout<<"Enter n"<<endl;
                        cin>>n;
                        LOL temp=EnumeratePascalTriangle(n+1);
                        prtll(temp);
                    }break;
            case 2: {
                        int n(0);
                        cout<<"Enter n"<<endl;
                        cin>>n;
                        if(n<0||n>20) throw runtime_error("n must not less than 0 or greater than 20");
                        EnumeratePascalTriangle(n+1);
                        LOL::iterator v=begin();
                        while(n--) ++v;
                        prt(*v);
                        cout<<endl;
                    }break;
            case 3: {
                        int x(0), n(0);
                        cout<<"Enter x"<<endl;
                        cin>>x;
                        cout<<"How many coefficients you want to input?"<<endl;
                        cin>>n;
                        list<UT> coef;
                        cout<<"Please enter from degree "<< n-1 <<" to degree 0" << endl;
                        while(n--) {
                            int c=0;
                            cin>>c;
                            coef.push_back(c);
                        }
                        cout<<EvalPolynomial(x,coef)<<endl;
                    }break;
            case 4: {
                        int n(0), x(0);
                        cout<<"Enter n"<<endl;
                        cin>>n;
                        cout<<"Enter x"<<endl;
                        cin>>x;
                        UT res=EvalRowOfPsacalsTriangle(n,x);
                        cout<<res<<endl;
                    }break;
            case 0:
                    return false; // return false to exit
                    break;
        }
        if(!cin.good()) throw runtime_error("Bad input format in submenu");
        cout<<"====="<<endl;
        return true; // ow continue
    }

    void UserInterface::pascalMainLoop(void) {
        int sig;
        while(true) {
            showMenu();
            try {
                cin>>sig;
                if(cin.eof()) return; // Read End-Of-File
                if(!cin.good()) throw runtime_error("Bad input format!");
                try {
                    if(!selectFunc(sig)) break;
                } catch (out_of_range ofrErr) {
#ifndef _PUBLISH
                    cerr<<"Some operation led to out-of-bound. Please check your code..."<<endl;
#endif
                }
            } catch (runtime_error err) {
                cerr<<err.what()<<endl<<"Please try again."<<endl;
                if(cin.bad()) {
                    cerr<<"IO stream corrupted. The program fails anyway."<<endl;
                    exit(-1); // Program fails!
                }
                cin.clear(); // clear error bit
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                // clean-up the buffer
            }
        }
    }
    /* End of Public Section */
}

#endif
#endif
