#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <list>
#include <stdexcept>
#include <limits>

using namespace std;

typedef long long int UT;
typedef list< list<UT> > LOL; // list-list
class Pascal {
    private:
        LOL pascal; // pascal triangle
        UT *P=NULL; // combinations
        inline LOL getPascalTriangle(int n) {
            // return first n rows of pascal triangle
            LOL::iterator v=pascal.begin();
            while(n--) ++v;
            LOL temp(pascal.begin(), v);
            return temp;
        }
        inline void build_comb(void) {
            // build the combinations
            const size_t lim=21;
            P = new UT[lim];
            P[0]=1;
            for(int i=1; i<lim; ++i) P[i]=P[i-1]*i;
        }
        inline UT combine(int n, int k) {
            // result of C^n_k
            return P[n] / (P[k]*P[n-k]);
        }
    public:
        inline UT PascalCord(int n, int k) {
            return combine(n, k);
        }
        LOL EnumeratePascalTriangle(int n) {
            // Why make the program in-efficient!?!?
            // Use combination to compute pascal triangle
            // Build first n rows of pascal triangle
            if(n<=pascal.size()) return getPascalTriangle(n);
            for(int i=pascal.size(); i<n; ++i) {
                list<UT> temp;
                for(int j=0; j<=i; ++j)
                    temp.push_back( Pascal::combine(i,j) );
                pascal.push_back(temp);
            }
            return getPascalTriangle(n);
        }
        LOL ClassicPascalTriangle(int n) {
            // This one is better for the specific purpose
            // Add from above row
            // Build first n rows of pascal triangle
            if(n<=pascal.size()) return getPascalTriangle(n); // Build only if missing terms
            LOL::iterator inst=pascal.begin();
            while(inst!=pascal.end()) ++inst;
            --inst; // Use the above row
            for(int i=pascal.size(); i!=n; ++i) {
                list<UT> temp(1,1);
                for(list<UT>::iterator v=inst->begin(); v!=inst->end(); ++v) {
                    list<UT>::iterator u=v; ++u;
                    if(u==inst->end()) break;
                    temp.push_back( (*v) + (*u) );
                }
                temp.push_back(1);
                pascal.push_back(temp);
                ++inst;
            }
            return getPascalTriangle(n);
        }
        UT EvalPolynomial(UT x, list<UT> &coef) {
            UT ans=0;
            for(list<UT>::iterator v=coef.begin(); v!=coef.end(); ++v) {
                ans = ans*x + *v; // Hornor's method
            }
            return ans;
        }
        list<UT> BinomialCoefficient(int n) { 
            EnumeratePascalTriangle(n+1);
            LOL::iterator v=pascal.begin();
            while(n--) ++v;
            return list<UT>(v->begin(), v->end());
        }
        UT EvalRowOfPsacalsTriangle(int n, int x) {
            list<UT> temp(BinomialCoefficient(n));
            return EvalPolynomial(x, temp);
        }
        LOL::iterator end() {
            return pascal.end();
        }
        LOL::iterator begin() {
            return pascal.begin();
        }
        Pascal() {
            build_comb(); //Preprocessing combinations
            pascal.push_back(list<UT>(1,1)); // The first term of pascal
        }
        ~Pascal() {
            delete[] P;
            P=NULL;
        }
};

class UserInterface:public Pascal {
    public:
        inline void prt(const list<UT> &l) {
            for(const UT& u: l) cout<<u<<' '; //C++11 auto loop
        }
        inline void prtll(const LOL &p) {
            int i=0;
            for(const list<UT>& v: p) { //C++11 auto loop
                prt(v);
                cout<<endl;
            }
        }

        inline void showMenu(void) {
            cout << "Choose:" << endl;
            cout << "1. Pascal_Cord(n,k), compute C^n_k" << endl;
            cout << "2. Pascal_Triangle(n), " << endl;
            cout << "   display first n rows of pascal triangle" << endl;
            cout << "3. Eval_Polynomial(x, [list])" << endl;
            cout << "4. Eval_(X+1)^n (n, x)" << endl;
            cout << "0. Quit" << endl;
        }

        bool selectFunc(const int sig) {
            switch(sig) {
                case 1: {
                    int n(0), k(0);
                    cout<<"Enter n k"<<endl;
                    cin>>n>>k;
                    cout<<PascalCord(n,k)<<endl;
                        }break;
                case 2: {
                    int n(0);
                    cout<<"Enter n"<<endl;
                    cin>>n;
                    LOL temp=EnumeratePascalTriangle(n);
                    prtll(temp);
                        }break;
                case 3: {
                    int x(0), n(0);
                    cout<<"Enter x"<<endl;
                    cin>>x;
                    cout<<"How many coefficients you want to input?"<<endl;
                    cin>>n;
                    list<UT> coef;
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

        void pascalMainLoop(void) {
            int sig;
            while(true) {
                showMenu();
                try {
                    cin>>sig;
                    if(!cin.good()) throw runtime_error("Bad input format!");
                    if(!selectFunc(sig)) break;
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
};

int main(void) {
    UserInterface UI;
    UI.pascalMainLoop();
    return 0;
}
