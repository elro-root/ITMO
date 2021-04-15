#include <iostream>
#include <vector>

using namespace std;

struct queue {
    vector <int> a;
    int head = 0;
    int tail = 0;
    explicit queue(int n) {
        a.resize(n);
    }
    int pop() {
        int x = a[head];
        head = head + 1;
        return x;
    }
    void push(int val) {
        a[tail] = val;
        tail = tail + 1;
    }
};

int main() {
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    long n;
    cin >> n;
    char com;
    long mean;
    queue a(n);
    for (int i = 0; i < n; ++i) {
        cin >> com;
        if (com == '+') {
            cin >> mean;
            a.push(mean);
        }
        else {
            if (a.head != a.tail) {
                cout << a.pop() << "\n";
            }
        }
    }
    return 0;
}