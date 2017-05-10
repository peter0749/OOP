#ifndef _INCLUDE_POLY
#define _INCLUDE_POLY
#include "CircularList.h"
#include <iostream>

class Polynomial {
    private:
        CircularList queue;
        int number;
        void _copy(const Polynomial &cpy);
    public:
        Polynomial();
        Polynomial(const Polynomial &cpy);
        Polynomial(int *arr, const int n);
        void insert(int coef, int power);
        void insert(const Node &ref);
        int getSize(void) const;
        void get(int *a, int n) const;
        void set(int *a, int n);
        const Polynomial derivative(void);
        const Node read(void) const;
        void readNext(void);
        void resetRead(void);
        const bool readEnd(void) const;
        const Polynomial& operator=(const Polynomial &second);
        friend std::ostream &operator << (std::ostream &os, const Polynomial &P);
        friend std::istream &operator >> (std::istream &is, Polynomial &P);
};

const Polynomial operator+(Polynomial &first, Polynomial &second);
const Polynomial operator-(Polynomial &first, Polynomial &second);

#endif
