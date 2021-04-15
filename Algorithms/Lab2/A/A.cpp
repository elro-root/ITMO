#include <iostream>
#include <vector>
using namespace std;
#define int long long
int n = 1;
vector<int> a;
void MergeSort(int l, int r) {
    if (l == r - 1) return;
    int mid = (l + r) / 2;
    // отсортируем вначале массив от l до mid и от mid до r
    MergeSort(l, mid);
    MergeSort(mid, r);
    int pb = 0;
    int b[r-l];
    int p1 = l, p2 = mid;
    // сольем две отсортированные части массива и запишем это в массив b
    while (p1 != mid && p2 != r) {
        if (a[p1] < a[p2]) {
            b[pb] = a[p1];
            p1++;
            pb++;
        } else {
            b[pb] = a[p2];
            p2++;
            pb++;
        }
    }
    while (p1 != mid) {
        b[pb] = a[p1];
        pb++;
        p1++;
    }

    while (p2 != r) {
        b[pb] = a[p2];
        pb++;
        p2++;
    }
    // переприсвоем элементы массива а, которые лежат в промежутке от l до r
    for (int i = l; i < r; i++) {
        a[i] = b[i - l];
    }
}
signed main() {
    //откроем файлы для чтения и записи как stdin, stdout
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    //сделаем быстрый ввод-вывод
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    MergeSort(0, n);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
}
