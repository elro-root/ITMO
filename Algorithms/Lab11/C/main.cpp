#include <iostream>
#include <vector>
#include <set>
#define long long long

static const long infinity = 1000000000000000; // бесконечность
static std::vector<std::vector<std::pair<long, long>>> graph; // граф
static std::vector<unsigned long> distance; // вектор, котрый хранит дистанцию от стартовой точки до других

void Dijkstra(const long & n, const long & from) {
    distance[from] = 0;
    std::set<std::pair<long, long>> queue; // используем set для хранения аершин по отсортированному расстоянию между вершинами
    queue.insert ({0, 0});
    while (!queue.empty()) {
        std::pair<long, long> v = *queue.begin(); // извлечение вершины
        queue.erase(queue.begin());
        for (auto& i : graph[v.second]) {
            if (distance[v.second] + i.first < distance[i.second]) {
                queue.erase({distance[i.second], i.second});
                distance[i.second] = distance[v.second] + i.first;
                queue.emplace(std::pair<long, long>{distance[i.second], i.second});
            }
        }
    }
}
int main() {
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    long n, m, vertex1, vertex2, weight;

    std::cin >> n >> m;
    graph.resize(n);
    distance.resize(n, infinity);
    for (long i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2 >> weight;
        graph[vertex1 - 1].push_back({weight, vertex2 - 1});
        graph[vertex2 - 1].push_back({weight, vertex1 - 1});
    }
    Dijkstra(n, 0);
    for (auto & i: distance) {
        std::cout << i << " ";
    }
    return 0;
}