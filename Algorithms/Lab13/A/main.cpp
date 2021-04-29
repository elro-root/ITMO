#include <iostream>
#include <string>
#include <vector>

std::vector<int> brute_force(std::string & t, std::string & p) {
    std::vector<int> ans;
    unsigned long tsize = t.length();
    unsigned long psize = p.length();
    if (tsize < psize){
        std::swap(tsize, psize);
        std::swap(t, p);
    }
    for (int i = 0; i <= tsize - psize; ++i) {
        std::string temp;
        for (int j = i; j <= i + psize - 1; ++j)
            temp.push_back(t[j]);
        if (temp == p)
            ans.push_back(i);
    }
    return ans;
}
int main() {
    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    std::string t, p;
    std::cin >> p >> t;
    std::vector<int> ans = brute_force(t, p);
    std::cout << ans.size() << std::endl;
    for (auto &i:ans) {
        std::cout << i + 1 << " ";
    }
    return 0;
}
