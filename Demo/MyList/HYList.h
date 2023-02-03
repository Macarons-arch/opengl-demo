
#include "stdio.h"

class HYList {
    
public:
    int value;
    HYList *next;
    
    
    HYList(int _value):value(_value){}
    ~HYList() {}
    
    static HYList* randomNew(int nodeCount, unsigned int range) {
        if (nodeCount <= 0) return nullptr;
        
        HYList* node = new HYList(rand() % range);
        node->next = randomNew(nodeCount - 1, range);
        return node;
    }
    
    void printWithNo(unsigned int no) {
        printf("node%d value is: %d\n", no, value);
        if (next) {
            next->printWithNo(no + 1);
        }
    }
    
    void printList() {
        printWithNo(1);
    }
};
