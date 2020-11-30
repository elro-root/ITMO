#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashMapEntry{
public:
    HashMapEntry(string key_input, string value_input){
        key = move(key_input);
        value = move(value_input);
    }
    string key;
    string value;
    HashMapEntry *prev = nullptr;
    HashMapEntry *next = nullptr;

};

vector<list<HashMapEntry*>> HashTable(100001);
HashMapEntry *head;

void input(){
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
}

int hashFunc(string &s){
    const int p = 31;
    int hash = 0, p_pow = 1;
    for (char i : s){
        hash += (i - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    hash = abs(hash)%(HashTable.size());
    return hash;
}

void put(string& key,  string& value){
    int hash = hashFunc(key);

    for (auto iterator = HashTable[hash].begin(); iterator != HashTable[hash].end(); ++iterator){
        if((*iterator)->key == key){
            (*iterator)->value = value;
            return;
        }
    }

    auto *entry = new HashMapEntry(key, value);
    HashTable[hash].push_back(entry);

    if(head == nullptr)
        head = entry;
    else{
        head->next = entry;
        entry->prev = head;
        head = entry;
    }
}

string get(string& key){
    int hash = hashFunc(key);

    for( HashMapEntry *element : HashTable[hash]){
        if(element->key == key)
            return element->value;
    }
    return "none";
}

void erase(string& key){
    int hash = hashFunc(key);

    for (auto iterator = HashTable[hash].begin(); iterator != HashTable[hash].end(); ++iterator){
        if((*iterator)->key == key){
            HashMapEntry *next, *prev;
            HashTable[hash].erase(iterator);

            next = (*iterator)->next;
            prev = (*iterator)->prev;

            if(prev != nullptr)
                prev->next = next;
            if(next != nullptr)
                next->prev = prev;
            else
                head = prev;

            delete *iterator;
            return;
        }
    }

}

string prev(string& key){
    int hash = hashFunc(key);

    for (auto  iterator = HashTable[hash].begin();  iterator != HashTable[hash].end(); ++ iterator){
        if((* iterator)->key == key){
            if((* iterator)->prev == nullptr)
                return "none";

            return (*iterator)->prev->value;
        }
    }
    return "none";
}

string next(string &key){
    int hash = hashFunc(key);
    for (auto iterator = HashTable[hash].begin(); iterator != HashTable[hash].end(); ++iterator){
        if((*iterator)->key == key){
            if((*iterator)->next == nullptr)
                return "none";
            return (*iterator)->next->value;
        }
    }
    return "none";
}


signed main(){
    string s;
    string key, value;

    input();

    while(cin >> s){
        cin >> key;

        if(s == "put"){
            cin >> value;
            put(key, value);
        }

        if(s == "get")
            cout << get(key) << "\n";

        if(s == "prev")
            cout << prev(key) << "\n";

        if(s == "next")
            cout << next(key) << "\n";

        if(s == "delete")
            erase(key);
    }
}