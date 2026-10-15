#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<int> bfs(vector<vector<pair<int, int>>>& adjList, int source, int n) {
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    dist[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adjList[u]) {
            int v = edge.first;
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1; // Chỉ đếm số cạnh, bỏ qua trọng số w
                q.push(v);
            }
        }
    }
    return dist;
}

vector<int> dijkstra(vector<vector<pair<int, int>>>& adjList, int source, int n) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n = 5; // 0=A, 1=B, 2=C, 3=D, 4=E
    vector<vector<pair<int, int>>> adjList(n);

    auto addEdge = [&](int u, int v, int w) {
        adjList[u].push_back({v, w});
        // Bài giảng định hướng đồ thị có hướng (mũi tên trong đề), hoặc vô hướng đều cho kết quả tương tự
    };

    addEdge(0, 1, 5); addEdge(1, 3, 5); // Đường 1: A-B-D (w=10, 2 cạnh)
    addEdge(0, 2, 1); addEdge(2, 4, 1); addEdge(4, 3, 1); // Đường 2: A-C-E-D (w=3, 3 cạnh)

    vector<int> distBFS = bfs(adjList, 0, n);
    vector<int> distDijkstra = dijkstra(adjList, 0, n);

    cout << "Khoang cach tu A(0) den D(3) theo BFS (dem so canh): " << distBFS[3] << endl;
    cout << "Khoang cach tu A(0) den D(3) theo Dijkstra (trong so): " << distDijkstra[3] << endl;

    return 0;
}
