// SAMPLE driver program that uses the Car class.

// ADD in your own calls to Car member functions to more thoroughly
// test the features, or feel free to write your own main program
// with other tests and uses of the Car class.

#include <iostream>
#include <string>
#include "../include/car.h"
using namespace std;
int main(){
    Car car1("Ford", "Crown Victoria", 1997);
    Car car2("Chevrolet", "Camaro");
    Car car3("Hyundai", "Sonata", -15);

    cout << "\n*** Displaying each car's stats\n";
    cout << "Car1:\n";
    car1.Display();
    cout << "\nCar2:\n";
    car2.Display();
    cout << "\nCar3:\n";
    car3.Display();

    cout << "\n*** Accelerating car 3 several times:\n";
    car3.Accelerate('h'); // accelerate hard
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Accelerate('M'); // accelerate medium
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Accelerate('L'); // accelerate low
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Accelerate('L'); // accelerate low
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Accelerate('Z'); // accelerate with invalid level
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';

    cout << "\n*** Resetting car make/models\n";
    car1.Set("Flinstones", "Rock Car", -2100);
    car3.Set("Toyota", "Camry", 2005);
    cout << "Car1:\n";
    car1.Display();
    cout << "\nCar3:\n";
    car3.Display();

    cout << "\n*** Decelerating car3\n";
    car3.Brake('m');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Brake('L');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Brake('l');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Brake('M');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Brake('A');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';
    car3.Brake('H');
    cout << "Car3 speed: " << car3.GetSpeed() << '\n';

    cout << "\n*** Calling accessors\n";
    cout << "Car1:\n";
    cout << " Make: " << car1.GetMake() << '\n'
         << " Model: " << car1.GetModel() << '\n'
         << " Year: " << car1.GetYear() << '\n';
    cout << "Car2:\n";
    cout << " Make: " << car2.GetMake() << '\n'
         << " Model: " << car2.GetModel() << '\n'
         << " Year: " << car2.GetYear() << '\n';
    cout << "Car1:\n";
    cout << " Make: " << car3.GetMake() << '\n'
         << " Model: " << car3.GetModel() << '\n'
         << " Year: " << car3.GetYear() << '\n';
    return 0;
}
