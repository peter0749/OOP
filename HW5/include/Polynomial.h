#ifndef _INCLUDE_POLY
#define _INCLUDE_POLY

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
        void attach(CircularList &list) const {
            Node *temp=data->getNext();
            while(!( temp->getCoef()==0 && temp->getPower()==-1 )) {
                list.insert( temp->getCoef(), temp->getPower() );
                temp = temp->getNext();
            }
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
            read_ptr = read_ptr->getNext();
        }
        void resetReadPtr(void) {
            read_ptr = data->getNext();
        }
        bool isEmpty(void) const {
            return data->getNext()==data;
        }
        bool readEnd(void) const {
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
        ~CircularList() {
            Node *ptr = data->getNext();
            Node *last= data;
            Node *end = data;
            while(ptr!=end) {
                delete last;
                last = ptr;
                ptr = ptr->getNext();
            }
        }
};

class Polynomial {
    private:
        CircularList queue;
        int number;
    public:
        Polynomial() :number(0) {}
        Polynomial(Polynomial &cpy) :number(cpy.getSize()) {
            int n=number*2+2;
            int *a = new int[n];
            cpy.get(a, n);
            set(a, n);
            delete[] a;
        }
        Polynomial(int *arr, const int n) : number(0) {
            set(arr, n);
        }
        void insert(int coef, int power) {
            queue.insert(coef, power);
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
            queue.erase_all();
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
};

std::ostream &operator << (std::ostream &os, const Polynomial &P) {
    int n = P.getSize()*2+2;
    int *arr = new int[n];
    P.get(arr, n);
    if (P.getSize()>0) os << arr[0] << "^" << arr[1];
    for (int i=2; i+1<P.getSize()*2; i+=2) {
        os << (arr[i]>0?" +":" ") << arr[i];
        if (arr[i+1]!=0) {
            os << "^" << arr[i+1];
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
