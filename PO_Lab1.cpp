#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

using namespace std;
using namespace std::chrono;

void compute_columns(int start_col, int end_col, int n, vector<vector<double>>& matrix) {
    for (int j = start_col; j < end_col; ++j) {
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += matrix[i][j];
        }
        matrix[j][j] = sum; 
    }
}

int main() {
    int n, num_threads;
    cout << "Enter matrix size (n): ";
    cin >> n;

    cout << "Enter number of threads for parallel execution: ";
    cin >> num_threads;

    vector<vector<double>> matrix(n, vector<double>(n));
    mt19937 gen(42);
    uniform_real_distribution<> dis(0, 100);


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    auto s_start = high_resolution_clock::now();
    
    for (int j = 0; j < n; ++j) {
        double sum = 0;
        for (int i = 0; i < n; ++i) { 
            sum += matrix[i][j]; 
        }
        matrix[j][j] = sum;
    }
    
    auto s_end = high_resolution_clock::now();
    duration<double> s_diff = s_end - s_start;
    cout << "Sequential Time: " << s_diff.count() << " s" << endl;

    vector<thread> threads;
    int cols_per_thread = n / num_threads;

    auto p_start = high_resolution_clock::now();
    
    for (int t = 0; t < num_threads; ++t) {
        int start_col = t * cols_per_thread;
        int end_col = (t == num_threads - 1) ? n : (t + 1) * cols_per_thread;
        threads.emplace_back(compute_columns, start_col, end_col, n, ref(matrix));
    }

    for (auto& th : threads) {
        th.join();
    }
    
    auto p_end = high_resolution_clock::now();
    duration<double> p_diff = p_end - p_start;

    cout << "Parallel Time (" << num_threads << " threads): " << p_diff.count() << " s" << endl;
    cout << "Speedup: " << s_diff.count() / p_diff.count() << "x" << endl;

    return 0;
}
