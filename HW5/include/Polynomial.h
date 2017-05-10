#ifndef _INCLUDE_POLY
#define _INCLUDE_POLY
#include "CircularList.h"
#include <iostream>

class Polynomial {
    private:
        CircularList queue;
        int number;
        void _copy(const Polynomial &cpy);
        int  _fast_pow(int x, int n) const;
    public:
        Polynomial();
        Polynomial(const Polynomial &cpy);
        Polynomial(int *arr, const int n);
        void clear(void);
        void insert(int coef, int power);
        void insert(const Node &ref);
        int getSize(void) const;
        void get(int *a, int n) const;
        void set(int *a, int n);
        Polynomial derivative(void);
        const Node read(void) const;
        void readNext(void);
        void resetRead(void);
        const bool readEnd(void) const;
        const Polynomial& operator=(const Polynomial &second);
        const int operator()(const int x) const;
        friend std::ostream &operator << (std::ostream &os, const Polynomial &P);
        friend std::istream &operator >> (std::istream &is, Polynomial &P);
};

const Polynomial operator+(const Polynomial &first, const Polynomial &second);
const Polynomial operator+(const Polynomial &first, const int coef);
const Polynomial operator+(const int coef, const Polynomial &second);
const Polynomial operator-(const Polynomial&);
const Polynomial operator-(const Polynomial &first, const Polynomial &second);
const Polynomial operator-(const Polynomial &first, const int coef);
const Polynomial operator-(const int coef, const Polynomial &second);
const Polynomial operator*(const Polynomial &first, const Polynomial &second);
const Polynomial operator*(const Polynomial &first, const int coef);
const Polynomial operator*(const int coef, const Polynomial &second);
const Polynomial& operator+=(Polynomial &first, const Polynomial &second);
const Polynomial& operator-=(Polynomial &first, const Polynomial &second);
const Polynomial& operator*=(Polynomial &first, const Polynomial &second);
const Polynomial& operator+=(Polynomial &first, const int coef);
const Polynomial& operator-=(Polynomial &first, const int coef);
const Polynomial& operator*=(Polynomial &first, const int coef);
const bool operator==(const Polynomial &first, const Polynomial &second);
const bool operator!=(const Polynomial &first, const Polynomial &second);

#endif
