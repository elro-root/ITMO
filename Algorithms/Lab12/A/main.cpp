#include <iostream>
#include <vector>
#include <algorithm>
#include "input.hpp"
#define long long long
int main() {
    input();
    long n;
    std::cin >> n;
    std::vector<long> array(n);
    std::vector<std::vector<long>> pod_array(n);
    for (int i = 0; i < n; ++i)
        std::cin >> array[i];
    int g = 0;
    for (int i = 0; i <= n - 1; ++i) {
        if (array[i] < array[i + 1]) {
            pod_array[g].push_back(array[i]);
        }
        else {
            pod_array[g].push_back(array[i]);
            ++g;
        }
    }

    long max = pod_array[0].size();
    for (auto &i: pod_array) {
        if (i.size() > max){
            max = i.size();
        }
    }
    std::cout << max << std::endl;
    std::reverse(pod_array.begin(), pod_array.end());
    for (auto &i : pod_array){
        if(i.size() == max) {
            for (auto &j: i) {
                std::cout << j << " ";
            }
            return 0;
        }
    }
    return 0;
}