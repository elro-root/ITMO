#include <iostream>
#include <vector>

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    int n, s;
    std::cin >> n >> s;
    std::vector<std::vector<int>> a(s + 1, std::vector<int>(n + 1, 0));
    std::vector<int> w(s + 1);

    for (int i = 1; i <= s; ++i)
        std::cin >> w[i];

    for (int i = 0; i < n + 1; ++i)
        a[0][i] = 0;

    for (int i = 1; i <= s; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (j >= w[i])
                a[i][j] = std::max(a[i - 1][j], a[i - 1][j - w[i]] + w[i]);
            else
                a[i][j] = a[i - 1][j];
        }
    }
    std::cout << a[s][n] << "\n";
    return 0;
}