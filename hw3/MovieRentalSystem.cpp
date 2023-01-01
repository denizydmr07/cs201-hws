/*
 @author Deniz Aydemir Section 1 22001859 
*/
#include "MovieRentalSystem.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool MovieRentalSystem::containsSub(Subscriber& sub) const {
    return getSubNode(sub) != nullptr;
}

MovieRentalSystem::SubNode* MovieRentalSystem::getSubNode(Subscriber& sub) const{
    SubNode* ptr = subHeadPtr;

    if (subSize == 0) {
        return nullptr;
    }

    while (ptr != nullptr) {
        if (ptr->subscriber == sub) {
            return ptr;
        }
        ptr = ptr->nextSub;
    }
    
    return nullptr;
}

void MovieRentalSystem::loadSubscriber(int subId) {
    Subscriber sub(subId);
    if (containsSub(sub)) {
        cout << "Subscriber " << subId << " already exists " << endl; 
    }
    else {
        SubNode* newPtr = new SubNode();
        newPtr->subscriber = sub;

        if (subSize == 0) {
            newPtr->nextSub = nullptr;
            subHeadPtr = newPtr;
        }
        else {
            SubNode* prev = nullptr;
            SubNode* current = subHeadPtr;

            if (sub < current->subscriber) {
                newPtr->nextSub = subHeadPtr;
                subHeadPtr = newPtr;
                subSize++;
                return;
            }

            while (current != nullptr && sub > current->subscriber) {
                prev = current;
                current = current->nextSub;
            }

            newPtr->nextSub = current;
            prev->nextSub = newPtr;
        }
        subSize++;
    }
}

void MovieRentalSystem::clearSubs(const int subId) {
    Subscriber sub(subId);

    //Removing subscriber
    SubNode* current = subHeadPtr;
    SubNode* prev = nullptr;

    //if sub is in the first noed
    if (current->subscriber == sub) {
        subHeadPtr = subHeadPtr->nextSub;

        current->nextSub = nullptr;
        delete current;
        current = nullptr;
        subSize--;
    }
    else {
        while (current != nullptr && !(current->subscriber == sub)) {
            prev = current;
            current = current->nextSub;
        }

        prev->nextSub = current->nextSub;
        current->nextSub = nullptr;
        delete current;
        current = nullptr;
        prev = nullptr;
        subSize--;
    }
}

bool MovieRentalSystem::containsMovie(Movie& movie) const {
    return getMovieNode(movie) != nullptr;
} 

MovieRentalSystem::MovieNode* MovieRentalSystem::getMovieNode(Movie& movie) const {
    MovieNode* ptr = movieHeadPtr;

    if (movieSize == 0) {
        return nullptr;
    }

    while (ptr != nullptr) {
        if (ptr->movie == movie) {
            return ptr;
        }
        ptr = ptr->nextMovie;
    }

    return nullptr;
}

void MovieRentalSystem::loadMovie(int movieId, int numCopies) {
    Movie movie(movieId, numCopies);
    if (containsMovie(movie)) {
        cout << "Movie " << movieId << " already exists " << endl; 
    }
    else {
        MovieNode* newPtr = new MovieNode();
        newPtr->movie = movie;

        if (movieSize == 0) {
            newPtr->nextMovie = nullptr;
            movieHeadPtr = newPtr;
        }
        else {
            MovieNode* prev = nullptr;
            MovieNode* current = movieHeadPtr;

            if (movie < current->movie) {
                newPtr->nextMovie = movieHeadPtr;
                movieHeadPtr = newPtr;
                movieSize++;
                return;
            }

            while (current != nullptr && movie > current->movie) {
                prev = current;
                current = current->nextMovie;
            }

            newPtr->nextMovie = current;
            prev->nextMovie = newPtr;
        }
        movieSize++;
        //cout << "Movie " << movieId << " has been added" << endl;
    }
}

void MovieRentalSystem::clearMovies(const int movieId) {
    Movie movie(movieId, 0); 

    MovieNode* current = movieHeadPtr;
    MovieNode* prev = nullptr;

    //if node to be deleted is in the first index
    if (current->movie == movie) {
        movieHeadPtr = movieHeadPtr->nextMovie;

        current->nextMovie = nullptr;
        delete current;
        current = nullptr;
        movieSize--;
    }
    else {
        while(current != nullptr && !(current->movie == movie)) {
            prev = current;
            current = current->nextMovie;
        }

        prev->nextMovie = current->nextMovie;
        current->nextMovie = nullptr;
        delete current;
        current = nullptr;
        prev = nullptr;
        movieSize--;
    }
}

