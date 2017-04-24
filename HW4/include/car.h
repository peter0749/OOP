#ifndef INCLUDE_CARH
#define INCLUDE_CARH
class Car {
    private:
        std::string make;
        std::string model;
        static const int defaultYear;
        int year;
        int speed;
    public:
        Car(const std::string, const std::string, const int=2011);
        Car(const char*, const char*, const int=2011);
        bool Set(const std::string , const std::string , const int=2011);
        const std::string GetMake(void) const; 
        const std::string GetModel(void) const;
        const int GetYear(void) const;
        const int GetSpeed(void) const;
        void Display(void) const;
        const bool Accelerate(const char );
        const bool Brake(const char );
};


#endif
