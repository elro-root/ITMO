#include <iostream>
#include <vector>
#define long long long

std::vector<std::vector<std::pair<long, long>> > graph;
const long infinity = LONG_LONG_MAX;

std::vector<long> BellmanFord(long start, long n) { // Алгоритм Беллмона Форда
    std::vector<long> dist(n, infinity);
    dist[start] = 0;
    for (long i = 0; i < n; ++i)
        for (long j = 0; j < n; ++j)
            for (long k = 0; k < graph[j].size(); ++k)
                if ((dist[j] < infinity) && (dist[graph[j][k].second] > dist[j] + graph[j][k].first))
                    dist[graph[j][k].second] = dist[j] + graph[j][k].first;
    return  dist;
}

void dfs(long v, std::vector<bool>& used) {
    used[v] = true;
    for (auto & i : graph[v])
        if (!used[i.second])
            dfs(i.second, used);
}

int main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    long n, m, start, vertex1, vertex2, weight;
    std::cin >> n >> m >> start;
    graph.resize(n);
    for (int i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2 >> weight;
        graph[vertex1 - 1].push_back({weight, vertex2 - 1});
    }
    std::vector<long> d = BellmanFord(start - 1, n);
    std::vector<bool> used(n, false);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < graph[i].size(); ++j)
            if ((d[i] < infinity) && (d[graph[i][j].second] > d[i] + graph[i][j].first) && !used[graph[i][j].second])
                dfs(graph[i][j].second, used);
    for (int i = 0; i < n; ++i)
        if (d[i] == infinity)
            std::cout << "*" << "\n";
        else if (used[i] || d[i] < -5e18)
            std::cout << "-" << "\n";
        else
            std::cout << d[i] << "\n";
    return 0;
}