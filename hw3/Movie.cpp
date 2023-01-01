/*
 @author Deniz Aydemir Section 1 22001859 
*/
#include "Movie.h"

Movie::Movie() {
    id = 0;
    copies = 0;
}

Movie::Movie(int id, int copies) {
    this->id=id;
    this->copies=copies;
}

void Movie::operator=(const Movie& movie) {
    this->id = movie.id;
    this->copies = movie.copies;
}

bool Movie::operator==(const Movie& movie) {
    return this->id == movie.id;
}

bool Movie::operator<(const Movie& movie) {
    return this->id < movie.id;
}
bool Movie::operator>(const Movie& movie) {
    return this->id > movie.id;
}
