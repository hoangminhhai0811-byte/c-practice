#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define WHITE 0 // Chưa thăm
#define GRAY 1  // Đang thăm (nằm trên nhánh đệ quy hiện tại)
#define BLACK 2 // Đã thăm xong

bool dfsCycle(int u, vector<vector<int>>& adjList, vector<int>& color) {
    color[u] = GRAY;
    for (int v : adjList[u]) {
        if (color[v] == GRAY) return true; // Phát hiện cạnh ngược (back edge)
        if (color[v] == WHITE && dfsCycle(v, adjList, color)) return true;
    }
    color[u] = BLACK;
    return false;
}

bool hasCycle(vector<vector<int>>& adjList, int n) {
    vector<int> color(n, WHITE);
    for (int i = 0; i < n; i++) {
        if (color[i] == WHITE) {
            if (dfsCycle(i, adjList, color)) return true;
        }
    }
    return false;
}

void dfsTopo(int u, vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfsTopo(v, adjList, visited, st);
        }
    }
    st.push(u);
}

vector<int> topologicalSort(vector<vector<int>>& adjList, int n) {
    stack<int> st;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsTopo(i, adjList, visited, st);
        }
    }

    vector<int> order;
    while (!st.empty()) {
        order.push_back(st.top());
        st.pop();
    }
    return order;
}

int main() {
    int numCourses = 8;
    vector<vector<int>> adjList(numCourses);

    // Đồ thị chương trình đào tạo 8 môn học không chu trình (DAG)
    adjList[0].push_back(1); // Môn 0 -> Môn 1
    adjList[0].push_back(2);
    adjList[1].push_back(3);
    adjList[2].push_back(3);
    adjList[3].push_back(4);
    adjList[4].push_back(5);
    adjList[5].push_back(6);
    adjList[6].push_back(7);

    // Thêm dòng này để cố ý tạo vòng lặp tiên quyết:
    // adjList[7].push_back(0);

    if (hasCycle(adjList, numCourses)) {
        cout << "LOI: chuong trinh dao tao co vong lap tien quyet!" << endl;
        return 1;
    }

    vector<int> order = topologicalSort(adjList, numCourses);
    cout << "Thu tu hoc hop le: ";
    for (int course : order) cout << course << " ";
    cout << endl;

    return 0;
}
