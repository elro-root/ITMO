#include <iostream>
#include <vector>
#define long long long

static const long infinity = 1000000000000000; // бесконечность
static std::vector<std::vector<unsigned long>> graph; // граф
static std::vector<bool> flag; // вектор меток
static std::vector<unsigned long> distance; // вектор, котрый хранит дистанцию от стартовой точки до других

void Dijkstra(const long & n, const long & from) {
    distance[from] = 0;
    for (long i = 0; i < n; ++i) {
        long v = -1;
        for (long j = 0; j < n; ++j) {
            if (!flag[j] && (distance[j] < distance[v] || v == -1))
                v = j;
        }
        if (distance[v] == infinity)
            break;
        flag[v] = true;
        for (long j = 0; j < n; ++j) {
            if (distance[v] + graph[v][j] < distance[j])
                distance[j] = distance[v] + graph[v][j];
        }
    }
}
int main() {
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    long n, from, to, weight;

    std::cin >> n >> from >> to;
    graph.resize(n, std::vector<unsigned long > (n));
    flag.resize(n, false);
    distance.resize(n, infinity);
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            std::cin >> weight;
            weight >= 0 ? graph[i][j] = weight : graph[i][j] = infinity;
        }
    }
    Dijkstra(n, from - 1);
    distance[to - 1] != infinity ? std::cout << distance[to - 1] : std::cout << "-1";
    return 0;
}
