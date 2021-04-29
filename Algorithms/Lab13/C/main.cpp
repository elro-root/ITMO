#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_function (const std::string & s) {
    int n = (int) s.length();
    std::vector<int> pi (n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}


int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    std::string t;
    std::cin >> t;
    std::vector<int> ans = prefix_function(t);
    for (auto &i:ans) {
        std::cout << i << " ";
    }
    return 0;
}
