#include <iostream>
#include <vector>

using namespace std;

void input(){
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
}

vector<vector<pair<string, string>>> hashTable(100001);

int hashFunc(string &s){
    const int p = 31;
    int hash = 0, p_pow = 1;
    for (char i : s){
        hash += (i - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    hash = abs(hash)%(hashTable.size());
    return hash;
}

void MapPut(string &key, string &value){

    int hash = hashFunc(key);
    for (auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it){
        if(it->first == key){
            it->second = value;
            return;
        }
    }

    hashTable[hash].push_back(make_pair(key, value));
}

string MapGet(string &key){
    int hash = hashFunc(key);
    for(pair pair:hashTable[hash]){
        if(pair.first == key)
            return pair.second;
    }
    return "none";
}

void MapDelete(string &key){
    int hash = hashFunc(key);
    for (auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it){
        if(it->first == key){
            hashTable[hash].erase(it);
            return;
        }
    }
}


signed main(){
    string s;
    string key, value;

    input();

    while(cin >> s){
        cin >> key;
        if(s == "put"){
            cin >> value;
            MapPut(key, value);
        }

        if(s == "get")
            cout << MapGet(key) << "\n";

        if(s == "delete")
            MapDelete(key);
    }
}