#include "TestNumbers.h"

inline bool TestNumbers::isNumber(BaseNumber *base) {
    Number* inst = dynamic_cast<Number*>(base);
    return inst!=NULL;
}
inline bool TestNumbers::isTwoDigitNumber(BaseNumber *base) {
    TwoDigitNumber* inst = dynamic_cast<TwoDigitNumber*>(base);
    return inst!=NULL;
}
inline bool TestNumbers::isThreeDigitNumber(BaseNumber *base) {
    ThreeDigitNumber* inst = dynamic_cast<ThreeDigitNumber*>(base);
    return inst!=NULL;
}

Number TestNumbers::getFirstDigit (int n) {
    Number ret((n/10)%10);
    return ret;
}
Number TestNumbers::getSecondDigit (int n) {
    Number ret(n%10);
    return ret;
}
Number** TestNumbers::genNums (const int num, const int lim) {
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
std::string TestNumbers::printAvg (Number** nums, const size_t num) {
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

