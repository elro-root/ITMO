#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
double distance(std::pair<int, int> vertex1, std::pair<int, int> vertex2) {
    return pow(vertex2.first - vertex1.first, 2) + pow(vertex2.second - vertex1.second, 2);
}
int main() {
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    int n;
    std::vector<std::vector<int> > graph;
    std::vector<bool> used;
    std::vector<std::pair<int, int>> vertex;
    std::vector<double> dist;

    std::cin >> n;
    graph.assign(n, std::vector<int>(n));
    used.resize(n);
    vertex.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vertex[i].first >> vertex[i].second;
        dist[i] = std::numeric_limits<int>::max();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = distance(vertex[i], vertex[j]);
        }
    }
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        int minID = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (minID == -1 || dist[j] < dist[minID]))
                minID = j;
        used[minID] = true;
        for (int j = 0; j < n; j++)
            if (!used[j] && graph[minID][j] < dist[j] && minID != j)
                dist[j] = graph[minID][j];
    }
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += sqrt(dist[i]);
    std::cout << std::setprecision(10) << ans;
    return 0;
}