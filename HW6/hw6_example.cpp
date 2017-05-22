#include <string>
// Class representing 1-digit natural numbers (from 0 to 9)
class Number {
    // Declare a protectedinstance variable:
    // n, 1-digit integer initialized to 0
    private:
        int n; 
    public:
        Number () { this->n =0; }
        Number (int n) : n(n) {
            if(n<0||n>9) exit(1);
        }
        // Check that n is a 1-digit number,
        // if not, terminate using exit ()
        // initialize instance variable to n

        Number (const Number& n) : n(n.getNumber()) {/*empty*/} // Initialize instance variable
        int getNumber (void) const { 
            return this->n;
        } // Return the 1-digit number
        bool equals (Number n) const {
            return this->n == n.getNumber();
        }
        // Return true if this number is equal to n
        bool compare (Number n) const {
            return this->n > n.getNumber();
        }
        // Return true if this number is greater than n
        std::string toString() {
            char ch = (char)this->n + '0';
            std::string ret(1,ch);
            return ret;
        }
        bool _check_valid(const int n) const {
            return n>=0 && n<=9;
        }
        // Return a string consisting of this number
};

// Class representing 2-digit numbers (from 00 to 99)
class TwoDigitNumber: public Number{
    // Declare two protectedinstance variables
    // n1, Numberrepresenting first digit
    // n2, Numberrepresenting second digit
    private:
        int n1, n2;
    public:
        int getN1(void) const {
            return this->n1;
        }
        int getN2(void) const {
            return this->n2;
        }
        TwoDigitNumber () : n1(0), n2(0) {/*empty*/} // Initialize all digits to 0
        TwoDigitNumber (const Number &n1, const Number &n2) :n1(n1.getNumber()), n2(n2.getNumber()) {
            if (!(_check_valid(this->n1)&&_check_valid(this->n2))) exit(2);
        }
        // Initialize all digits to n1 and n2
        bool equals (TwoDigitNumber n) {
            return this->n1==n.getN1() && this->n2==n.getN2();
        }
        // Return true if this TwoDigitNumber number
        // is equal to n
        bool compare (TwoDigitNumber n) {
            if (this->n1 > n.getN1()) return true;
            if (this->n1 == n.getN1()) return this->n2 > n.getN2();
            return false;
        }
        // Return true if this number is greater than n
        // Example: 21 > 11 and 10 > 08
        std::string toString() {
            char ch1 = (char)n1 + '0';
            char ch2 = (char)n2 + '0';
            std::string str("");
            str += ch1;
            str += ch2;
            return str;
        }
        // Return a string consisting of this
        // TwoDigitNumber; for example 11 or 04.
};

// Class representing 3-digit numbers (from 000 to 999)
class ThreeDigitNumber: public TwoDigitNumber {
    // Declare two protectedinstance variables
    // n1, Numberrepresenting first digit
    // n2, TwoDigitNumberrepresenting next 2-digits
    private:
        Number n1;
        TwoDigitNumber n2;
    public:
        ThreeDigitNumber (const Number &n1,
                const TwoDigitNumber &n2) :n1(n1), n2(n2) {/*empty*/}
        // Initialize all digits to n1 and n2
        Number getN1(void) const {
            return this->n1;
        }
        TwoDigitNumber getN2(void) const {
            return this->n2;
        }
        bool equals (const ThreeDigitNumber &n) const {
            return getN1().equals(n.getN1()) && getN2().equals(n.getN2());
        }
        // Return true if this ThreeDigitNumber number
        // is equal to n
        bool compare (ThreeDigitNumber n) const {
            Number inst = getN1();
            if (inst.compare(n.getN1())) return true;
            if (inst.equals(n.getN1()) ) return getN2().compare(n.getN2());
            return false;
        }
        // Return true if this number is greater than n
        std::string toString() {
            std::string str("");
            str += this->n1.toString();
            str += this->n2.toString();
            return str;
        }
        // Return a string consisting of this
        // ThreeDigitNumber, for example 111 or 003.
};

