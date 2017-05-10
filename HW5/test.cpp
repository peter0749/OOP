// Main Program Example for HW5

// You can use this file as your main program, or add more functions if you want.
// Please ***MAKE SURE*** that your class works fine in this main program.
// TA will test your class by this program with additional test data.


#include <iostream>
// ****If you need to include more header files, add it here****

class Node {
    private:
        int coef, power;
        Node *next;
    public:
        Node() : coef(0), power(-1), next(NULL) {
            this->next = this;
        }
        Node *getNext(void) const {
            return next;
        }
        int getCoef(void) const {
            return coef;
        }
        int getPower(void) const {
            return power;
        }
        void setNext(Node *next) {
            this->next = next;
        }
        void setCoef(int coef) {
            this->coef = coef;
        }
        void setPower(int power) {
            this->power = power;
        }
};

class CircularList {
    private:
        Node *data;
        Node *data_ptr;
        Node *read_ptr;
    public:
        CircularList() {
            data = new Node();
            data_ptr = data;
            read_ptr = data->getNext();
        }
        CircularList(const Node &nod) {
            data = new Node(nod);
            data->setNext(data); // loop back
            data_ptr = data;
            read_ptr = data->getNext();
        }
        void attach(CircularList &list) const {
            Node *temp=data->getNext();
            while(!( temp->getCoef()==0 && temp->getPower()==-1 )) {
                list.insert( temp->getCoef(), temp->getPower() );
                temp = temp->getNext();
            }
        }
        void insert(int coef, int power) {
            Node *temp = new Node;
            temp->setCoef(coef);
            temp->setPower(power);
            temp->setNext(data);
            data_ptr->setNext(temp);
            data_ptr = temp;
        }
        void erase_last(void) {
            if(data_ptr!=data) {
                Node *temp = data_ptr;
                data_ptr = data_ptr->getNext();
                delete temp;
            }
        }
        const Node read(void) const {
            Node result( *read_ptr );
            result.setNext(&result);
            return result;
        }
        void nextReadPtr(void) {
            read_ptr = read_ptr->getNext();
        }
        void resetReadPtr(void) {
            read_ptr = data->getNext();
        }
        bool isEmpty(void) const {
            return data==data_ptr;
        }
        bool readEnd(void) const {
            return read_ptr->getCoef()==0 && read_ptr->getPower()==-1;
        }
        void toArray(int *a, int n) const {
            int top=0;
            Node *temp = data->getNext();
            while( !( temp->getCoef()==0 && temp->getPower()==-1 ) && top+2<n ) {
                a[top++] = temp->getCoef();
                a[top++] = temp->getPower();
                temp = temp->getNext();
            }
            a[top++] = 0;
            a[top++] = -1;
        }
        void erase_all(void) {
            while(!isEmpty()) {
                erase_last();
            }
            data_ptr = data;
            read_ptr = data->getNext();
        }

        ~CircularList() {
            erase_all();
            delete data;
        }
};

class Polynomial {
    private:
        CircularList queue;
        int number;
    public:
        Polynomial() :number(0) {}
        Polynomial(Polynomial &cpy) :number(cpy.getSize()) {
            int n=number*2+2;
            int *a = new int[n];
            cpy.get(a, n);
            set(a, n);
            delete[] a;
        }
        Polynomial(int *arr, const int n) : number(0) {
            set(arr, n);
        }
        void insert(int coef, int power) {
            queue.insert(coef, power);
            ++number;
        }
        int getSize(void) const {
            return number;
        }
        void get(int *a, int n) const {
            queue.toArray(a,n);
        }
        void set(int *a, int n) {
            if (n<4) return;
            number = 0;
            queue.erase_all();
            for (int i=0; i+1<n; i+=2) {
                if (a[i]==0 && a[i+1]==-1) break;
                queue.insert(a[i], a[i+1]);
                ++number;
            }
        }
        const Polynomial derivative(void) {
            int n = this->number*2+2;
            int *a = new int[n];
            queue.toArray(a,n);
            for (int i=0; i+1<n; i+=2) {
                if (a[i]==0 && a[i+1]==-1) break;
                a[i] *= a[i+1];
                --a[i+1];
            }
            Polynomial result(a, n-2);
            return result;
        }
};

std::ostream &operator << (std::ostream &os, const Polynomial &P) {
    int n = P.getSize()*2+2;
    int *arr = new int[n];
    P.get(arr, n);
    if (P.getSize()>0) os << arr[0] << "^" << arr[1];
    for (int i=2; i+1<P.getSize()*2; i+=2) {
        os << (arr[i]>0?" +":" ") << arr[i];
        if (arr[i+1]!=0) {
            os << "^" << arr[i+1];
        }
    }
    return os;
}

std::istream &operator >> (std::istream &is, Polynomial &P) {
    int coef, power;
    while(is>>coef>>power && !(coef==0 && power==-1)) {
        P.insert(coef, power);
    }
    return is;
}

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
    return 0;
}
