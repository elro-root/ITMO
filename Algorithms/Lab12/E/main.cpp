#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<std::vector<int>> d;

void dfs(int v) {
    d[v][0] = 0;
    d[v][1] = 1;
    for (int i: g[v])
        dfs(i);
    for (int i: g[v]) {
        d[v][0] += std::max(d[i][0], d[i][1]);
        d[v][1] += d[i][0];
    }
}

int main() {
    //    freopen("in.txt", "r", stdin);
    //    freopen("out.txt", "w", stdout);
    //    std::ios_base::sync_with_stdio(false);
    //    cin.tie();
    //    cout.tie();
    int n, v, root = 0;
    std::cin >> n;
    g.resize(n);
    d.resize(n, std::vector<int>(2));
    for (int i = 0; i < n; i++) {
        std::cin >> v;
        if (v)
            g[v-1].push_back(i);
        else
            root = i;

    }
    dfs(root);
    std::cout << std::max(d[root][0], d[root][1]);
}