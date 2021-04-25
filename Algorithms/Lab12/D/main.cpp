#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> chessField;

void update(int i, int j) {
    chessField[i][j] += chessField[i - 2][j - 1] + chessField[i - 2][j + 1] + chessField[i - 1][j - 2] + chessField[i + 1][j - 2];
}

int main(){
    freopen("knight2.in", "r", stdin);
    freopen("knight2.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();
    int N, M;
    std::cin >> N >> M;
    N += 2;
    M += 2;
    chessField.resize(N + 1, std::vector<int> (M + 1, 0));
    chessField[2][2] = 1;
    int i = 2, j = 2;
    while (i != N - 1 || j != M - 1) {
        int x = i, y = j;
        while (x >= 2 && y < M)
            update(x--, y++);
        i == N - 1 ? ++j : ++i;
    }
    update(N - 1, M - 1);
    std::cout << chessField[N - 1][M - 1];
    return 0;
}