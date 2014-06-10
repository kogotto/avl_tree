#include <iostream>
#include <stack>

using namespace std;

typedef int key_t;
typedef struct {} data_t;
typedef int delta_t;


class TAvlTree {
    friend int main();
public:

    template<class T>
    struct Deleter {
        void operator() (const T * node) const {
            delete node;
        }
    };

    TAvlTree():
        root(0)
    {}

    ~TAvlTree() {
        recursivePostOrderTraverse(root, Deleter<node_t>());
    }

    template<class action_t>
    void recursivePostOrderTraverse(action_t & action) {
        recursivePostOrderTraverse(root, action);
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


    void inOrderTraverse() {
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

    template<class action_t>
    static void recursivePostOrderTraverse(node_t * root, const action_t & action) {
        if (root == 0) {
            return;
        }

        recursivePostOrderTraverse(root->left, action);
        recursivePostOrderTraverse(root->right, action);

        action(root);
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

    static void rotate(node_t *& root) {
        if (root->dh == 0) {
            return;
        }

        if (root->dh > 0) {
            rightRotate(root);
        } else {
            leftRotate(root);
        }
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

    avlTree.inOrderTraverse();
    cout << endl;

    cout << "min = " << avlTree.min() << endl;
    cout << "max = " << avlTree.max() << endl;
    return 0;
}

