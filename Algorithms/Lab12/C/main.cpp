#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void LCS(int lenX, int lenY, std::string str1, std::string str2, std::vector<int>& lastMatrixStr) {
    std::vector<std::vector<int>> k(2, std::vector<int>(lenY + 1));
        for (int j = 0; j <= lenY; ++j)
            k[1][j] = 0;
        for (int i = 0; i < lenX; ++i) {
            for (int j = 0; j <= lenY; ++j)
                k[0][j] = k[1][j];
                
            for (int j = 1; j <= lenY; ++j) {
                if (str1[i] == str2[j - 1])
                    k[1][j] = k[0][j - 1] + 1;
                else
                    k[1][j] = std::max(k[1][j - 1], k[0][j]);
            }
        }
    for (int j = 0; j <= lenY; ++j)
        lastMatrixStr[j] = k[1][j];
}

void h_berg(int lenX, int lenY, std::string str1, std::string str2){
    if (lenY == 0)
        return;

    if (lenX == 1) {
        int f = str2.find_first_of(str1[0]);
        if (f != std::string::npos)
            std::cout << str1[0];
        return;
    }

    std::vector<int> l1(lenY + 1);
    std::vector<int> l2(lenY + 1);
    int mid = lenX / 2;

    LCS(mid, lenY, str1.substr(0, mid), str2, l1);

    std::string str1_second = str1;
    std::string str2_second = str2;
    reverse(str1_second.begin(), str1_second.end());
    reverse(str2_second.begin(), str2_second.end());

    LCS(mid + 1, lenY, str1_second.substr(0, lenX - mid), str2_second, l2);

    int maxV = l2[0], maxJ = 0;

    for (int j = 0; j <= lenY; ++j) {
        if (l1[j] + l2[lenY - j] > maxV) {
            maxV = l1[j] + l2[lenY - j];
            maxJ = j;
        }
    }

    if (!mid)
        ++mid;
    if (l1[lenY] > maxV)
        maxJ = lenY;

    h_berg(mid, maxJ, str1.substr(0, mid), str2.substr(0, maxJ));
    h_berg(lenX - mid, lenY - maxJ, str1.substr(mid, lenX), str2.substr(maxJ, lenY));
}
int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie();
//    std::cin.tie();
    std::string str1, str2;
    std::cin >> str1 >> str2;
    h_berg(str1.length(), str2.length(), str1, str2);
    return 0;
}