#include <iostream>

using namespace std;

int N;
bool flag = true;

struct Node
{
    int left;
    int key;
    int right;
};

void check(struct Node BST[], int x, int min, int max)
{
    if(flag)
    {
        if (BST[x].key <= min || BST[x].key >= max)
            flag = false;
        if (BST[x].right != 0)
            check(BST, BST[x].right - 1, BST[x].key, max);
        if (BST[x].left != 0)
            check(BST, BST[x].left - 1, min, BST[x].key);
    }
}

signed main()
{
    freopen("check.in", "max", stdin);
    freopen("check.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N;
    struct Node BST[N];

    if (N == 0)
    {
        cout << "YES";
    }

    for (int i = 0; i < N; i++)
        cin >> BST[i].key >> BST[i].left >> BST[i].right;

    check(BST, 0, -1000000001, 1000000001);

    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
