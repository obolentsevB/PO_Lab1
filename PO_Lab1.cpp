#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

int main() {

    const int n = 2000; 
    vector<vector<double>> matrix(n, vector<double>(n));

    // Initialize random number generator
    mt19937 gen(42);
    uniform_real_distribution<> dis(0, 100);

    // Fill matrix with random numbers
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    // Measure sequential execution time
    auto start = high_resolution_clock::now();

    //Place the sum of column elements on the main diagonal
    for (int j = 0; j < n; ++j) {
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += matrix[i][j];
        }
        matrix[j][j] = sum; 
    }

    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;

    cout << "Sequential Time: " << diff.count() << " s" << endl;

    return 0;
}
