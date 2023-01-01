/*
 @author Deniz Aydemir Section 1 22001859 
*/
#include "Subscriber.h"

Subscriber::Subscriber() {
    id = 0;
    size = 0;
    headPtr = nullptr;
}

Subscriber::Subscriber(const int id) {
    this->id = id;
    size = 0;
    headPtr = nullptr;
}

Subscriber::~Subscriber() {
    clear();
}

bool Subscriber::addTr(Transaction& tr) {
    TrNode* newPtr = new TrNode();
    newPtr->transaction = tr;

    if (size == 0) {
        newPtr->next = nullptr;
        headPtr = newPtr;
    }
    else {
        TrNode* prev = nullptr;
        TrNode* current = headPtr;

        if (tr < current->transaction) {
            newPtr->next = headPtr;
            headPtr = newPtr;
            size++;
            return true;
        }

        while (current != nullptr && (tr > current->transaction || (tr.movie == current->transaction.movie && tr.returned < current->transaction.returned))) {
            prev = current;
            current = current->next;
        }

        newPtr->next = current;
        prev->next = newPtr;
    }
    size++;
    return true;
}

bool Subscriber::removeTr(Transaction& tr) {
    if (size == 0) {
        return false;
    }

    TrNode* current = headPtr;
    TrNode* prev = nullptr;

    if (current->transaction == tr) {
        headPtr = headPtr->next;

        current->next = nullptr;
        delete current;
        current = nullptr;
        size--;
        return true;
    }

    while (current != nullptr && !(current->transaction == tr)) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        prev = nullptr;
        return false;
    }

    prev->next = current->next;
    current->next = nullptr;
    delete current;
    current = nullptr;
    prev = nullptr;
    size--;
    return true;
}

Subscriber::TrNode* Subscriber::getTransactionNode(Transaction& tr) {
    TrNode* ptr = headPtr;

    while (ptr != nullptr) {
        if (ptr->transaction == tr) {
            return ptr;
        }
        ptr = ptr->next;
    }

    return nullptr;
}

bool Subscriber::contains(Transaction& tr) {
    return getTransactionNode(tr) != nullptr;
}

void Subscriber::clear() {
    while (!(size==0)) {
        removeTr(headPtr->transaction);
    }
}

bool Subscriber::operator==(const Subscriber& sub) {
    return this->id == sub.id;
}
bool Subscriber::operator<(const Subscriber& sub) {
    return this->id < sub.id;
}
bool Subscriber::operator>(const Subscriber& sub) {
    return this->id > sub.id;
}