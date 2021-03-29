#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define int long long
signed main() {
    //откроем файлы для чтения и записи как stdin, stdout
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
    //сделаем быстрый ввод-вывод
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();
    int n;
    cin >> n;
    //сделаем map, в которой для каждой страны будет лежать список участников в порядке финиширования
    map <string, vector <string> > mp;
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        mp[a].push_back(b);
    }
    //выведим ответ
    for (auto ans : mp) {
        cout << "=== " << ans.first << " ===" << endl;
        for (auto name : ans.second) {
            cout << name << endl;
        }
    }
}