MovieRentalSystem::MovieRentalSystem( const string movieInfoFileName,const string subscriberInfoFileName ) {
    fstream MyMovieFile(movieInfoFileName, ios_base::in);
    fstream MySubFile(subscriberInfoFileName, ios_base::in);

    if (!MyMovieFile || !MySubFile) {
        if(!MyMovieFile) {
            cout << "Input file " << movieInfoFileName << " does not exist" << endl;
        }
        if(!MySubFile) {
            cout << "Input file " << subscriberInfoFileName << " does not exist" << endl;
        }
    }
    else {
        int movieID, copies, movieCount; 

        MyMovieFile >> movieCount;

        for (int i = 0; i < movieCount; i++) {
            MyMovieFile >> movieID >> copies;
            
            loadMovie(movieID, copies);
        }

        MyMovieFile.close();

        int subId, subCount;

        MySubFile >> subCount;

        for (int i = 0; i < subCount; i++) {
            MySubFile >> subId;
            
            loadSubscriber(subId);
        }

        MySubFile.close();

        cout << subCount << " subscribers and " << movieCount << " movies have been loaded" << endl;
    }
}

MovieRentalSystem::~MovieRentalSystem() {
    while (subSize != 0) {
        clearSubs(subHeadPtr->subscriber.id);
    }
    while (movieSize != 0) {
        clearMovies(movieHeadPtr->movie.id);
    }
}

void MovieRentalSystem::removeMovie(const int movieId) {
    Movie movie(movieId, 0);
    if(!containsMovie(movie)) {
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }

    //Searching for non-returned copy
    SubNode* subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
        while (trPtr != nullptr) {
            if (trPtr->transaction.movie == movieId) {
                if (!trPtr->transaction.returned) {
                    cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << endl;
                    return;
                }
            }

            trPtr = trPtr->next;
        }

        subPtr = subPtr->nextSub;
    }

    subPtr = nullptr;

    // removing the movie
    MovieNode* current = movieHeadPtr;
    MovieNode* prev = nullptr;

    //if node to be deleted is in the first index
    if (current->movie == movie) {
        movieHeadPtr = movieHeadPtr->nextMovie;

        current->nextMovie = nullptr;
        delete current;
        current = nullptr;
        movieSize--;
    }
    else {
        while(current != nullptr && !(current->movie == movie)) {
            prev = current;
            current = current->nextMovie;
        }

        prev->nextMovie = current->nextMovie;
        current->nextMovie = nullptr;
        delete current;
        current = nullptr;
        prev = nullptr;
        movieSize--;
    }

    cout << "Movie " << movieId << " has been removed" << endl;
}

void MovieRentalSystem::addMovie( const int movieId, const int numCopies ) {
    Movie movie(movieId, numCopies);
    if (containsMovie(movie)) {
        cout << "Movie " << movieId << " already exists " << endl; 
    }
    else {
        MovieNode* newPtr = new MovieNode();
        newPtr->movie = movie;

        if (movieSize == 0) {
            newPtr->nextMovie = nullptr;
            movieHeadPtr = newPtr;
        }
        else {
            MovieNode* prev = nullptr;
            MovieNode* current = movieHeadPtr;

            if (movie < current->movie) {
                newPtr->nextMovie = movieHeadPtr;
                movieHeadPtr = newPtr;
                movieSize++;
                return;
            }

            while (current != nullptr && movie > current->movie) {
                prev = current;
                current = current->nextMovie;
            }

            newPtr->nextMovie = current;
            prev->nextMovie = newPtr;
        }
        movieSize++;
        cout << "Movie " << movieId << " has been added" << endl;
    }
}

void MovieRentalSystem::removeSubscriber(const int subId) {
    Subscriber sub(subId);
    if(!containsSub(sub)) {
        cout << "Subscriber " << subId << " does not exist" << endl;
        return;
    }

    //searching for non-returned movie
    SubNode* subPtr = getSubNode(sub);
    Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
    while (trPtr != nullptr) {
        if(!trPtr->transaction.returned) {
            cout << "Subscriber " << subId << " cannot be removed -- at least one movie has not been returned" << endl;
            return;
        }
        trPtr = trPtr->next;
    }

    //Removing subscriber
    SubNode* current = subHeadPtr;
    SubNode* prev = nullptr;

    //if sub is in the first noed
    if (current->subscriber == sub) {
        subHeadPtr = subHeadPtr->nextSub;

        current->nextSub = nullptr;
        delete current;
        current = nullptr;
        subSize--;
    }
    else {
        while (current != nullptr && !(current->subscriber == sub)) {
            prev = current;
            current = current->nextSub;
        }

        prev->nextSub = current->nextSub;
        current->nextSub = nullptr;
        delete current;
        current = nullptr;
        prev = nullptr;
        subSize--;
    }

    cout << "Subscriber " << subId << " has been removed" << endl;
}

