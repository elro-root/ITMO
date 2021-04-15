#include <iostream>

using namespace std;

int n;
double h[10000];

double garland() {
    double right = 0;
    double left = h[0];
    while (left - right > 0.000001) {
        h[1] = (left + right) / 2;
        bool b = true;
        for (int i = 2; i < n; i++) {
            h[i] = 2 * h[i - 1] - h[i - 2] + 2;
            if (h[i] < 0) {
                b = false;
                break;
            }
        }
        if (b)
            left = h[1];
        else
            right = h[1];
    }
    return h[n - 1];
}

int main() {
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin.tie();

    cin >> n;
    cin >> h[0];
    double a = garland();
    cout.precision(2);
    cout << fixed << a;
    return 0;
}