#ifndef _INCLUDE_NODE
#define _INCLUDE_NODE
class Node {
    private:
        int coef, power;
        Node *next;
    public:
        Node();
        Node *getNext(void) const;
        int getCoef(void) const;
        int getPower(void) const;
        void setNext(Node *next);
        void setCoef(int coef);
        void setPower(int power);
};
#endif