void MovieRentalSystem::rentMovie(const int subId, const int movieId) {
    // checking if movie and subscriber exists
    Subscriber copySub(subId);
    const int mockCopyCount = 0;
    Movie copyMovie(movieId, mockCopyCount);
    if (!containsMovie(copyMovie)) {
        if (!containsSub(copySub)) {
            cout << "Subscriber " << subId <<" and movie " << movieId << " do not exist" << endl;
            return;
        }
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }
    if (!containsSub(copySub)) {
        cout << "Subscriber " << subId << " does not exist" << endl;
        return;
    }

    //Searching to learn whether or not there is an available copy for the movie
    int copyCount = 0;
    SubNode* subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
        while (trPtr != nullptr) {
            if (trPtr->transaction.movie == movieId) {
                if(! trPtr->transaction.returned) {
                    copyCount++; // there is a non-returned copy
                }
            }
            trPtr = trPtr->next;
        }
        subPtr = subPtr->nextSub;
    }

    // checking if all copies are rented
    if (copyCount == getMovieNode(copyMovie)->movie.copies) {
        cout << "Movie " << movieId << " has no available copy for renting" << endl;
        return;
    }

    Transaction copyTr(subId, movieId, false);
    getSubNode(copySub)->subscriber.addTr(copyTr);
    cout << "Movie " << movieId << " has been rented by subscriber " << subId << endl;
}

void MovieRentalSystem::returnMovie(const int subId, const int movieId) {
    // checking if movie and subscriber exists
    Subscriber copySub(subId);
    const int mockCopyCount = 0;
    Movie copyMovie(movieId, mockCopyCount);
    if (!containsMovie(copyMovie)) {
        if (!containsSub(copySub)) {
            cout << "Subscriber " << subId <<" and movie " << movieId << " do not exist" << endl;
            return;
        }
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }
    if (!containsSub(copySub)) {
        cout << "Subscriber " << subId << " does not exist" << endl;
        return;
    }

    // Searching for rental tranaction
    Transaction tr(subId,movieId,false);
    SubNode* subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
        while (trPtr != nullptr) {
            if (trPtr->transaction == tr) {
                trPtr->transaction.returned = true;
                cout << "Movie " << movieId << " has been returned by subscriber " << subId << endl;
                return;
            }
            trPtr = trPtr->next;
        }
        subPtr = subPtr->nextSub;
    }

    // ıf there is not any rental transaction
    cout << "No rental transaction for subscriber " << subId << " and movie " << movieId << endl;
}

void MovieRentalSystem::showMoviesRentedBy( const int subscriberId ) const{
    Subscriber copySub(subscriberId);
    if (!containsSub(copySub)) {
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
        return;
    }
    if(getSubNode(copySub)->subscriber.headPtr == nullptr) {
        cout << "Subscriber " << subscriberId << " has not rented any movies" << endl;
        return;
    }
    cout << "Subscriber " << subscriberId << " has rented the following movies:" << endl;
    
    SubNode* subPtr = getSubNode(copySub);
    Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
    while (trPtr != nullptr) {
        cout << trPtr->transaction.movie;
        if (!trPtr->transaction.returned) {
            cout << " not";
        }
        cout << " returned" << endl;
        trPtr = trPtr->next;
    }
}

void MovieRentalSystem::showSubscribersWhoRentedMovie( const int movieId ) const {
    const int mockNoOfCopies = 0;
    Movie movie(movieId, mockNoOfCopies);

    if(!containsMovie(movie)) {
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }

    int count = 0; // counting movie's transaction appereances
    SubNode* subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
        while (trPtr != nullptr) {
            if(trPtr->transaction.movie == movieId) {
                count++;
            }
            trPtr = trPtr->next;
        }
        
        subPtr = subPtr->nextSub;
    }

    if (count == 0) {
        cout << "Movie " << movieId << " has not been rented by any subscriber" << endl;
        return;
    }

    cout << "Movie " << movieId << " has been rented by the following subscribers:" << endl;

    subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        Subscriber::TrNode* trPtr = subPtr->subscriber.headPtr;
        while (trPtr != nullptr) {
            if(trPtr->transaction.movie == movieId) {
                cout << subPtr->subscriber.id;
                if (!trPtr->transaction.returned) {
                    cout << " not";
                }
                cout << " returned" << endl;
            }
            trPtr = trPtr->next;
        }
        
        subPtr = subPtr->nextSub;
    }
}

void MovieRentalSystem::showAllMovies() const {
    cout << "Movies in the movie rental system:" << endl;

    MovieNode* moviePtr = movieHeadPtr;
    while(moviePtr != nullptr) {
        cout << moviePtr->movie.id << " " << moviePtr->movie.copies << endl;
        
        moviePtr = moviePtr->nextMovie;
    }
}

void MovieRentalSystem::showAllSubscribers() const {
    cout << "Subscribers in the movie rental system:" << endl;

    SubNode* subPtr = subHeadPtr;
    while (subPtr != nullptr) {
        cout << subPtr->subscriber.id << endl;
        
        subPtr = subPtr->nextSub;
    }
}