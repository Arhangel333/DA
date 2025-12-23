#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

std::vector<int> topo_sort(const int n, std::vector<std::pair<int, int>> &limits) {
    std::vector<std::vector<int>> graph(n + 1);
    std::vector links(n + 1, 0);

    for (const auto &[a, b] : limits) {
        graph[a].push_back(b);
        links[b]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (links[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> res;
    while (!q.empty()) {
        int nd = q.front();
        q.pop();
        res.push_back(nd);

        for (int neighbor : graph[nd]) {
            links[neighbor]--;
            if (links[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (res.size() != n) {
        return {-1};
    }

    return res;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> limits(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> limits[i].first >> limits[i].second;
    }

    std::vector<int> sorted_order = topo_sort(n, limits);
    if (sorted_order.size() == 1 && sorted_order[0] == -1) {
        std::cout << -1 << "\n";
    } else {
        for (const int num : sorted_order) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}