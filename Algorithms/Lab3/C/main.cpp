#include <iostream>
using namespace std;

string arr[1000], result[1000];
int n, m, k;

void radixsort(int position)
{
    char symb = 'a';
    int j = 0;
    for (int i = 0; i < 26; ++i)
    {
        for (int g = 0; g < n; ++g)
        {
            if (arr[g][position] == symb)
            {
                result[j] = arr[g];
                j++;
            }
        }
        symb++;
    }
    for (int i = 0; i < n; ++i)
        arr[i] = result[i];
}

int main()
{
    freopen("radixsort.in", "r", stdin);
    freopen ("radixsort.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    for (int i = m - 1; i >= m - k; --i)
        radixsort(i);
    for (int i = 0; i < n; ++i)
        cout << arr[i] << "\n";

    return 0;
}