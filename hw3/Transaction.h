/*
 @author Deniz Aydemir Section 1 22001859 
*/
#ifndef __TRANSACTION_H
#define __TRANSACTION_H

class Transaction {
    public:
        int sub;
        int movie;
        bool returned;

        Transaction(int sub, int movie, bool returned);
        Transaction();

        // overloading operators to be able to compare the transaction objects
        void operator=(const Transaction& other);
        bool operator==(const Transaction& other);
        bool operator<(const Transaction& other);
        bool operator>(const Transaction& other);
};
#endif