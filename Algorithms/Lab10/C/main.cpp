#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> parents;

int get_grandparent(int vertex){
    if (parents[vertex] == vertex)
        return vertex;
    else{
        int grandparent;
        grandparent = get_grandparent(parents[vertex]);
        parents[vertex] = grandparent;
        return grandparent;
    }
}
struct Edge {
    int vertex1, vertex2;
    int WeightOfVertex;
    bool operator < (Edge edge) const {
        return this->WeightOfVertex < edge.WeightOfVertex;
    }
    bool operator > (Edge edge) const {
        return this->WeightOfVertex > edge.WeightOfVertex;
    }
};
std::vector<Edge> graph;

int main() {
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    int n, m, vertex1, vertex2, weight;

    std::cin >> n >> m;
    graph.resize(m);
    parents.resize(n);
    for (int i = 0; i < m; i++)
    {
        std::cin >> vertex1 >> vertex2 >> weight;
        vertex2 -= 1;
        vertex1 -= 1;
        graph[i].WeightOfVertex = weight;
        graph[i].vertex1 = vertex1;
        graph[i].vertex2 = vertex2;
    }
    for (int i = 0; i < n; ++i) {
        parents[i] = i;
    }
    std::sort(graph.begin(), graph.end());
    long long min = 0;
    for (int i = 0; i < m; i++) {
        vertex1 = graph[i].vertex1, vertex2 = graph[i].vertex2, weight = graph[i].WeightOfVertex;
        if (get_grandparent(vertex1) != get_grandparent(vertex2)) {
            min += weight;
            vertex1 = get_grandparent(vertex1);
            vertex2 = get_grandparent(vertex2);
            if (rand() & 1)
                std::swap (vertex1, vertex2);
            if (vertex1 != vertex2)
                parents[vertex1] = vertex2;
        }
    }
    std::cout << min << std::endl;
    return 0;
}