#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include "Graph.hpp"

using namespace std; // <--- Not in header file, it's okay.

inline void cleanupSTDIN_BUFF (void) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

template <class T>
inline void inputObj(T &ref) {
    const string errMsg = "Wrong input format.";
    while (true) {
        cin >> ref;
        if (cin.fail()) {
            cerr << errMsg << endl;
            cleanupSTDIN_BUFF();
        } else break;
    }
}

inline void inputXY(double &x, double &y) {
    const string errMsg = "Wrong input format.";
    while(true) {
        cin >> x >> y;
        if(cin.fail()) {
            cerr<< errMsg << " Please input two doubles."<<endl;
            cleanupSTDIN_BUFF();
        } else break;
    }
}

int main(void) {
    Line l(0, 0, 1, 1);
    Line k;
    Line n(1, 2, 3, 3);

    cout << "slope of l = " << l.slope() << endl;
    cout << "slope of k = " << k.slope() << endl;
    cout << "slope of n = " << n.slope() << endl;
    n.vshift(2.0);
    cout << n << k << l << endl;
    cout << "Enter a line (4 doubles): ";
    Line x;
    inputObj(x);
    //cin >> x;
    cout << "Input line is: " << x << endl;
    cout << "The Y-intercept of input line is: " << x.y_intercept() << endl;

    cout << "Enter a line2 (4 doubles): ";
    Line2 y;
    inputObj(y);
    //cin >> y;
    cout << "Input line2 is: " << y << endl;
    Line2 z;
    y.normal(z);
    cout << "Normal of line2 is: " << z << endl;


    // Test Circle and Circle2 here...

    // Note: The code above is given by TAs. I only modify inputs...
    double i(0), j(0);

    // Test Circle
    Circle circle;
    cout << "Enter a circle (3 doubles, x, y, radius): ";
    inputObj(circle);
    //cin >> circle;
    cout << "Input circle is (x, y, radius): " << circle << endl;
    cout << "Enter x, y: " << endl;
    inputXY(i,j);
    //cin >> i >> j;
    cout << "(" << i << "," << j << ") is " << (circle.is_inside(i, j)?"inside":"outside");
    cout << " of the circle " << circle << endl;

    // Test Circle2
    Circle2 circle2;
    cout << "Enter a circle2 (4 doubles, x0, y0, x1, y1): ";
    inputObj(circle2);
    //cin >> circle2;
    cout << "Input circle2 is: " << circle2 << endl;
    cout << "Enter x, y: " << endl;
    inputXY(i,j);
    //cin >> i >> j;
    cout << "(" << i << "," << j << ") is " << (circle2.is_inside(i, j)?"inside":"outside");
    cout << " of the circle2 " << circle2 << endl;

    return 0;
}
