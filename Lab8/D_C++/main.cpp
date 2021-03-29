#include <iostream>
#include <vector>

using namespace std;
int component_num = 0;

int n, m;
vector<int> graph[100000];
vector<bool> visited;
vector<int> component;

void dfs (int v) {
    visited[v] = true;
    component.push_back (v);
    for (int to : graph[v]) {
        if (! visited[to])
            dfs (to);
    }
}

void find_comps() {
    for (int i=0; i<n; ++i)
        visited[i] = false;
    for (int i=1; i<n; ++i)
        if (! visited[i]) {
            component.clear();
            dfs (i);

            cout << "Component:";
            for (int j : component)
                cout << ' ' << j;
            cout << endl;
        }
}
int main() {
    int a, b;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        component.push_back(0);
        visited.push_back(false);
    }
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph[a].push_back(b);
    }

    find_comps();
    return 0;
}
