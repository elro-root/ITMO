#include <iostream>
using namespace std;

struct BST {
    int key{};
    int height{};
    int diff{};
    size_t number{};
    BST* left = nullptr;
    BST* right = nullptr;
};
int N;
BST *tree;

void height_of_tree(BST *node){
    for (int i = N - 1; i >= 0; --i) {
        if (node[i].right) {
            node[i].height = node[i].right->height + 1;
        }
        else
            node[i].height = 1;
        if (node[i].left)
            node[i].height = (node[i].height > node[i].left->height + 1)
                             ? node[i].height : (node[i].left->height + 1);
        else
            node[i].height = 1;
    }
}

void diff(BST *node){
    for (int i = 0; i < N; ++i) {
        if (!(node[i].right))
            if (node[i].left)
                node[i].diff = node[i].left->height;
        if (!(node[i].left))
            if (node[i].right)
                node[i].diff = node[i].right->height;
        if (node[i].right && node[i].left)
            node[i].diff = node[i].right->height - node[i].left->height;
    }
}

void create_tree(BST *node){
    int left_son;
    int right_son;
    //создание дерева
    for (int i = 0; i < N; ++i) {
        cin >> node[i].key >> left_son >> right_son;
        if (left_son != 0)
            node[i].left = &node[left_son - 1];

        if (right_son != 0)
            node[i].right = &node[right_son - 1];
    }
    height_of_tree(node);
    diff(node);
}

BST* rotate_left(BST *node){
    BST *b = node->right;
    node->right = b->left;
    b->left = node;
    height_of_tree(tree);
    diff(tree);
    return b->left;
}

BST* rotate_right(BST *node){
    BST *b = node->left;
    node->left = b->right;
    b->right = node;
    height_of_tree(node);
    diff(node);
    return b;
}

BST* balance(BST* node){ // балансировка узла node
    height_of_tree(node);
    if( node->diff==2 )
    {
        if ((node->right->diff) < 0 )
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if( node->diff==-2 )
    {
        if( (node->left)->diff > 0  )
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node; // балансировка не нужна
}


void key_number(BST *node){
    for (int i = 0; i < N; ++i) {
        node[i].number = i + 1;
    }
}

int main(){
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N;
    tree = new BST[N];
    create_tree(tree);
    key_number(tree);
    tree = balance(tree);
    cout << N << "\n";
    for (int i = 0; i < N; ++i) {
        cout << tree[i].key << " ";
        if (tree[i].left)
            cout <<tree[i].left->number<< " ";
        else
            cout << "0 ";
        if (tree[i].right)
            cout << tree[i].right->number << " ";
        else
            cout << "0 ";
        cout <<"\n";
    }
    return 0;
}