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
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    long n, m, vertex1, vertex2, weight;

    std::cin >> n >> m;
    std::vector<unsigned long> temp = std::vector<unsigned long>(n);
    temp.assign(n, infinity);
    graph.resize(n, temp);
    flag.resize(n, false);
    distance.resize(n, infinity);
    for (long i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2 >> weight;
        graph[vertex1 - 1][vertex2 - 1] = weight;
    }
    for (int i = 0; i < n; ++i) {
        Dijkstra(n, i);
        for (unsigned long j: distance)
            j == infinity ? std::cout << 0 << " " : std::cout << j << " ";
        std::cout << std::endl;
        flag.assign(n, false);
        distance.assign(n, infinity);
    }
    return 0;
}