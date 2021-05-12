#include <iostream>
#include <vector>
#include <algorithm>

struct vertex {
    vertex (int p1, int ch = -1) {
        p = p1;
        index = ch;
        go = std::vector <int>(26, -1);
        next = std::vector <int>(26, -1);
    }

    std::vector <int> next;
    std::vector <int> go;
    std::vector <int> termIdx;

    int p;
    int suffix = -1;
    int link = -1;
    int index;
};


class forest {
private:
    int count = 0;
    std::vector <vertex> t;

public:
    forest () {
        t.push_back(vertex(0));
    }

    void addWord (std::string &s) {
        int v = 0;
        for (char c: s) {
            int idx = (int) c - 'a';
            if (t[v].next[idx] == -1) {
                vertex v1 = vertex(v, idx);
                t.push_back(v1);
                t[v].next[idx] = (int) t.size() - 1;
            }
            v = t[v].next[idx];
        }
        t[v].termIdx.push_back(count);
        ++count;
    }

    int getLinkToLastCharachter (int v) {
        if (t[v].link == -1) {
            int suf = getSuff(v);
            if (suf == 0)
                t[v].link = 0;
            else if (t[suf].termIdx.empty())
                t[v].link = getLinkToLastCharachter(suf);
            else
                t[v].link = suf;
        }
        return t[v].link;
    }

    int go (int v, int index) {
        if (t[v].go[index] == -1) {
            // если переход есть, то автомат должен вести туда же
            if (t[v].next[index] != -1)
                t[v].go[index] = t[v].next[index];
                // если перехода нет из корня, то нужно сделать петлю
            else if (v == 0)
                t[v].go[index] = 0;
                // иначе находим суффиксную ссылку и запишем её в переход
            else
                t[v].go[index] = go(getSuff(v), index);
        }
        return t[v].go[index];
    }

    vertex *getVertex(int v) {
        return &t[v];
    }

    //Функция для вычисления суффиксной ссылки
    int getSuff(int v) {
        if (t[v].suffix == -1) {
            // для строк длины меньше двух, суффиксная ссылка это корень
            if (v == 0 || t[v].p == 0)
                t[v].suffix = 0;
                // для остальных случаев 
            else
                t[v].suffix = go(getSuff(t[v].p), t[v].index);
        }
        return t[v].suffix;
    }

    ~forest () = default;
};


int main () {
    freopen("search4.in", "r", stdin);
    freopen("search4.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    int n;
    std::cin >> n;
    std::vector <bool> check(n, false);

    forest a = forest();

    std::string si, t;
    for (int i = 0; i < n; ++i) {
        std::cin >> si;
        a.addWord(si);
    }
    std::cin >> t;
    int current = 0;
    for (char c: t) {
        int idx = (int) c - 'a';
        current = a.go(current, idx);
        auto vertex = a.getVertex(current);
        int local = current;
        while (local != 0) {
            if (!vertex->termIdx.empty()) {
                for (int i: vertex->termIdx)
                    check[i] = true;
                vertex->termIdx.clear();
            }
            local = a.getLinkToLastCharachter(local);
            vertex = a.getVertex(local);
        }
    }
    for (bool i: check) {
        if (i)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
    return 0;
}
