#include <iostream>
#include <vector>

using namespace std;

struct node {
    int id;
    int key;
    int height;
    node *left;
    node *right;
    node(int id = -1, int key = -1e9, node *left = nullptr, node *right = nullptr): id(id), key(key), left(left), right(right) {
        this->height = 1;
    }
};

int get_height(node *node) {
    return node == nullptr ? 0 : node->height;
}

void update_height(node *node) {
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
}

int get_balance(node *node) {
    return get_height(node->right) - get_height(node->left);
}

node *rotate_left(node *node) {
    auto r = node->right;
    node->right = r->left;
    r->left = node;

    update_height(node);
    update_height(r);
    return r;
}

node *rotate_right(node *node) {
    auto l = node->left;
    node->left = l->right;
    l->right = node;

    update_height(node);
    update_height(l);
    return l;
}

node *big_rotate_left(node *node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

node *big_rotate_right(node *node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

node *balance(node *node) {
    int bal = get_balance(node);
    if (abs(bal) < 2) {
        return node;
    }
    if (bal == 2) {
        if (get_balance(node->right) == -1) {
            return big_rotate_left(node);
        } else {
            return rotate_left(node);
        }
    } else {
        if (get_balance(node->left) == 1) {
            return big_rotate_right(node);
        } else {
            return rotate_right(node);
        }
    }
}

void out(node *node) {
    if (node == nullptr) {
        return;
    }
    cout << node->key << ' ';
    cout << (node->left == nullptr ? 0 : node->left->id + 1) << ' ';
    cout << (node->right == nullptr ? 0 : node->right->id + 1) << '\n';

    out(node->left);
    out(node->right);
}

void set_new_ids(node *v, int &number) {
    if (v == nullptr) {
        return;
    }
    v->id = number;
    number++;
    set_new_ids(v->left, number);
    set_new_ids(v->right, number);
}


void dfs(node *node, vector<bool> &visited) {
    if (node == nullptr || visited[node->id]) {
        return;
    }
    visited[node->id] = true;

    dfs(node->left, visited);
    dfs(node->right, visited);

    update_height(node);
}

int main() {
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);
    int n;
    cin >> n;
    vector<node*> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new node();
    }
    for (int i = 0; i < n; i++) {
        nodes[i]->id = i;
        int key, left, right;
        cin >> key >> left >> right;
        nodes[i]->key = key;

        left--; right--;
        if (left != -1) {
            nodes[i]->left = nodes[left];
        }
        if (right != -1) {
            nodes[i]->right = nodes[right];
        }
    }

    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(nodes[i], visited);
        }
    }

    auto root = balance(nodes[0]);

    int num = 0;
    set_new_ids(root, num);
    cout << num << "\n";
    out(root);
    return 0;
}