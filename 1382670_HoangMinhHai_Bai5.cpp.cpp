#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge { int u, v, weight; };

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // Nén đường dẫn
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
            return true;
        }
        return false;
    }
};

int kruskalMST(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    int mstWeight = 0;
    int edgesUsed = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.weight;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }
    return mstWeight;
}

int primMST(vector<vector<pair<int, int>>>& adjList, int n) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int mstWeight = 0;
    pq.push({0, 0}); // {trọng số, đỉnh}

    while (!pq.empty()) {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += weight;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    return mstWeight;
}

int main() {
    int n = 6;
    vector<Edge> edgeList = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4},
        {3, 4, 2}, {4, 5, 6}, {2, 4, 5}, {3, 5, 7}
    };

    vector<vector<pair<int, int>>> adjList(n);
    for (auto& e : edgeList) {
        adjList[e.u].push_back({e.v, e.weight});
        adjList[e.v].push_back({e.u, e.weight});
    }

    cout << "Tong trong so MST (Kruskal): " << kruskalMST(edgeList, n) << endl;
    cout << "Tong trong so MST (Prim): " << primMST(adjList, n) << endl;

    return 0;
}
