#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

int main() {
    mt19937 rng(42);
    vector<int> sizes = {1000, 5000, 10000};

    cout << "V\tE\tMem Matrix(MB)\tMem List(MB)\tTime Matrix(ms)\tTime List(ms)\n";
    cout << "--------------------------------------------------------------------------------\n";

    for (int V : sizes) {
        int E = V * 5;
        vector<pair<int, int>> edges(E);
        uniform_int_distribution<int> dist(0, V - 1);

        for (auto& e : edges) {
            e = {dist(rng), dist(rng)};
        }

        // 1. Xây dựng ma trận kề
        vector<vector<int>> matrix(V, vector<int>(V, 0));
        for (auto& e : edges) {
            matrix[e.first][e.second] = 1;
        }

        // 2. Xây dựng danh sách kề
        vector<vector<int>> adjList(V);
        for (auto& e : edges) {
            adjList[e.first].push_back(e.second);
        }

        // 3. Tính toán bộ nhớ lý thuyết
        double mem_matrix = (1.0 * V * V * sizeof(int)) / (1024 * 1024);
        int total_list_elements = 0;
        for (int i = 0; i < V; ++i) {
            total_list_elements += adjList[i].size();
        }
        double mem_list = (1.0 * total_list_elements * sizeof(int)) / (1024 * 1024);

        // 4. Đo thời gian duyệt
        volatile int dummy = 0; // Tránh tối ưu hoá của trình biên dịch

        // - Ma trận kề
        auto start_matrix = high_resolution_clock::now();
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (matrix[i][j] != 0) {
                    dummy += matrix[i][j];
                }
            }
        }
        auto end_matrix = high_resolution_clock::now();
        double time_matrix = duration<double, std::milli>(end_matrix - start_matrix).count();

        // - Danh sách kề
        auto start_list = high_resolution_clock::now();
        for (int i = 0; i < V; ++i) {
            for (int neighbor : adjList[i]) {
                dummy += neighbor;
            }
        }
        auto end_list = high_resolution_clock::now();
        double time_list = duration<double, std::milli>(end_list - start_list).count();

        cout << V << "\t" << E << "\t" << mem_matrix << "\t\t" << mem_list << "\t\t"
             << time_matrix << "\t\t" << time_list << "\n";
    }
    return 0;
}
