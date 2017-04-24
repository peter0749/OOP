#include <string>
#include <iostream>
#include "../include/car.h"

const int Car::defaultYear=2011;
Car::Car(const char *arg_make, const char *arg_model, const int arg_year) : year(arg_year), speed(0) {
    this->make = arg_make;
    this->model = arg_model;
    if (this->year<0) this->year = this->defaultYear;
}
Car::Car(const std::string arg_make, const std::string arg_model, const int arg_year) : make(arg_make), model(arg_model), year(arg_year), speed(0) {
    if (this->year<0) this->year = this->defaultYear;
    // do nothing
}
bool Car::Set( const std::string make,  const std::string model, const int year) {
    if (year<0) return false;
    this->make = make;
    this->model = model;
    this->year = year;
    return true;
}
const std::string Car::GetMake(void) const {
    return this->make;
}
const std::string Car::GetModel(void) const {
    return this->model;
}
const int Car::GetYear(void) const {
    return this->year;
}
const int Car::GetSpeed(void) const {
    return this->speed;
}
void Car::Display(void) const {
    std::cout << "Your car is a " << this->year << " " << this->make << " " << this->model << std::endl << "And it is currently going " << this->speed << " MPH" << std::endl;
}
const bool Car::Accelerate(const char command) {
    if (command=='H'||command=='h') {
        this->speed += 10;
        return true;
    } else if (command=='M'||command=='m') {
        this->speed += 5;
        return true;
    } else if (command=='L'||command=='l') {
        ++this->speed;
        return true;
    } 
    // else
    return false;
}
const bool Car::Brake(const char command) {
    if (this->speed==0) return false;
    bool ret=false;
    if (command=='H'||command=='h') {
        this->speed -= 10;
        ret=true;
    } else if (command=='M'||command=='m') {
        this->speed -= 5;
        ret=true;
    } else if (command=='L'||command=='l') {
        --this->speed;
        ret=true;
    } 
    if (this->speed<0) this->speed = 0;
    // else
    return ret;
}
