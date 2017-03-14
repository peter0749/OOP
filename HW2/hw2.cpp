#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <list>

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
            EnumeratePascalTriangle(n);
            LOL::iterator v=pascal.begin();
            while(n--) ++v;
            return list<UT>(v->begin(), v->end());
        }
        UT EvalRowOfPsacalsTriangle(int n=0, int x=0) {
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

int main(void) {
    const UT inputData[]={1,5,0,3}; // The sample coefficients
    Pascal poly;
    LOL tri=poly.ClassicPascalTriangle(21); // Compute the pascal triangle
    cout << "Task 1:\nenumerate-pascal-triangle\n" << endl;
    prtll(tri);
    list<UT> bi=poly.BinomialCoefficient(10);
    cout << "==="  << endl << "Task 2:\nbinomial-coefficient(10)\n" << endl;
    prt(bi); cout<<endl;
    bi.clear();
    for(int i=0; i<4; ++i) bi.push_back(inputData[i]);
    cout << "==="  << endl << "Task 3:\neval-polynomial(5, [1,5,0,3])\n" << endl;
    cout << poly.EvalPolynomial(5, bi) << endl;
    cout << "==="  << endl << "Task 4:\neval-row-of-psacals-triangle(5, 3)\n" << endl;
    cout << poly.EvalRowOfPsacalsTriangle(5, 3) << endl;
    return 0;
}
