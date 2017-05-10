#include <iostream>
#include "../include/Polynomial.h"
void Polynomial::clear(void) {
    queue.clear();
    number=0;
}
void Polynomial::_copy(const Polynomial &cpy) {
    int n=cpy.getSize()*2+2;
    int *a = new int[n];
    queue.clear();
    cpy.get(a, n);
    set(a, n);
    delete[] a;
}
Polynomial::Polynomial() :number(0) {}
Polynomial::Polynomial(const Polynomial &cpy) :number(cpy.getSize()) {
    _copy(cpy);
}
Polynomial::Polynomial(int *arr, const int n) : number(0) {
    set(arr, n);
}
void Polynomial::insert(int coef, int power) {
    queue.insert(coef, power);
    ++number;
}
void Polynomial::insert(const Node &ref) {
    queue.insert(ref.getCoef(), ref.getPower());
    ++number;
}
int Polynomial::getSize(void) const {
    return number;
}
void Polynomial::get(int *a, int n) const {
    queue.toArray(a,n);
}
void Polynomial::set(int *a, int n) {
    if (n<4) return;
    number = 0;
    queue.clear();
    for (int i=0; i+1<n; i+=2) {
        if (a[i]==0 && a[i+1]==-1) break;
        if (a[i]==0) continue;
        queue.insert(a[i], a[i+1]);
        ++number;
    }
}
Polynomial Polynomial::derivative(void) {
    int n = this->number*2+2;
    int *a = new int[n];
    queue.toArray(a,n);
    for (int i=0; i+1<n; i+=2) {
        if (a[i]==0 && a[i+1]==-1) break;
        a[i] *= a[i+1];
        --a[i+1];
    }
    Polynomial result(a, n-2);
    delete[] a;
    return result;
}
const Node Polynomial::read(void) const {
    return queue.read();
}
void Polynomial::readNext(void) {
    queue.nextReadPtr();
}
void Polynomial::resetRead(void) {
    queue.resetReadPtr();
}
const bool Polynomial::readEnd(void) const {
    return queue.readEnd();
}
const Polynomial& Polynomial::operator=(const Polynomial &second) {
    if (this != &second) {
        _copy(second);
    }
    return *this;
}

const Polynomial operator+(const Polynomial &first, const int coef) {
    Polynomial result(first);
    result.insert(coef, 0);
    return result;
}
const Polynomial operator+(const int coef, const Polynomial &second) {
    return (second + coef);
}
const Polynomial operator+(const Polynomial &first, const Polynomial &second) {
    Polynomial result;
    int *a = new int[first.getSize()*2+2];
    int *b = new int[second.getSize()*2+2];
    first.get(a,first.getSize()*2+2);
    second.get(b,second.getSize()*2+2);
    int i=0, j=0;
    while (!(a[i*2]==0&&a[i*2+1]==-1) && !(b[j*2]==0&&b[j*2+1]==-1)) {
        if (a[i*2+1]>b[j*2+1]) {
            result.insert(a[i*2], a[i*2+1]);
            ++i;
        } else if (a[i*2+1]<b[j*2+1]) {
            result.insert(b[j*2], b[j*2+1]);
            ++j;
        } else {
            if (a[i*2]+b[j*2]!=0)
                result.insert(a[i*2]+b[j*2], a[i*2+1]);
            ++j; ++i;
        }
    }
    while (!(a[i*2]==0&&a[i*2+1]==-1)) {
        result.insert(a[i*2], a[i*2+1]);
        ++i;
    }
    while (!(b[j*2]==0&&b[j*2+1]==-1)) {
        result.insert(b[j*2], b[j*2+1]);
        ++j;
    }
    delete[] a;
    delete[] b;
    return result;
}

const Polynomial operator-(const Polynomial &first, const int coef) {
    return (first + (-coef));
}

const Polynomial operator-(const Polynomial &ref) {
    Polynomial result;
    int n = ref.getSize()*2+2;
    int *a = new int[n];
    ref.get(a,n);
    for (int i=0; i<ref.getSize(); ++i) {
        a[i*2] = -a[i*2];
    }
    result.set(a,n);
    delete[] a;
    return result;
}

const Polynomial operator-(int coef, const Polynomial &second) {
    Polynomial result(-second);
    return (result + coef);
}

