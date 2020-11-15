#include <iostream>
#define int long long

using namespace std;

struct Node {
    int key{};
    size_t height = 1;
    Node* parent = nullptr;
};
Node *node;
signed main() {
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    size_t N;
    cin >> N;
    node = new Node[N];

    size_t left_son;
    size_t right_son;
    size_t tree_height = 0;

    for (int i = 0; i < N; ++i) {
        cin >> node->key >> left_son >> right_son;

        if (left_son != 0) {
            node[left_son - 1].parent = &node[i];
        }
        
        if (right_son != 0) {
            node[right_son - 1].parent = &node[i];
        }
        
        if (node[i].parent != nullptr) {
            node[i].height = node[i].parent->height + 1;
        }
        
        if (node[i].height > tree_height) {
            tree_height = node[i].height;
        }
    }
    cout << tree_height;
}