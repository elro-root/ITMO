#include <iostream>
using namespace std;

struct BST{
    int key{};
    int l_height{};
    int r_height{};
    BST* l_child = nullptr;
    BST* r_child = nullptr;
};
BST *tree;

void create_tree(BST *node, int N){
    int left_son;
    int right_son;

    for (int i = 0; i < N; ++i) {
        cin >> node[i].key >> left_son >> right_son;

        if (left_son != 0)
            node[i].l_child = &node[left_son - 1];

        if (right_son != 0)
            node[i].r_child = &node[right_son - 1];
    }
    for (int i = N - 1; i >= 0; --i) {
        if (node[i].r_child){
            int a = (node[i].r_child)->r_height;
            int b = node[i].r_child->l_height;
            node[i].r_height = ((a >= b) ? a:b) + 1;
        } else {
            node[i].r_height = 1;
        }
        if (node[i].l_child != nullptr){
            int a = node[i].l_child->r_height;
            int b = node[i].l_child->l_height;
            node[i].l_height = ((a >= b) ? a:b) + 1;
        } else {
            node[i].l_height = 1;
        }
    }
}

int main(){
    size_t N;

    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N;
    tree = new BST[N];
    create_tree(tree, N);
    for (int i = 0; i < N; ++i) {
        cout << tree[i].r_height - tree[i].l_height << "\n";
    }
    return 0;
}