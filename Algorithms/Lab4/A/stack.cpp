#include <iostream>
#include <vector>

using namespace std;

struct stack {
    vector <int> a;
    int size = 0;
    explicit stack(int n) {
        a.resize(n);
    }
    int pop() {
        return a[size--];
    }
    void push(int val) {
        a[++size] = val;
    }
};

int main() {
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    long n;
    cin >> n;
    char com;
    long mean;
    stack a(n);
    for (int i = 0; i < n; ++i) {
        cin >> com;
        if (com == '+') {
            cin >> mean;
            a.push(mean);
        }
        else {
            cout << a.pop() << "\n";
        }
    }
    return 0;
}