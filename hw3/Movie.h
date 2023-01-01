/*
 @author Deniz Aydemir Section 1 22001859 
*/
#ifndef __MOVIE_H
#define __MOVIE_H

class Movie {
    public:
        int id;
        int copies;
        
        Movie();
        Movie(int id, int copies);

        // overloading operators to be able to compare the movie objects
        void operator=(const Movie& movie);
        bool operator==(const Movie& movie);
        bool operator<(const Movie& movie);
        bool operator>(const Movie& movie);
};
#endif