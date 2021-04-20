#include<iostream>
#include <string>
//#include "input.hpp"
std::string lcs(std::string X, std::string Y, unsigned long m, unsigned long n ) {
    int L[2][n + 1];
    bool bi;
    for (int i = 0; i <= m; i++) {
        bi = i & 1;
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[bi][j] = 0;

            else if (X[i-1] == Y[j-1]){
                L[bi][j] = L[1 - bi][j - 1] + 1;
            }
            else
                L[bi][j] = std::max(L[1 - bi][j],
                                    L[bi][j - 1]);
        }
    }
    int index = L[bi][n];
    std::string lcs(index, ' ');
    unsigned long i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs[index - 1] = X[i-1];
            --i; --j; --index;
        }
        else if (L[1 - bi][j] > L[bi][j-1])
            --i;
        else
            --j;
        bi = i & 1;
    }
    return lcs;
}

/* Driver program to test above function */
int main(){
//    input();
    std::string X, Y;
    std::cin >> X >> Y;
    unsigned long m = X.size();
    unsigned  long n = Y.size();
    std::string answer = lcs(X, Y, m, n);
    std::cout << answer << std::endl;
    return 0;
}