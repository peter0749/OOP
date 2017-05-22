#include "Number.h"

Number::Number () { this->n =0; }
Number::Number (int n) : n(n) {
    if(n<0||n>9) exit(1);
}
// Check that n is a 1-digit number,
// if not, terminate using exit ()
// initialize instance variable to n

Number::Number (const Number& n) : n(n.getNumber()) {/*empty*/} // Initialize instance variable
void Number::guessWho(void) {
    std::cout << "I'm Number!" <<std::endl;
}
int Number::getNumber (void) const {
    return this->n;
} // Return the 1-digit number
bool Number::equals (Number n) const {
    return this->n == n.getNumber();
}
// Return true if this number is equal to n
bool Number::compare (Number n) const {
    return this->n > n.getNumber();
}
// Return true if this number is greater than n
std::string Number::toString() {
    char ch = (char)this->n + '0';
    std::string ret(1,ch);
    return ret;
}
bool Number::_check_valid(const int n) const {
    return n>=0 && n<=9;
}


int TwoDigitNumber::getN1(void) const {
    return this->n1;
}
int TwoDigitNumber::getN2(void) const {
    return this->n2;
}
TwoDigitNumber::TwoDigitNumber () : n1(0), n2(0) {/*empty*/} // Initialize all digits to 0
TwoDigitNumber::TwoDigitNumber (const Number &n1, const Number &n2) :n1(n1.getNumber()), n2(n2.getNumber()) {
    if (!(_check_valid(this->n1)&&_check_valid(this->n2))) exit(2);
}
void TwoDigitNumber::guessWho() {
    std::cout<<"I'm TwoDigitNumber!"<<std::endl;
}
// Initialize all digits to n1 and n2
bool TwoDigitNumber::equals (TwoDigitNumber n) {
    return this->n1==n.getN1() && this->n2==n.getN2();
}
// Return true if this TwoDigitNumber number
// is equal to n
bool TwoDigitNumber::compare (TwoDigitNumber n) {
    if (this->n1 > n.getN1()) return true;
    if (this->n1 == n.getN1()) return this->n2 > n.getN2();
    return false;
}
// Return true if this number is greater than n
// Example: 21 > 11 and 10 > 08
std::string TwoDigitNumber::toString() {
    char ch1 = (char)n1 + '0';
    char ch2 = (char)n2 + '0';
    std::string str("");
    str += ch1;
    str += ch2;
    return str;
}
// Return a string consisting of this
// TwoDigitNumber; for example 11 or 04.

// Return a string consisting of this number


ThreeDigitNumber::ThreeDigitNumber (const Number &n1,
        const TwoDigitNumber &n2) :n1(n1), n2(n2) {/*empty*/}
// Initialize all digits to n1 and n2
Number ThreeDigitNumber::getN1(void) const {
    return this->n1;
}
TwoDigitNumber ThreeDigitNumber::getN2(void) const {
    return this->n2;
}
void ThreeDigitNumber::guessWho() {
    std::cout<<"I'm ThreeDigitNumber!"<<std::endl;
}
bool ThreeDigitNumber::equals (const ThreeDigitNumber &n) const {
    return getN1().equals(n.getN1()) && getN2().equals(n.getN2());
}
// Return true if this ThreeDigitNumber number
// is equal to n
bool ThreeDigitNumber::compare (ThreeDigitNumber n) const {
    Number inst = getN1();
    if (inst.compare(n.getN1())) return true;
    if (inst.equals(n.getN1()) ) return getN2().compare(n.getN2());
    return false;
}
// Return true if this number is greater than n
std::string ThreeDigitNumber::toString() {
    std::string str("");
    str += this->n1.toString();
    str += this->n2.toString();
    return str;
}
// Return a string consisting of this
// ThreeDigitNumber, for example 111 or 003.

