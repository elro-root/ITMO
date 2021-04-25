#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::pair<std::vector<int>, int>> g;
std::vector<std::vector<int>> d;

void dfs(int v) {
    d[v][0] = 0;
    d[v][1] = g[v].second;
    for (int i: g[v].first)
        dfs(i);
    for (int i: g[v].first) {
        d[v][0] += std::max(d[i][0], d[i][1]);
        d[v][1] += d[i][0];
    }
}

int main() {
    freopen("selectw.in", "r", stdin);
    freopen("selectw.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    int n, v1, v2, root = 0;
    std::cin >> n;
    g.resize(n);
    d.resize(n, std::vector<int>(2));
    for (int i = 0; i < n; i++) {
        std::cin >> v1 >> v2;
        if (v1) {
            g[v1-1].first.push_back(i);
            g[i].second = v2;
        } else {
            root = i;
            g[i].second = v2;
        }
    }
    dfs(root);
    std::cout << std::max(d[root][0], d[root][1]);
}