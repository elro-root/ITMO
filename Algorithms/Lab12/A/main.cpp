#include <iostream>
#include <vector>
//#include "input.hpp"
#define long long long
namespace boom {
    template<class InputIterator>
    bool is_sorted(InputIterator first, InputIterator last) {
        InputIterator tmp = first;
        ++first;
        if (*first > *tmp) {
            for (; first != last; ++first, ++tmp) {
                if (*first >= *tmp)
                    continue;
                else
                    return false;
            }
            return true;
        } else
            return false;
    }
}
int main() {
    //input();
    long n;
    std::cin >> n;
    std::vector<long> array(n);
    std::vector<std::vector<long>> pod_array(n);
    for (int i = 0; i < n; ++i)
        std::cin >> array[i];
    if (boom::is_sorted(array.begin(), array.end())){
        std::cout << array.size() << std::endl;
        for (auto &i : array)
            std::cout << i << " ";
        return 0;
    }
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
    long j = 0;
    for (auto &i: pod_array) {
        if (i.size() > max){
            max = i.size();
            ++j;
        }
    }
    std::cout << max << std::endl;
    for (auto &i : pod_array[j]){
        std::cout << i << " ";
    }
    return 0;
}