#include <iostream>
#include <typeinfo>
#include <string>
#include <cstdlib>
// Class representing 1-digit natural numbers (from 0 to 9)
class BaseNumber {
    public:
        virtual void guessWho() = 0;
        virtual std::string toString() = 0;
};
class Number : public BaseNumber {
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
        virtual void guessWho(void) {
            std::cerr << "I'm Number!" <<std::endl;
        }
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
        virtual void guessWho() {
            std::cout<<"I'm TwoDigitNumber!"<<std::endl;
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
        virtual void guessWho() {
            std::cerr<<"I'm ThreeDigitNumber!"<<std::endl;
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

class TestNumbers {
    private:
        inline static bool isNumber(BaseNumber *base) {
            Number* inst = dynamic_cast<Number*>(base);
            return inst!=NULL;
        }
        inline static bool isTwoDigitNumber(BaseNumber *base) {
            TwoDigitNumber* inst = dynamic_cast<TwoDigitNumber*>(base);
            return inst!=NULL;
        }
        inline static bool isThreeDigitNumber(BaseNumber *base) {
            ThreeDigitNumber* inst = dynamic_cast<ThreeDigitNumber*>(base);
            return inst!=NULL;
        }
    public:
        Number getFirstDigit (int n) {
            Number ret(n%10);
            return ret;
        }
        Number getSecondDigit (int n) {
            Number ret((n/10)%10);
            return ret;
        }
        static Number** genNums (const int num=100, const int lim=1000) {
            Number **ptr = new Number*[num];
            for (int i=0; i<num; ++i) {
                int temp = rand()%lim;
                if (temp<10) {
                    ptr[i] = new Number(temp);
                } else if (temp<100) {
                    ptr[i] = new TwoDigitNumber(Number(temp/10), Number(temp%10));
                } else {
                    ptr[i] = new ThreeDigitNumber(Number(temp/100),\
                            TwoDigitNumber(Number((temp/10)%10), Number(temp%10)));
                }
            }
            return ptr;
        }
        static std::string printAvg (Number** nums, const size_t num=100) {
            BaseNumber **ptr = (BaseNumber**)nums; //Downcasting. It's okay.
            std::string ret("");
            int counter=0, sum=0;
            for (int i=0; i<num; ++i) {
                if (isThreeDigitNumber(ptr[i])) {
                    ThreeDigitNumber *tptr = (ThreeDigitNumber*)ptr[i];
                    Number n1 = tptr->getN1();
                    TwoDigitNumber n2 = tptr->getN2();
                    int number = n1.getNumber()*100 + n2.getN1()*10 + n2.getN2();
                    sum+=number;
                    ++counter;
                }
            }
            sum/=counter;
            ret += (char)( (sum/100)%10 + '0' );
            ret += (char)( (sum/10)%10 + '0' );
            ret += (char)( sum%10 + '0' );
            return ret;
        }
};

using namespace std;

int main(void) {
    srand(3);
    Number **arr = TestNumbers::genNums();
    cout << "Test random Numbers: " << TestNumbers::printAvg(arr) << endl;
    delete[] arr;
    Number n1(3), n2(6);
    TwoDigitNumber n3(n1, n2);
    ThreeDigitNumber n4(n1, n3);
    cout << "Number: " << n1.toString() << endl;
    cout << "Number: " << n2.toString() << endl;
    cout << "TwoDigitNumber: " << n3.toString() << endl;
    cout << "ThreeDigitNumber: " << n4.toString() << endl;
    ThreeDigitNumber *arr2[7];
    for (int i=0; i<7; ++i) {
        n1=Number(i); n2=Number(i); n3=TwoDigitNumber(n1,n2);
        arr2[i] = new ThreeDigitNumber(n1,n3);
        cout << "ThreeDigitNumber in array[" << i << "] :" << arr2[i]->toString() << endl;
    }
    cout << "Average: " << TestNumbers::printAvg((Number**)arr2,7) << endl;
    return 0;
}
