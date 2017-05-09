#ifndef _INCLUDE_POLY
#define _INCLUDE_POLY

class Node {
    private:
        int coef, power;
        Node *next;
    public:
        Node(int c, int p, Node *next) : coef(c), power(p), next(next) {};
        Node *getNext(void) const {
            return next;
        }
        int getCoef(void) const {
            return coef;
        }
        int getPower(void) const {
            return power;
        }
        void setNext(Node *next) const {
            this->next = next;
        }
        void setCoef(int coef) const {
            this->coef = coef;
        }
        void setPower(int power) const {
            this->power = power;
        }
};

class CircularList {
    private:
        Node *data;
        Node *data_ptr;
    public:
        CircularList() {
            data = new Node(0,-1,NULL);
            data->setNext(data); // loop back
            data_ptr = data;
        }
        void insert(int coef, int power) {
            Node *temp = new Node(coef,power,data);
            data_ptr->setNext(temp);
            data_ptr = temp;
        }
        void erase_one(void) {
            if(data_ptr!=data) {
                Node *temp = data_ptr;
                data_ptr = data_ptr->getNext();
                delete temp;
            }
        }
        bool isEmpty(void) {
            return data==data_ptr;
        }
        ~CircularList() {
            while(!isEmpty()) {
            }
        }
};

class Polynomial {
    private:
    public:
};
#endif
