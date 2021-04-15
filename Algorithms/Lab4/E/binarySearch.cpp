#include <iostream>
#include <vector>

using namespace std;

int bin_right(vector<int> & arr, int x) {
    int l = 0;
    int r = arr.size();

    while (l < r) {
        int mid = (l + r) / 2;
        if (x < arr[mid]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return arr[l - 1] == x ? l : -1;
}

int bin_left(vector<int> & arr, int x) {
    int l = 0;
    int r = arr.size();

    while (l < r) {
        int mid = (l + r) / 2;
        if (x <= arr[mid]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return arr[l] == x ? l + 1 : -1;
}

int main() {
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    int n, m;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cin >> m;

    for (int i = 0; i < m; ++i) {
        int x = 0;
        cin >> x;
        int leftest = bin_left(arr, x);
        int rightest = bin_right(arr, x);
        cout << leftest << " " << rightest << endl;
    }
}