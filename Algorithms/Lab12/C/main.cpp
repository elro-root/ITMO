#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "input.hpp"

std::vector<int> lcs(const std::string &x, const std::string &y) {
    std::vector<int> curr(y.size() + 1, 0);
    for (auto &i : x) {
        std::vector<int> prev = curr;
        for (int j = 0; j < y.size(); ++j) {
            if (i == y[j])
                curr[j + 1] = prev[j] + 1;
            else
                curr[j + 1] = std::max(curr[j], prev[j + 1]);
        }
    }
    return curr;
}
std::string h_berg(std::string x, std::string y){
    std::string ans;
    int x_len = (int) x.size();
    int y_len = (int) y.size();
    if (x_len == 0) {
        return std::string();
    }
    if (x_len == 1) {
        for (auto &i : y) {
            if (i == x[0]){
                ans.push_back(x[0]);
                return ans;
            } else {
                return std::string();
            }
        }
    }
    int i = x_len / 2;
    std::string xb, xe, yb, ye;
    for (int j = 0; j < i; ++j)
        xb.push_back(x[j]);
    for (int j = i; j < x_len; ++j)
        xe.push_back(x[j]);
    std::vector<int> L1 = lcs(xb, y);
    std::reverse(xe.begin(), xe.end()); std::reverse(y.begin(), y.end());
    std::vector<int> L2 = lcs(xe, y);
    std::reverse(xe.begin(), xe.end()); std::reverse(y.begin(), y.end());
    int max = L2[0];
    int it_max = -1;
    for (int j = 0; j < y_len; ++j) {
        if (L1[j] + L2[y_len - (j + 1)] > max){
            max = L1[j] + L2[y_len - (j + 1)];
            it_max = j;
        }
    }
    if (L1[y_len - 1] > max)
        it_max = (int) y_len - 1;
    for (int j = 0; j < it_max; ++j)
        yb.push_back(y[j]);
    for (int j = it_max; j < y_len; ++j)
        ye.push_back(y[j]);
    auto tmp = h_berg(xb, yb);
    for (auto &item : tmp)
        ans.push_back(item);
    tmp = h_berg(xe, ye);
    for (auto &item : tmp)
        ans.push_back(item);
    return ans;
}
int main(){
    input();
    std::string x, y;
    std::cin >> x >> y;
    std::cout << h_berg(x, y) << std::endl;
    return 0;
}