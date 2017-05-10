#ifndef _INCLUDE_CIRCULAR_LIST
#define _INCLUDE_CIRCULAR_LIST
#include "Node.h"
class CircularList {
    private:
        Node *data;
        Node *read_ptr;
    public:
        CircularList();
        CircularList(const Node &nod);
        void insert(int coef, int power);
        const Node read(void) const;
        void nextReadPtr(void);
        void resetReadPtr(void);
        const bool isEmpty(void) const;
        const bool readEnd(void) const;
        void toArray(int *a, int n) const;
        void clear(); 
        ~CircularList();
};
#endif
