#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

vector<int> hashTable[1000001];
void input(){
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
}

int hashFunc(int element){
    int hash = abs((element % 1000001));
    return hash;
}
bool exists(int element){
    int hash = hashFunc(element);
    if (!(find(hashTable[hash].begin(), hashTable[hash].end(), element) == hashTable[hash].end()))
        return true;
    else
        return false;
}
void insert(int element) {
    if (!exists(element)) {
        int hash = hashFunc(element);

        if (hashTable[hash].empty()) {
            new vector<int>(hashTable[hash]);
            hashTable[hash].push_back(element);
        } else
            hashTable[hash].push_back(element);
    }
}

void erase(int element){
    if (exists(element)){
        int hash = hashFunc(element);
        hashTable[hash].erase(remove(hashTable[hash].begin(), hashTable[hash].end(), element), hashTable[hash].end());
    }
}

signed main(){
    input();
    string s;
    int x;
    while (cin >> s) {
        if (s == "insert") {
            cin >> x;
            insert(x);
        }
        if (s == "exists") {
            cin >> x;
            if (exists(x))
                cout << "true" << "\n";
            else
                cout << "false" << "\n";
        }
        if (s == "delete") {
            cin >> x;
            erase(x);
        }
    }
}