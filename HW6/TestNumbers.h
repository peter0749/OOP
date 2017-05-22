#include <string>
#include <iostream>
#include "Number.h"
#ifndef _INCLUDE_TESTNUMBERS_H
#define _INCLUDE_TESTNUMBERS_H
class TestNumbers {
    private:
        inline static bool isNumber(BaseNumber *base);
        inline static bool isTwoDigitNumber(BaseNumber *base);
        inline static bool isThreeDigitNumber(BaseNumber *base);
    public:
        static Number getFirstDigit (int n);
        static Number getSecondDigit (int n);
        static Number** genNums (const int=100, const int=1000);
        static std::string printAvg (Number** nums, const size_t=100);
};

#endif
