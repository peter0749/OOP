#ifndef _PASCAL_CLASS
#define _PASCAL_CLASS
// Require once

class Pascal {
    private:
        LOL pascal; // pascal triangle
        vector<UT> P; // combinations
        inline LOL getPascalTriangle(int); 
        inline void build_comb(void);
        inline UT combine(int, int);
    public:
        inline UT PascalCord(int, int);
        LOL EnumeratePascalTriangle(int);
        LOL ClassicPascalTriangle(int);
        list<UT> BinomialCoefficient(int);
        UT EvalPolynomial(UT , list<UT> &);
        UT EvalRowOfPsacalsTriangle(int , int);
        LOL::iterator end();
        LOL::iterator begin();
        Pascal();
};

/* Constuctor */
Pascal::Pascal() {
    build_comb(); //Preprocessing combinations
    pascal.push_back(list<UT>(1,1)); // The first term of pascal
}
/* End of Constructor */

/* Private Section */
inline LOL Pascal::getPascalTriangle(int n) {
    if(n<0) throw runtime_error("n must not less than 0");
    if(n>21) throw runtime_error("n must less than 22");
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
    for(UT v: P) cerr << v << endl;
#endif
}
inline UT Pascal::combine(int n, int k) {
    // result of C^n_k
    if(n<0 || k<0 || n>20 || k>20) throw runtime_error("The term of factorial is limited from [0,20]");
    return P.at(n) / (P.at(k)*P.at(n-k));
}
/*End of Private Section */

/*Public Section*/
inline UT Pascal::PascalCord(int n, int k) {
    int res(0);
    try {
        res=combine(n, k);
    } catch(runtime_error err) {
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
                list<UT> temp;
                for(int j=0; j<=i; ++j)
                    temp.push_back( Pascal::combine(i,j) );
                pascal.push_back(temp);
            }
            res = getPascalTriangle(n);
        }
    } catch (runtime_error err) {
#ifndef _PUBLISH
        cerr<<err.what()<<endl;
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
            res = getPascalTriangle(n);
        }
    } catch (runtime_error err) {
#ifndef _PUBLISH
        cerr<<err.what()<<endl;
#endif
    }
    return res;
}
UT Pascal::EvalPolynomial(UT x, list<UT> &coef) {
    UT ans=0;
    try {
        for(list<UT>::iterator v=coef.begin(); v!=coef.end(); ++v) {
            ans = ans*x + *v; // Hornor's method
        }
    } catch (runtime_error err) {
#ifndef _PUBLISH
        cerr<<err.what()<<endl;
        cerr<<"The result is undefined."<<endl;
#endif
        ans=-1;
    }
    return ans;
}

list<UT> Pascal::BinomialCoefficient(int n) { 
    LOL::iterator v;
    try {
        if(n<0) throw runtime_error("Degree must greater than 0");
        EnumeratePascalTriangle(n+1);
        v=pascal.begin();
        while(n--) ++v;
    } catch (runtime_error err) {
#ifndef _PUBLISH
        cerr<<err.what()<<endl;
        cerr<<"The result is undefined"<<endl;
#endif
        return list<UT>(1,1);
    }
    return list<UT>(v->begin(), v->end());
}

UT Pascal::EvalRowOfPsacalsTriangle(int n, int x) {
    list<UT> res;
    try {
        if(n<0) throw runtime_error("Negative row is undefined");
        if(n>20) throw runtime_error("Can't complete if n is greater than 20");
        list<UT> temp=BinomialCoefficient(n);
        res.clear();
        res.insert(res.end(), temp.begin(), temp.end());
    } catch (runtime_error err) {
#ifndef _PUBLISH
        cerr << err.what() << endl;
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
#endif
