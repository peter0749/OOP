// Main Program Example for HW5

// You can use this file as your main program, or add more functions if you want.
// Please ***MAKE SURE*** that your class works fine in this main program.
// TA will test your class by this program with additional test data.


#include "include/global.h"
#include "include/Node.h"
#include "include/CircularList.h"
#include "include/Polynomial.h"
// ****If you need to include more header files, add it here****

using std::cout;
using std::cin;
using std::endl;

int main(){
	// Help section
	cout << "-------------------------------------------------------------" << endl;
	cout << "Please Type in coefficients and exponents, seperated by SPACE" << endl;
	cout << ", and add 0 -1 in the end" << endl;
	cout << "For example, if you wish to assign P1 as 5x^3 -4x^2 + x -9" << endl;
	cout << "Type: 5 3 -4 2 1 1 -9 0 0 -1"<<endl;
	cout << "-------------------------------------------------------------" << endl << endl;

	Polynomial P1, P2, P3, P4;
	cout << "* Assign values for polynomial P1 *" << endl;
	cout << "Input: ";
	cin >> P1;
	cout << "P1 is: " << P1 << endl << endl;

	cout << "* Assign values for polynomial P2 *" << endl;
	cout << "Input: ";
	cin >> P2;
	cout << "P2 is: " << P2 << endl << endl;

	cout << "P3 = P1 - P2" <<endl;
	P3 = P1 - P2;
	cout << "Now P3 is: " << P3 << endl << endl;
    P3 = P1 * P2;
	cout << "Now P3 is: " << P3 << endl << endl;
    P3 = -P3;
	cout << "Now P3 is: " << P3 << endl << endl;
    P3 = P3 - 3;
	cout << "Now P3 is: " << P3 << endl << endl;
    cout << P3(3) << endl;
    P3 += P3;
	cout << "Now P3 is: " << P3 << endl << endl;
    P3 -= P3;
	cout << "Now P3 is: " << P3 << endl << endl;

#if 0
	cout << "P3 += 11" << endl;
	P3 += 11;
	cout << "Now P3 is: " << P3 << endl << endl;

	cout << "P3 += P1" << endl;
	P3 += P1;
	cout << "Now P3 is: " << P3 << endl << endl;
	
	int A[100] = {0};
	cout << "Loading values of P3 into Array A" << endl;
	P3.get(A, 100);
	cout << "Content of Array A is now: " << endl;
	for(int i=0; i<99; i++){
	    if(A[i] == 0 && A[i+1] == -1) break;
	    cout << A[i] << " ";
	}
	cout << endl << endl;

	cout << "P3 = P1 * 4" << endl;
	P3 = P1 * 4;
	cout << "Now P3 is: " << P3 << endl << endl;

	cout << "P3 *= P2" << endl;
	P3 *= P2;
	cout << "Now P3 is: " << P3 << endl << endl;

	cout << "P3 = 2 * P1 * P2" << endl;
	P3 = 2 * P1 * P2;
	cout << "Now P3 is: " << P3 << endl << endl;

	cout << "P4 = P2 * 2 * P1" << endl;
	P4 = P2 * 2 * P1;
	cout << "Now P4 is: " << P4 << endl << endl;

	cout << "P3 now equals to P4, is that true?" << endl;
	if (P3 == P4) cout << "TRUE";
	else cout << "FALSE";
	cout << endl << endl;
	
	cout << "P3 is: " << P3 << endl;
	cout << "The first derivative of P3 is:" << P3.derivative() << endl;
	cout << "The second derivative of P3 is:" << P3.derivative().derivative() << endl << endl;
	
	cout << "P4 is: " << P4 << endl;
	cout << "P4 (-6) equals to: " << P4(-6) << endl << endl;

#endif
	cout << "---------- END PROGRAM ----------" << endl << endl;

    return 0;
}
