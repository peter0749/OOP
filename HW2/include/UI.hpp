#ifndef _PAS_UI
#ifdef _PASCAL_CLASS
// Require Pascal Class
#define _PAS_UI
// Require once

namespace Pascal {
    class UserInterface:public Pascal {
        public:
            inline void prt(const std::list<UT>&);
            inline void prtll(const LOL &);
            inline void showMenu(void);
            bool selectFunc(const int);
            void pascalMainLoop(void);
    };

    /* All Public Section */

    inline void UserInterface::prt(const std::list<UT> &l) {
        for(const UT& u: l) std::cout<<u<<' '; //C++11 auto loop
    }
    inline void UserInterface::prtll(const LOL &p) {
        int i=0;
        for(const std::list<UT>& v: p) { //C++11 auto loop
            prt(v);
            std::cout<<std::endl;
        }
    }

    inline void UserInterface::showMenu(void) {
        std::cout << "Choose:" << std::endl;
        std::cout << "1. Pascal_Triangle(n), " << std::endl;
        std::cout << "   display [0,n] rows of pascal triangle" << std::endl;
        std::cout << "2. Pascal_Row(n), " << std::endl;
        std::cout << "   display (n+1)-th rows of pascal triangle" << std::endl;
        std::cout << "3. Eval_Polynomial(x, [list])" << std::endl;
        std::cout << "4. Eval_(X+1)^n (n, x)" << std::endl;
        std::cout << "0. Quit" << std::endl;
    }

    bool UserInterface::selectFunc(const int sig) {
        switch(sig) {
            case 1: {
                        int n(0);
                        std::cout<<"Enter n"<<std::endl;
                        std::cin>>n;
                        LOL temp=EnumeratePascalTriangle(n+1);
                        prtll(temp);
                    }break;
            case 2: {
                        int n(0);
                        std::cout<<"Enter n"<<std::endl;
                        std::cin>>n;
                        if(n<0||n>20) throw std::runtime_error("n must not less than 0 or greater than 20");
                        EnumeratePascalTriangle(n+1);
                        LOL::iterator v=begin();
                        while(n--) ++v;
                        prt(*v);
                        std::cout<<std::endl;
                    }break;
            case 3: {
                        int x(0), n(0);
                        std::cout<<"Enter x"<<std::endl;
                        std::cin>>x;
                        std::cout<<"How many coefficients you want to input?"<<std::endl;
                        std::cin>>n;
                        std::list<UT> coef;
                        std::cout<<"Please enter from degree "<< n-1 <<" to degree "<< 0 << std::endl;
                        while(n--) {
                            int c=0;
                            std::cin>>c;
                            coef.push_back(c);
                        }
                        std::cout<<EvalPolynomialRec(x,coef.rbegin(), coef.rend())<<std::endl;
                    }break;
            case 4: {
                        int n(0), x(0);
                        std::cout<<"Enter n"<<std::endl;
                        std::cin>>n;
                        std::cout<<"Enter x"<<std::endl;
                        std::cin>>x;
                        UT res=EvalRowOfPsacalsTriangle(n,x);
                        std::cout<<res<<std::endl;
                    }break;
            case 0:
                    return false; // return false to exit
                    break;
        }
        if(!std::cin.good()) throw std::runtime_error("Bad input format in submenu");
        std::cout<<"====="<<std::endl;
        return true; // ow continue
    }

    void UserInterface::pascalMainLoop(void) {
        int sig;
        while(true) {
            showMenu();
            try {
                std::cin>>sig;
                if(std::cin.eof()) return; // Read End-Of-File
                if(!std::cin.good()) throw std::runtime_error("Bad input format!");
                try {
                    if(!selectFunc(sig)) break;
                } catch (std::out_of_range ofrErr) {
#ifndef _PUBLISH
                    std::cerr<<"Some operation led to out-of-bound. Please check your code..."<<std::endl;
#endif
                }
            } catch (std::runtime_error err) {
                std::cerr<<err.what()<<std::endl<<"Please try again."<<std::endl;
                if(std::cin.bad()) {
                    std::cerr<<"IO stream corrupted. The program fails anyway."<<std::endl;
                    exit(-1); // Program fails!
                }
                std::cin.clear(); // clear error bit
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                // clean-up the buffer
            }
        }
    }
    /* End of Public Section */
}

#endif
#endif
