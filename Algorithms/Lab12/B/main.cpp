#include <iostream>
#include <vector>
#include <algorithm>
#include "input.hpp"

std::vector<long long > findLIS(std::vector<long long > a, unsigned long n) {
    long long  d[n - 1];
    long long  prev[n - 1];

    for (long long  i = 0; i < n; ++i) {
        d[i] = 1;
        prev[i] = -1;
        for (long long  j = 0; j < i; ++j)
            if ( a[j] < a[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
    }
    long long  pos = 0;
    long long  l = d[0];
    for(long long  i = 0; i < n; ++i){
        if (d[i] > l) {
            pos = i;
            l = d[i];
        }
    }
    std::vector<long long > answer;
    while(pos != -1) {
        answer.push_back(a[pos]);
        pos = prev[pos];
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}

int main() {
    input();
    long long n;
    std::cin >> n;
    std::vector<long long> array(n);
    std::vector<long long> answer;
    for (long long  i = 0; i < n; ++i)
        std::cin >> array[i];
    answer = findLIS(array, n);
    std::cout << answer.size() << std::endl;
    for (auto &i : answer){
        std::cout << i << " ";
    }
    return 0;
}