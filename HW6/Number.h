#include <iostream>
#include <string>
#ifndef _INCLUDE_NUMBER_H
#define _INCLUDE_NUMBER_H
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
        Number ();
        Number (int n);
        // Check that n is a 1-digit number,
        // if not, terminate using exit ()
        // initialize instance variable to n
        Number (const Number& n);// Initialize instance variable
        virtual void guessWho(void);
        int getNumber (void) const; // Return the 1-digit number
        bool equals (Number n) const;  // Return true if this number is equal to n
        bool compare (Number n) const;  // Return true if this number is greater than n
        std::string toString();
        bool _check_valid(const int n) const;  // Return a string consisting of this number
};

// Class representing 2-digit numbers (from 00 to 99)
class TwoDigitNumber: public Number{
    // Declare two protectedinstance variables
    // n1, Numberrepresenting first digit
    // n2, Numberrepresenting second digit
    private:
        int n1, n2;
    public:
        int getN1(void) const;
        int getN2(void) const;
        TwoDigitNumber (); // Initialize all digits to 0
        TwoDigitNumber (const Number &n1, const Number &n2);
        virtual void guessWho();  // Initialize all digits to n1 and n2
        bool equals (TwoDigitNumber n);  // Return true if this TwoDigitNumber number
        // is equal to n
        bool compare (TwoDigitNumber n);  // Return true if this number is greater than n
        // Example: 21 > 11 and 10 > 08
        std::string toString(); // Return a string consisting of this
        // TwoDigitNumber; for example 11 or 04.
};

class ThreeDigitNumber: public TwoDigitNumber {
    // Declare two protectedinstance variables
    // n1, Numberrepresenting first digit
    // n2, TwoDigitNumberrepresenting next 2-digits
    private:
        Number n1;
        TwoDigitNumber n2;
    public:
        ThreeDigitNumber (const Number &n1,
                const TwoDigitNumber &n2);
        // Initialize all digits to n1 and n2
        Number getN1(void) const;
        TwoDigitNumber getN2(void) const;
        virtual void guessWho();
        bool equals (const ThreeDigitNumber &n) const;
        // Return true if this ThreeDigitNumber number
        // is equal to n
        bool compare (ThreeDigitNumber n) const;
        // Return true if this number is greater than n
        std::string toString();
        // Return a string consisting of this
        // ThreeDigitNumber, for example 111 or 003.
};


#endif
