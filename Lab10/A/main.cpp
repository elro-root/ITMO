#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    std::vector<int> vertex_degree;
    int n, m, vertex1, vertex2;
    std::cin >> n >> m;
    vertex_degree.assign(n, 0);
    for (int i = 0; i < m; ++i) {
        std::cin >> vertex1 >> vertex2;
        vertex1 -= 1;
        vertex2 -= 1;
        vertex_degree[vertex1] += 1;
        vertex_degree[vertex2] += 1;
    }
    for (auto &item:vertex_degree){
        std::cout << item << " ";
    }
    return 0;
}
