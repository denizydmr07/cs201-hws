/*
 @author Deniz Aydemir Section 1 22001859 
*/
#ifndef __MOVIE_RENTAL_SYSTEM_H
#define __MOVIE_RENTAL_SYSTEM_H
#include <string>
#include "Subscriber.h"
#include "Movie.h"
#include "Transaction.h"
using namespace std;

class MovieRentalSystem {
    public:
        MovieRentalSystem( const string movieInfoFileName,
        const string subscriberInfoFileName );
        ~MovieRentalSystem();
        void removeMovie( const int movieId );
        void addMovie( const int movieId, const int numCopies );
        void removeSubscriber( const int subscriberId );
        void rentMovie( const int subscriberId, const int movieId );
        void returnMovie( const int subscriberId, const int movieId );
        void showMoviesRentedBy( const int subscriberId ) const;
        void showSubscribersWhoRentedMovie( const int movieId ) const;
        void showAllMovies() const;
        void showAllSubscribers() const;


    private:
        // Subscriber Sorted LinkedList
        struct SubNode {
            Subscriber subscriber;
            SubNode* nextSub;
        };   
        // Movie Sorted LinkedList
        struct MovieNode {
            Movie movie;
            MovieNode* nextMovie;
        };
        //Subscriber headPtr
        SubNode* subHeadPtr;
        int subSize = 0;
        //Movie headPtr
        MovieNode* movieHeadPtr;
        int movieSize = 0;


        //Functions for Subscriber List
        SubNode* getSubNode(Subscriber& sub) const;
        bool containsSub(Subscriber& sub) const;
        void loadSubscriber(int subId); // add subscriber for loading from text since there is no addSubscriber method
        void clearSubs(const int subId); //clear method for destructor. I created since destructor does not print any messages while removing objects

        //Functions for Movie List
        MovieNode* getMovieNode(Movie& movie) const;
        bool containsMovie(Movie& movie) const; 
        void loadMovie(int movieId, int numCopies); //add movie for loading from text since while loading there is no message to be printed
        void clearMovies(const int movieId); // clear method for destructor.  I created since destructor does not print any messages while removing objects
};
#endif