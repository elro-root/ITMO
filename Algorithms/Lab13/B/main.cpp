#include <iostream>
#include <vector>
#include <string>

std::vector<int> zFunction (const std::string & s) {
    int n = (int) s.length();
    std::vector<int> z (n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i,  r = i + z[i] - 1;
    }
    return z;
}

std::vector<unsigned int> search(std::string & t, std::string & p){
    std::vector<unsigned int> ans;
    unsigned long tsize = t.length();
    unsigned long psize = p.length();
    if (tsize < psize){
        std::swap(tsize, psize);
        std::swap(t, p);
    }
    std::vector<int> zf = zFunction((p + "#" + t));
    for (unsigned int i = psize; i <= tsize + 1; ++i) {
        if (zf[i] == psize)
            ans.push_back(i - psize);
    }
    return ans;
}

int main() {
    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    std::string t, p;
    std::cin >> p >> t;
    std::vector<unsigned int> ans = search(t, p);
    std::cout << ans.size() << std::endl;
    for (auto &i:ans) {
        std::cout << i << " ";
    }
    return 0;
}
