#include <iostream>
#include "../include/Polynomial.h"
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
            result.insert(node1.getCoef()+node2.getCoef(), node1.getPower());
            first.readNext(); second.readNext();
        }
    }
    first.resetRead() , second.resetRead();
    return result;
}
std::ostream &operator << (std::ostream &os, const Polynomial &P) {
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
    return os;
}

std::istream &operator >> (std::istream &is, Polynomial &P) {
    int coef, power;
    while(is>>coef>>power && !(coef==0 && power==-1)) {
        P.insert(coef, power);
    }
    return is;
}
