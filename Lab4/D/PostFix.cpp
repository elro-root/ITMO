#include <iostream>
#include <vector>

using namespace std;

class Stack
{
    vector<int> data;

public:
    void push(int element)
    {
        data.push_back(element);
    }

    int pop()
    {
        int element = data.back();
        data.pop_back();
        return element;
    }
};

int main()
{
    Stack stack;

    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    string str;
    while (cin >> str)
    {
        int res;

        if (str[0] - 48 >= 0)
            stack.push(str[0] - 48);
        else
        {
            int element1 = stack.pop(), element2 = stack.pop();

            switch (str[0])
            {
                case '+':
                    res = element2 + element1;
                    stack.push(res);
                    break;

                case '-':
                    res = element2 - element1;
                    stack.push(res);
                    break;

                case '*':
                    res = element2 * element1;
                    stack.push(res);
                    break;
            }

        }
    }

    cout << stack.pop();
    return 0;
}