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
        queue.insert(a[i], a[i+1]);
        ++number;
    }
}
const Polynomial Polynomial::derivative(void) {
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

const Polynomial operator+(Polynomial &first, int coef) {
    Polynomial result(first);
    result.insert(coef, 0);
    return result;
}
const Polynomial operator+(int coef, Polynomial &second) {
    return (second + coef);
}
const Polynomial operator+(Polynomial &first, Polynomial &second) {
    Polynomial result;
    first.resetRead() , second.resetRead();
    while(!first.readEnd() && !second.readEnd()) {
        Node node1 = first.read();
        Node node2 = second.read();
        if (node1.getPower()>node2.getPower()) {
            result.insert(node1);
            first.readNext();
        } else if (node1.getPower()<node2.getPower()) {
            result.insert(node2);
            second.readNext();
        } else {
            result.insert(node1.getCoef()+node2.getCoef(), node1.getPower());
            first.readNext(); second.readNext();
        }
    }
    first.resetRead() , second.resetRead();
    return result;
}

const Polynomial operator-(Polynomial &first, int coef) {
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

const Polynomial operator-(Polynomial &first, Polynomial &second) {
    Polynomial result;
    first.resetRead() , second.resetRead();
    while(!first.readEnd() && !second.readEnd()) {
        Node node1 = first.read();
        Node node2 = second.read();
        node2.setCoef(-node2.getCoef()); // negation
        if (node1.getPower()>node2.getPower()) {
            result.insert(node1);
            first.readNext();
        } else if (node1.getPower()<node2.getPower()) {
            result.insert(node2);
            second.readNext();
        } else {
            int temp = node1.getCoef()+node2.getCoef();
            if (temp)
                result.insert(temp, node1.getPower());
            first.readNext(); second.readNext();
        }
    }
    first.resetRead() , second.resetRead();
    return result;
}

const Polynomial operator*(Polynomial &first, Polynomial &second) {
    Polynomial result;
    first.resetRead();
    while(!first.readEnd()) {
        Node node1=first.read();
        second.resetRead();
        while(!second.readEnd()) {
            Node node2=second.read();
            result.insert(node1.getCoef()*node2.getCoef(), node1.getPower()+node2.getPower());
            second.readNext();
        }
        first.readNext();
    }
    first.resetRead(); second.resetRead();
    return result;
}

const Polynomial operator*(const Polynomial &ref, const int coef) {
    Polynomial result;
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

int Polynomial::_fast_pow(int x, int n) const {
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

const Polynomial& operator+=(Polynomial &first, Polynomial &second) {
    if (&first==&second) {
        first = first*2;
        return first;
    }
    first = first + second;
    return first;
}

const Polynomial& operator-=(Polynomial &first, Polynomial &second) {
    if (&first==&second) {
        first.clear();
        return first;
    }
    first = first - second;
    return first;
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
