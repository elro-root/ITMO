#include <iostream>
#include <vector>
#include <algorithm>
#include "input.hpp"

std::vector<int> lis(std::vector<int> const& a) {
    unsigned long n = a.size();
    const int INF = 1e9;
    std::vector<int> d(n+1, INF);
    d[0] = -INF;
    int pos[n];
    int prev[n - 1];
    pos[0] = -1;
    long ans = 0;
    for (int i = 0; i < n; i++) {
        long j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j-1] < a[i] && a[i] < d[j]){
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            ans = std::max(ans, j);
        }
    }

    std::vector<int> answer;
    int p = pos[ans];
    while (p != -1){
    answer.push_back(a[p]);
    p = prev[p];
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

int main() {
    input();
    int n;
    std::cin >> n;
    std::vector<int> array(n);
    std::vector<int> answer;
    for (long long  i = 0; i < n; ++i)
        std::cin >> array[i];
    answer = lis(array);
    std::cout << answer.size() << std::endl;
    for (auto &i : answer){
        std::cout << i << " ";
    }
    return 0;
}