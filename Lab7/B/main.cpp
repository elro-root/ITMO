#include <iostream>
#include <queue>

using namespace std;

struct BST{
    int key{};
    unsigned char height{};
    int diff{};
    BST* left = nullptr;
    BST* right = nullptr;
};
int N;
BST *tree;

BST* height_of_tree(BST *node){
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
    return node;
}

unsigned char height(BST* p){
    return p?p->height:0;
}

int diff(BST* p){
    return height(p->right) - height(p->left);
}

void fix_height(BST* p){
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

BST* rotate_left(BST* node){
    BST* p = node->right;
    node->right = p->left;
    p->left = node;
    fix_height(node);
    fix_height(p);
    return p;
}

BST* rotate_right(BST* node){
    BST* q = node->left;
    node->left = q->right;
    q->right = node;
    fix_height(node);
    fix_height(q);
    return q;
}

BST* balance(BST* node){
    fix_height(node);
    if(node->diff == 2)
    {
        if((node->right)->diff < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if(node->diff == -2)
    {
        if((node->left)->diff > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

BST* read(BST* node){
    for (int i = 0; i < N; ++i) {
        int left_c, right_c;
        cin >> node[i].key >> left_c >> right_c;
        if (left_c != 0)
            node[i].left = &node[left_c - 1];
        if (right_c != 0)
            node[i].right = &node[right_c - 1];
    }
    height_of_tree(node);
    for (int i = 0; i < N; ++i) {
        node[i].diff = diff(&node[i]);
    }
    return node;
}

int out_bfs(BST *root) {
    int i = 1;
    queue<BST*> q;

    if (root) {
        q.push(root);
    } else {
        return 0;
    }
    while (!q.empty()) {
        const BST * const temp_node = q.front();
        q.pop();

        cout << temp_node->key << " ";

        if (temp_node->left) {
            q.push(temp_node->left);
            cout << ++i << " ";
        } else {
            cout << "0 ";
        }

        if (temp_node->right) {
            q.push(temp_node->right);
            cout << ++i;
        } else {
            cout << "0";
        }
        cout << "\n";
    }
    return 0;
}

int main(){
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    cin >> N;
    tree = new BST[N];
    tree = read(tree);
    tree = balance(tree);
    cout << N <<"\n";
    out_bfs(tree);
    return 0;
}