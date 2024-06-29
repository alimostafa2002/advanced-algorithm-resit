#include <iostream>
#include <pthread.h>
#include <vector>

#define MAX_SIZE 100

using namespace std;

int matrixA[MAX_SIZE][MAX_SIZE];
int matrixB[MAX_SIZE][MAX_SIZE];
int result[MAX_SIZE][MAX_SIZE];

int rowsA, colsA, rowsB, colsB;

void* multiply(void* arg) {
    int row = *((int*)arg);
    for (int j = 0; j < colsB; ++j) {
        result[row][j] = 0;
        for (int k = 0; k < colsA; ++k) {
            result[row][j] += matrixA[row][k] * matrixB[k][j];
        }
    }
    pthread_exit(0);
}

int main() {
    // Input matrices A and B
    cout << "Enter the number of rows and columns for Matrix A: ";
    cin >> rowsA >> colsA;
    cout << "Enter the elements of Matrix A:\n";
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            cin >> matrixA[i][j];
        }
    }

    cout << "Enter the number of rows and columns for Matrix B: ";
    cin >> rowsB >> colsB;
    cout << "Enter the elements of Matrix B:\n";
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            cin >> matrixB[i][j];
        }
    }

    // Initialize pthread variables
    pthread_t threads[MAX_SIZE];
    int threadArgs[MAX_SIZE];

    // Create threads for parallel multiplication
    for (int i = 0; i < rowsA; ++i) {
        threadArgs[i] = i;
        pthread_create(&threads[i], NULL, multiply, (void*)&threadArgs[i]);
    }

    // Join threads
    for (int i = 0; i < rowsA; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Display the result matrix
    cout << "Resultant Matrix:\n";
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
