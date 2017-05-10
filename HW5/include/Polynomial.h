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
        Node *data_ptr;
        Node *read_ptr;
    public:
        CircularList() {
            data = new Node();
            data_ptr = data;
            read_ptr = data->getNext();
        }
        CircularList(const Node &nod) {
            data = new Node(nod);
            data->setNext(data); // loop back
            data_ptr = data;
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
            Node *temp = new Node;
            temp->setCoef(coef);
            temp->setPower(power);
            temp->setNext(data);
            data_ptr->setNext(temp);
            data_ptr = temp;
        }
        void erase_last(void) {
            if(data_ptr!=data) {
                Node *temp = data_ptr;
                data_ptr = data_ptr->getNext();
                delete temp;
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
            return data==data_ptr;
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
            while(!isEmpty()) {
                erase_last();
            }
            delete data;
        }
};

class Polynomial {
    private:
        CircularList queue;
        int number;
    public:
        Polynomial() :number(0) {}
        Polynomial(Polynomial &cpy) :number(cpy.getSize()*2) {
            int n=number;
            int *a = new int[n];
            cpy.get(a, n);
            set(a, n);
            delete[] a;
        }
        int getSize(void) const {
            return number;
        }
        void get(int *a, int n) const {
            queue.toArray(a,n);
        }
        void set(int *a, int n) {
            if (n<4) return;
            for (int i=0; i<n; i+=2) {
                if (a[i]==0 && a[i+1]==-1) break;
                queue.insert(a[i], a[i+1]);
                ++number;
            }
        }
};
#endif
