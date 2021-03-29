#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > g(100000);
vector<bool> used;
vector<int> order;

void dfs(int v) // топологическая сортировка
{
    used[v] = true;
    for (auto i: g[v])
        if (!used[i])
            dfs(i);
    order.push_back(v);
}

int main()
{
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    int n, m, v1, v2;
    cin >> n >> m;
    g.resize(n);
    used.assign(n, false);
    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);
    bool flag = true; // создаём флаг
    for (int i = order.size() - 1; i > 0; i--)
    {
        bool tempFlag = false; // доп. флаг
        for (int j = 0; j < g[order[i]].size(); j++)
            if (g[order[i]][j] == order[i - 1]) // если вершина из топологической сортировки совпадает с текущей
                tempFlag = true;
        if (!tempFlag) // если прошли все вершины и флаг не изменился
        {
            flag = false; // то гамильнотого путя нет
            break;
        }
    }
    flag ? cout << "YES" : cout << "NO";
    return 0;
}