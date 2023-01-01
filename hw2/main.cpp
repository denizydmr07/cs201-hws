// Deniz Aydemir
// 22001859
// Section 1

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "findMedian.h"
using namespace std;

// I used functions as a parameter for another function to avoid code repetation
void calculateExecTimes(int arr[], const int size,int (*func)(int input[], const int n));

int main() {
    // doubling size until reaching 2^19, starting with size = 1
    for (int size = 1000; size <= 500'000; size += 1'000) {
        
        // I created 3 equal arrays to pass same array to each function
        int arr1[size];
        int arr2[size];
        int arr3[size];

        // Initializing arrays with random values between 0 and 100'000
        for (int i = 0; i < size; i++) {
            int random = rand() % 100'000;
            
            arr1[i] = random;
            arr2[i] = random;
            arr3[i] = random;
        }

        cout << "Size = " << size << endl;
        
        cout << "Algorithm 1:";
        calculateExecTimes(arr1, size, &FIND_MEDIAN_1);

        cout << "Algorithm 2:";
        calculateExecTimes(arr2, size, &FIND_MEDIAN_2);

        cout << "Algorithm 3:";
        calculateExecTimes(arr3, size, &FIND_MEDIAN_3);

        cout << endl;

        if (size >= 10'000) {
            size += 39'000;
        }

    }
    
    return 0;
}

void calculateExecTimes(int arr[], const int size,int (*func)(int input[], const int n)) {
    // In order to get different rand() values each run
    // I made seed value dependent on the time 
    srand((unsigned) time(NULL));
    
    double duration;
    clock_t startTime = clock();

    func(arr, size);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "\tExecution took " << duration << " miliseconds." << endl;
}
