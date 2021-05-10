#include <iostream>
#include <vector>

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

std::vector<std::vector<int>> KMP(int n, std::string s) {
    unsigned int size = s.length();
    std::vector<int> pi = prefix_function(s);
    std::vector<std::vector<int>> kmp(size + 1, std::vector<int>(n));
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0 && j + 'a' != s[i]) {
                kmp[i][j] = kmp[pi[i - 1]][j];
            } else {
                kmp[i][j] = i + (j + 'a' == s[i]);
            }
        }
    }
    return kmp;
}

int main() {
    std::string s;
    int n;
    std::cin >> n >> s;
    std::vector<std::vector<int>> kmp = KMP(n, s);
    for (auto & i: kmp) {
        for (int j = 0; j < n; ++j) {
            std::cout << i[j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}