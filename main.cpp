#include <iostream>
#include <stack>

using namespace std;

typedef int key_t;
typedef struct {} data_t;
typedef int delta_t;


class TAvlTree {
    friend int main();
public:
    TAvlTree():
        root(0)
    {}

    ~TAvlTree() {
        free(root);
    }

    void recursivePostOrderTraverse() {
        recursivePostOrderTraverse(root);
    }

    void insert(key_t key, data_t data = data_t()) {
        if (root == 0) {
            root = new node_t(0, key, data);
            return;
        }

        node_t * parrent = root;
        for (;;) {
            node_t *& current = key < parrent->key ?
                        parrent->left:
                        parrent->right;
            if (current == 0) {
                current = new node_t(parrent, key, data);
                return;
            }

            parrent = current;
        }
    }

    key_t min() const {
        return findLeft(root)->key;
    }

    key_t max() const {
        return findRight(root)->key;
    }


    void postOrderTraverse() {
        stack<node_t *> s;
        s.push(root);
        while (!s.empty()) {
            while (s.top() != 0) {
                s.push(s.top()->left);
            }
            s.pop();

            if (s.empty()) {
                break;
            }

            node_t * current = s.top();
            visit(current);
            s.pop();
            s.push(current->right);
        }
    }


//    node_t * baseFind(node_t * root, key_t key);
//    node_t * baseInsert(node_t * root, key_t key, data_t data = data_t());
//    int ballance(node_t * root);
private:

    struct node_t {
        node_t(node_t * parrent, key_t key, data_t data = data_t()):
            parrent(parrent),
            key(key),
            data(data),
            dh(0),
            left(0),
            right(0)
        {}

        node_t * parrent;
        key_t key;
        data_t data;
        delta_t dh;
        node_t * left;
        node_t * right;
    };

    void visit(node_t * node) {
        cout << node->key << " ";
    }
    static void recursivePostOrderTraverse(node_t * root) {
        if (root == 0) {
            return;
        }

        recursivePostOrderTraverse(root->left);
        recursivePostOrderTraverse(root->right);

        cout << root->key << " ";
    }

    static void leftRotate(node_t *& root) {
        node_t * right = root->right;
        node_t * rightLeft = right->left;

        root->right = rightLeft;
        rightLeft->parrent = root;
        right->left = root;
        right->parrent = root->parrent;
        root->parrent = right;
        root = right;
    }

    static void rightRotate(node_t *& root) {
       node_t * left = root->left;
       node_t * leftRight = left->right;

       root->left = leftRight;
       leftRight->parrent = root;
       left->right = root;
       left->parrent = root->parrent;
       root->parrent = left;
       root = left;
    }

    static node_t * findLeft(node_t * root) {
        node_t * current = root;
        while (current->left != 0) {
            current = current->left;
        }

        return current;
    }

    static node_t * findRight(node_t * root) {
        node_t * current = root;
        while (current->right != 0) {
            current = current->right;
        }

        return current;
    }

    static void free(node_t * root) {
        if (root == 0) {
            return;
        }

        free(root->left);
        free(root->right);

        delete root;
    }

    node_t * root;
};


int main()
{
    TAvlTree avlTree;
    size_t size = 0;
    cin >> size;
    for (size_t i = 0; i < size; ++i) {
        key_t key = 0;
        cin >> key;
        avlTree.insert(key);
    }

    avlTree.postOrderTraverse();
    cout << endl;

    cout << "min = " << avlTree.min() << endl;
    cout << "max = " << avlTree.max() << endl;
    return 0;
}

