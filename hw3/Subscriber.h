/*
 @author Deniz Aydemir Section 1 22001859 
*/
#ifndef __SUB_H
#define __SUB_H
#include "Transaction.h"

class Subscriber {
    public:
        struct TrNode {
            Transaction transaction;
            TrNode* next;
        };
        int id;
        int size;
        TrNode* headPtr;


        Subscriber();
        Subscriber(const int id);
        ~Subscriber();

        bool addTr(Transaction& tr);
        bool removeTr(Transaction& tr);
        TrNode* getTransactionNode(Transaction& tr);
        bool contains(Transaction& tr);
        void clear();

        // overloading operators to be able to compare the subscriber objects
        //void operator=(const Subscriber& other);
        bool operator==(const Subscriber& other);
        bool operator<(const Subscriber& other);
        bool operator>(const Subscriber& other);
};
#endif