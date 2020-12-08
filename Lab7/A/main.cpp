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

int HeightOfTree(BST* node){
    if(node == nullptr)
        return 0;
    int left, right;
    if (node->l_child != nullptr)
        left = HeightOfTree(node->l_child);
    else
        left = -1;

    if (node->r_child != nullptr)
        right = HeightOfTree(node->r_child);
    else
        right = -1;
    int max = left > right ? left : right;
    return max + 1;

}
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
        if (tree[i].r_child != nullptr)
            tree[i].r_height = HeightOfTree(tree[i].r_child) + 1;
        if (tree[i].l_child != nullptr)
            tree[i].l_height = HeightOfTree(tree[i].l_child) + 1;
        cout << tree[i].r_height - tree[i].l_height << "\n";
    }
    return 0;
}