/*
 @author Deniz Aydemir Section 1 22001859 
*/
#include "Transaction.h"

Transaction::Transaction(int sub, int movie, bool returned) {
    this->sub = sub;
    this->movie  = movie;
    this->returned = returned;
}
Transaction::Transaction() {
    sub = 0;
    movie = 0;
    returned = 0;
}

void Transaction::operator=(const Transaction& other) {
    this->movie = other.movie;
    this->sub = other.sub;
    this->returned = other.returned;
}
bool Transaction::operator==(const Transaction& other) {
    return this->movie == other.movie && this->returned == other.returned && this->sub == other.sub;
}

bool Transaction::operator<(const Transaction& other) {
    return this->movie < other.movie;
}

bool Transaction::operator>(const Transaction& other) {
    return this->movie > other.movie;
}