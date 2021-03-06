#ifndef _PASCAL_CLASS
#define _PASCAL_CLASS
// Require once

namespace Pascal {
    typedef long long int UT;
    typedef std::list< std::list<UT> > LOL; // std::list-of-std::list
    class Pascal {
        private:
            LOL pascal; // pascal triangle
            std::vector<UT> P; // combinations
            inline LOL getPascalTriangle(int); 
            inline void build_comb(void);
            inline UT combine(int, int);
        public:
            inline UT PascalCord(int, int);
            LOL EnumeratePascalTriangle(int);
            LOL ClassicPascalTriangle(int);
            std::list<UT> BinomialCoefficient(int);
            UT EvalPolynomial(UT , std::list<UT> &);
            UT EvalPolynomialRec(UT , std::list<UT>::reverse_iterator , std::list<UT>::reverse_iterator ); // Recursive Hornor's method
            UT EvalRowOfPsacalsTriangle(int , int); // Iterative Hornor's method
            LOL::iterator end();
            LOL::iterator begin();
            Pascal();
    };

    /* Constuctor */
    Pascal::Pascal() {
        build_comb(); //Preprocessing combinations
        pascal.push_back(std::list<UT>(1,1)); // The first term of pascal
    }
    /* End of Constructor */

    /* Private Section */
    inline LOL Pascal::getPascalTriangle(int n) {
        if(n<0) throw std::runtime_error("n must not less than 0");
        if(n>21) throw std::runtime_error("n must less than 22");
        // return first n rows of pascal triangle
        LOL::iterator v=pascal.begin();
        while(n--) ++v;
        LOL temp(pascal.begin(), v);
        return temp;
    }
    inline void Pascal::build_comb(void) {
        // build the combinations
        int lim=20;
        P.push_back(1LL); // [0,1) , 0!=1
        for(int i=1; i<=lim; ++i) { // [1,20]
            P.push_back( *(P.rbegin()) * i ); // 1!=1, 2!=2 ...
            // unsure, pass
        }
#ifdef _TEST
        for(UT v: P) std::cerr << v << std::endl;
#endif
    }
    inline UT Pascal::combine(int n, int k) {
        // result of C^n_k
        if(n<0 || k<0 || n>20 || k>20) throw std::runtime_error("The term of factorial is limited from [0,20]");
        return P.at(n) / (P.at(k)*P.at(n-k));
    }
    /*End of Private Section */

    /*Public Section*/
    inline UT Pascal::PascalCord(int n, int k) {
        int res(0);
        try {
            res=combine(n, k);
        } catch(std::runtime_error err) {
            res=0;
        }
        return res;
    }
    LOL Pascal::EnumeratePascalTriangle(int n) {
        // Why make the program in-efficient!?!?
        // Use combination to compute pascal triangle
        // Build first n rows of pascal triangle
        LOL res;
        try {
            if(n<=pascal.size()) {
                res = getPascalTriangle(n);
            } else {
                for(int i=pascal.size(); i<n; ++i) {
                    std::list<UT> temp;
                    for(int j=0; j<=i; ++j)
                        temp.push_back( Pascal::combine(i,j) );
                    pascal.push_back(temp);
                }
                res = getPascalTriangle(n);
            }
        } catch (std::runtime_error err) {
#ifndef _PUBLISH
            std::cerr<<err.what()<<std::endl;
#endif
        }
        return res;
    }
    LOL Pascal::ClassicPascalTriangle(int n) {
        // This one is better for the specific purpose
        // Add from above row
        // Build first n rows of pascal triangle
        LOL res;
        try {
            if(n<=pascal.size()) { 
                res = getPascalTriangle(n); // Build only if missing terms
            } else {
                LOL::iterator inst=pascal.begin();
                while(inst!=pascal.end()) ++inst;
                --inst; // Use the above row
                for(int i=pascal.size(); i!=n; ++i) {
                    std::list<UT> temp(1,1);
                    for(std::list<UT>::iterator v=inst->begin(); v!=inst->end(); ++v) {
                        std::list<UT>::iterator u=v; ++u;
                        if(u==inst->end()) break;
                        temp.push_back( (*v) + (*u) );
                    }
                    temp.push_back(1);
                    pascal.push_back(temp);
                    ++inst;
                }
                res = getPascalTriangle(n);
            }
        } catch (std::runtime_error err) {
#ifndef _PUBLISH
            std::cerr<<err.what()<<std::endl;
#endif
        }
        return res;
    }
    UT Pascal::EvalPolynomialRec(UT x, std::list<UT>::reverse_iterator u, std::list<UT>::reverse_iterator endp) {
        std::list<UT>::reverse_iterator v=u; ++v;
        if(v==endp) {
            return *u;
        }
        return x*EvalPolynomialRec(x, v, endp) + *u;
    }
    UT Pascal::EvalPolynomial(UT x, std::list<UT> &coef) {
        UT ans=0;
        try {
            for(std::list<UT>::iterator v=coef.begin(); v!=coef.end(); ++v) {
                ans = ans*x + *v; // Hornor's method
            }
        } catch (std::runtime_error err) {
#ifndef _PUBLISH
            std::cerr<<err.what()<<std::endl;
            std::cerr<<"The result is undefined."<<std::endl;
#endif
            ans=-1;
        }
        return ans;
    }

    std::list<UT> Pascal::BinomialCoefficient(int n) { 
        LOL::iterator v;
        try {
            if(n<0) throw std::runtime_error("Degree must greater than 0");
            EnumeratePascalTriangle(n+1);
            v=pascal.begin();
            while(n--) ++v;
        } catch (std::runtime_error err) {
#ifndef _PUBLISH
            std::cerr<<err.what()<<std::endl;
            std::cerr<<"The result is undefined"<<std::endl;
#endif
            return std::list<UT>(1,1);
        }
        return std::list<UT>(v->begin(), v->end());
    }

    UT Pascal::EvalRowOfPsacalsTriangle(int n, int x) {
        std::list<UT> res;
        try {
            if(n<0) throw std::runtime_error("Negative row is undefined");
            if(n>20) throw std::runtime_error("Can't complete if n is greater than 20");
            std::list<UT> temp=BinomialCoefficient(n);
            res.clear();
            res.insert(res.end(), temp.begin(), temp.end());
        } catch (std::runtime_error err) {
#ifndef _PUBLISH
            std::cerr << err.what() << std::endl;
#endif
            return 0;
        }
        return EvalPolynomial(x, res);
    }
    LOL::iterator Pascal::end() {
        return pascal.end();
    }
    LOL::iterator Pascal::begin() {
        return pascal.begin();
    }
    /*End of Public Section */
}
#endif
