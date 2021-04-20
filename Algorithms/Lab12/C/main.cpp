#include<iostream>
#include <string>
#include "input.hpp"
std::string lcs(std::string X, std::string Y, unsigned long m, unsigned long n ) {
    int L[m+1][n+1];
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = std::max(L[i-1][j], L[i][j-1]);
        }
    }
    int index = L[m][n];
    std::string lcs(index, ' ');
    unsigned long i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs[index - 1] = X[i-1];
            i--; j--; index--;
        }
            // If not same, then find the larger of two and
            // go in the direction of larger value
        else if (L[i-1][j] > L[i][j-1])
            i--;
        else
            j--;
    }
    return lcs;
}

/* Driver program to test above function */
int main(){
    input();
    std::string X, Y;
    std::cin >> X >> Y;
    unsigned long m = X.size();
    unsigned  long n = Y.size();
    std::string answer = lcs(X, Y, m, n);
    std::cout << answer << std::endl;
    return 0;
}