const Polynomial operator-(const Polynomial &first, const Polynomial &second) {
    Polynomial result;
    int *a = new int[first.getSize()*2+2];
    int *b = new int[second.getSize()*2+2];
    int i=0, j=0;
    first.get(a,first.getSize()*2+2);
    second.get(b,second.getSize()*2+2);
    while (!(a[i*2]==0&&a[i*2+1]==-1) && !(b[j*2]==0&&b[j*2+1]==-1)) {
        if (a[i*2+1]>b[j*2+1]) {
            result.insert(a[i*2], a[i*2+1]);
            ++i;
        } else if (a[i*2+1]<b[j*2+1]) {
            result.insert(-b[j*2], b[j*2+1]);
            ++j;
        } else {
            if(a[i*2]-b[j*2]!=0)
                result.insert(a[i*2]-b[j*2], a[i*2+1]);
            ++j; ++i;
        }
    }
    while (!(a[i*2]==0&&a[i*2+1]==-1)) {
        result.insert(a[i*2], a[i*2+1]);
        ++i;
    }
    while (!(b[j*2]==0&&b[j*2+1]==-1)) {
        result.insert(-b[j*2], b[j*2+1]);
        ++j;
    }
    delete[] a;
    delete[] b;
    return result;
}

const Polynomial operator*(const Polynomial &first, const Polynomial &second) {
    Polynomial result;
    int *a = new int[first.getSize()*2+2];
    int *b = new int[second.getSize()*2+2];
    first.get(a,first.getSize()*2+2);
    second.get(b,second.getSize()*2+2);
    for (int i=0; i<first.getSize(); ++i) {
        for (int j=0; j<second.getSize(); ++j) {
            result.insert(a[i*2]*b[j*2], a[i*2+1]+b[j*2+1]);
        }
    }
    delete[] a;
    delete[] b;
    return result;
}

const Polynomial operator*(const Polynomial &ref, const int coef) {
    Polynomial result;
    if (coef==0) return result;
    int n = ref.getSize()*2+2;
    int *a = new int[n];
    ref.get(a,n);
    for (int i=0; i<ref.getSize(); ++i) {
        a[i*2] = a[i*2]*coef;
    }
    result.set(a,n);
    delete[] a;
    return result;
}

const Polynomial operator*(const int coef, const Polynomial &ref) {
    return ref * coef;
}

int Polynomial::_fast_pow(const int x, int n) const {
    int ans=1, temp=x;
    while(n) {
        if (n&1) {
            ans*=temp;
        }
        temp*=temp;
        n>>=1;
    }
    return ans;
}

const int Polynomial::operator()(const int x) const {
    int n = this->getSize()*2 + 2;
    int *a = new int[n];
    int ans=0;
    this->get(a, n);
    for (int i=0; i<this->getSize(); ++i) {
        ans += a[i*2]*_fast_pow(x, a[i*2+1]);
    }
    delete[] a;
    return ans;
}

const Polynomial& operator+=(Polynomial &first, const Polynomial &second) {
    if (&first==&second) {
        first = first*2;
        return first;
    }
    first = first + second;
    return first;
}

const Polynomial& operator-=(Polynomial &first, const Polynomial &second) {
    if (&first==&second) {
        first.clear();
        return first;
    }
    first = first - second;
    return first;
}

const Polynomial& operator*=(Polynomial &first, const Polynomial &second) {
    first = first * second;
    return first;
}

const Polynomial& operator+=(Polynomial &first, const int coef) {
    first = first + coef;
    return first;
}

const Polynomial& operator-=(Polynomial &first, const int coef) {
    first = first - coef;
    return first;
}

const Polynomial& operator*=(Polynomial &first, const int coef) {
    first = first * coef;
    return first;
}

const bool operator==(const Polynomial &first, const Polynomial &second) {
    if (first.getSize()!=second.getSize()) return false;
    int n  = first.getSize();
    int *a = new int[n*2+2];
    int *b = new int[n*2+2];
    first.get(a,n*2+2);
    second.get(b,n*2+2);
    for (int i=0; i<n; ++i) {
        if (a[i*2]!=b[i*2] || a[i*2+1]!=b[i*2+1]) return false;
    }
    delete[] a;
    delete[] b;
    return true;
}

const bool operator!=(const Polynomial &first, const Polynomial &second) {
    return !(first==second);
}

std::ostream &operator << (std::ostream &os, const Polynomial &P) {
    if (P.getSize()==0) {
        os << "0";
        return os;
    }
    int n = P.getSize()*2+2;
    int *arr = new int[n];
    P.get(arr, n);
    if (P.getSize()>0) os << arr[0] << "x^" << arr[1];
    for (int i=2; i+1<P.getSize()*2; i+=2) {
        os << (arr[i]>0?" +":" ") << arr[i];
        if (arr[i+1]!=0) {
            os << "x^" << arr[i+1];
        }
    }
    delete[] arr;
    return os;
}

std::istream &operator >> (std::istream &is, Polynomial &P) {
    int coef, power;
    while(is>>coef>>power && !(coef==0 && power==-1)) {
        P.insert(coef, power);
    }
    return is;
}
