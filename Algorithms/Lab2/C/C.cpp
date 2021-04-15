#include <iostream>
#include <vector>
using namespace std;
#define int long long
int n = 1;
int k = 0;
vector <int> a;
//идея - сделаем сортировку слиянием и когда будем менять элементы местами (при слиянии двух массивов) найдем их кол-во
void MergeSort(int l, int r) {
    if (r - 1 == l) return;
    int mid = (l + r) / 2;  // rand()%(r-l);
    MergeSort(l, mid);
    MergeSort(mid, r);
    int p1 = l, p2 = mid;
    int pb = 0, b[r - l];
    while (p1 != mid && p2 != r) {
        if (a[p1] <= a[p2]) {
            b[pb] = a[p1];
            p1++;
            pb++;
        } else {
            b[pb] = a[p2];
            p2++;
            pb++;
            k += mid - p1; // если мы из правой части перебрасываем число в левую, то он больше, чем mid - p1 чисел в левой части
        }
    }
    while (p1 != mid) {
        b[pb] = a[p1];
        p1++;
        pb++;
    }

    while (p2 != r) {
        b[pb] = a[p2];
        p2++;
        pb++;
    }

    for (int i = l; i < r; i++) {
        a[i] = b[i - l];
    }
}
signed main() {
    //откроем файлы для чтения и записи как stdin, stdout
    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);
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
    cout << k;
}
