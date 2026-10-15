#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> suggestFriends(vector<vector<int>>& adjList, int person, int n) {
    vector<int> dist(n, -1);
    vector<int> mutualCount(n, 0);
    queue<int> q;

    dist[person] = 0;
    q.push(person);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adjList[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
            // Nếu v cách person đúng 2 bước VÀ u là bạn trực tiếp của person
            if (dist[v] == 2 && dist[u] == 1) {
                mutualCount[v]++;
            }
        }
    }

    vector<pair<int, int>> result;
    for (int i = 0; i < n; i++) {
        if (dist[i] == 2) {
            result.push_back({i, mutualCount[i]});
        }
    }

    sort(result.begin(), result.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    return result;
}

int main() {
    int n = 10;
    vector<vector<int>> adjList(n);
    auto addFriend = [&](int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };

    // Tái sử dụng đồ thị từ Bài 2
    addFriend(0, 1); addFriend(0, 2); addFriend(1, 3);
    addFriend(2, 4); addFriend(3, 5); addFriend(4, 5);
    addFriend(5, 6); addFriend(6, 7); addFriend(7, 8);
    addFriend(8, 9); addFriend(3, 9);

    for (int person = 0; person < 10; person++) {
        cout << "Goi y ket ban cho nguoi " << person << ":\n";
        auto suggestions = suggestFriends(adjList, person, n);

        if (suggestions.empty()) {
            cout << "  (Khong co goi y)\n";
        } else {
            for (auto& candidate : suggestions) {
                cout << "  Nguoi " << candidate.first << " (" << candidate.second << " ban chung)\n";
            }
        }
        cout << "-----------------------\n";
    }

    return 0;
}
