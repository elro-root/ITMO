#include <iostream>
#include <vector>
using namespace std;
// #define int long long
int n = 1, k = 0;
vector<int> a;
vector <int> b;
void QuickSort(int l, int r) {
    int mid = l + rand() % (r - l); // возьмем случайное число, чтобы нельзя было подобрать плохой тест
    if (r - 1 == l) { // если всего одно число - значит оно и есть К-ая пор статистика
        cout << a[l];
        return;
    }
    // расположим все элементы, которые меньше опорного элемента левее него, а которые больше - правее
    int itl = 0, itr = r - l - 1, left, right;
    b.resize(r - l, 0);
    for (int i = l; i < r; i++) {
        if (a[i] > a[mid]) {
            b[itr] = a[i];
            itr--;
        }
        if (a[i] < a[mid]) {
            b[itl] = a[i];
            itl++;
        }
    }
    // все элементы, которые мы еще не заполнили = опорному элемнту (a[mid])
    left = itl + l;
    right = itr + l;
    while (itl <= itr) {
        b[itl] = a[mid];
        itl++;
    }
    for (int i = l; i < r; i++) {
        a[i] = b[i - l];
    }
    if (left <= k && k <= right) {
        cout << a[k];
        return;
    }
    // запустимся в одну из частей массива в зависимости от того, где к
    if (k < left) {
        QuickSort(l, left);
    }
    if (k > right) {
        QuickSort(right + 1, r);
    }
}
int A, B, C, pt = 0;
long random() {
    int ans = A * a[pt] + B * a[pt + 1] + C;
    pt++;
    return ans;
}
signed main() {
    //откроем файлы для чтения и записи как stdin, stdout
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
    //сделаем быстрый ввод-вывод
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();
    a.resize(2);
    cin >> n >> k >> A >> B >> C >> a[0] >> a[1];
    k--;
    a.resize(n);
    for (int i = 2; i < n; i++) {
        a[i] = random();
    }
    QuickSort(0, n);
}
