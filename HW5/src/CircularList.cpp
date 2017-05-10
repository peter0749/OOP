#include "../include/CircularList.h"
CircularList::CircularList() {
    data = new Node();
    read_ptr = data->getNext();
}
CircularList::CircularList(const Node &nod) {
    data = new Node(nod);
    data->setNext(data); // loop back
    read_ptr = data->getNext();
}
void CircularList::insert(int coef, int power) {
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
const Node CircularList::read(void) const {
    Node result( *read_ptr );
    result.setNext(&result);
    return result;
}
void CircularList::nextReadPtr(void) {
    read_ptr =  read_ptr->getNext();
}
void CircularList::resetReadPtr(void) {
    read_ptr = data->getNext();
}
const bool CircularList::isEmpty(void) const {
    return data->getNext()==data;
}
const bool CircularList::readEnd(void) const {
    return read_ptr->getCoef()==0 && read_ptr->getPower()==-1;
}
void CircularList::toArray(int *a, int n) const {
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
void CircularList::clear() {
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
CircularList::~CircularList() {
    clear();
    delete data;
}
