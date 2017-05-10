#ifndef _INCLUDE_POLY
#define _INCLUDE_POLY
#include <iostream>

class Node {
    private:
        int coef, power;
        Node *next;
    public:
        Node() : coef(0), power(-1), next(NULL) {
            this->next = this;
        }
        Node *getNext(void) const {
            return next;
        }
        int getCoef(void) const {
            return coef;
        }
        int getPower(void) const {
            return power;
        }
        void setNext(Node *next) {
            this->next = next;
        }
        void setCoef(int coef) {
            this->coef = coef;
        }
        void setPower(int power) {
            this->power = power;
        }
};

class CircularList {
    private:
        Node *data;
        Node *read_ptr;
    public:
        CircularList() {
            data = new Node();
            read_ptr = data->getNext();
        }
        CircularList(const Node &nod) {
            data = new Node(nod);
            data->setNext(data); // loop back
            read_ptr = data->getNext();
        }
        void insert(int coef, int power) {
            Node *searchPtr=data->getNext();
            Node *lastPtr  =data;
            while (!( searchPtr->getCoef()==0 && searchPtr->getPower()==-1) &&\
                    searchPtr->getPower()>power) {
                lastPtr = searchPtr;
                searchPtr = searchPtr->getNext();
            }
            if (searchPtr->getPower()==power) {
                searchPtr->setCoef( searchPtr->getCoef()+coef );
            } else {
                Node *temp = new Node;
                temp->setCoef(coef);
                temp->setPower(power);
                temp->setNext(searchPtr);
                lastPtr->setNext(temp);
            }
        }
        const Node read(void) const {
            Node result( *read_ptr );
            result.setNext(&result);
            return result;
        }
        void nextReadPtr(void) {
            read_ptr =  read_ptr->getNext();
        }
        void resetReadPtr(void) {
            read_ptr = data->getNext();
        }
        const bool isEmpty(void) const {
            return data->getNext()==data;
        }
        const bool readEnd(void) const {
            return read_ptr->getCoef()==0 && read_ptr->getPower()==-1;
        }
        void toArray(int *a, int n) const {
            int top=0;
            Node *temp = data->getNext();
            while( !( temp->getCoef()==0 && temp->getPower()==-1 ) && top+2<n ) {
                a[top++] = temp->getCoef();
                a[top++] = temp->getPower();
                temp = temp->getNext();
            }
            a[top++] = 0;
            a[top++] = -1;
        }
        void clear() {
            Node *ptr = data->getNext();
            Node *last= data;
            Node *end = data;
            while(ptr!=end) {
                if (last!=end)
                    delete last;
                last = ptr;
                ptr = ptr->getNext();
            }
            data->setNext(data);
            this->resetReadPtr();
        }
        ~CircularList() {
            clear();
            delete data;
        }
};

class Polynomial {
    private:
        CircularList queue;
        int number;
        void _copy(const Polynomial &cpy) {
            int n=cpy.getSize()*2+2;
            int *a = new int[n];
            queue.clear();
            cpy.get(a, n);
            set(a, n);
            delete[] a;
        }
    public:
        Polynomial() :number(0) {}
        Polynomial(const Polynomial &cpy) :number(cpy.getSize()) {
            _copy(cpy);
        }
        Polynomial(int *arr, const int n) : number(0) {
            set(arr, n);
        }
        void insert(int coef, int power) {
            queue.insert(coef, power);
            ++number;
        }
        void insert(const Node &ref) {
            queue.insert(ref.getCoef(), ref.getPower());
            ++number;
        }
        int getSize(void) const {
            return number;
        }
        void get(int *a, int n) const {
            queue.toArray(a,n);
        }
        void set(int *a, int n) {
            if (n<4) return;
            number = 0;
            queue.clear();
            for (int i=0; i+1<n; i+=2) {
                if (a[i]==0 && a[i+1]==-1) break;
                queue.insert(a[i], a[i+1]);
                ++number;
            }
        }
        const Polynomial derivative(void) {
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
        const Node read(void) const {
            return queue.read();
        }
        void readNext(void) {
            queue.nextReadPtr();
        }
        void resetRead(void) {
            queue.resetReadPtr();
        }
        const bool readEnd(void) const {
            return queue.readEnd();
        }
        const Polynomial& operator=(const Polynomial &second) {
            if (this != &second) {
                _copy(second);
            }
            return *this;
        }
};

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

#endif
