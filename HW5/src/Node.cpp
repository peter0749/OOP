#include "../include/Node.h"
Node::Node() : coef(0), power(-1), next(0) {
    this->next = this;
}
Node* Node::getNext(void) const {
    return next;
}
int Node::getCoef(void) const {
    return coef;
}
int Node::getPower(void) const {
    return power;
}
void Node::setNext(Node *next) {
    this->next = next;
}
void Node::setCoef(int coef) {
    this->coef = coef;
}
void Node::setPower(int power) {
    this->power = power;
}
