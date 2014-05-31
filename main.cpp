#include <iostream>

using namespace std;

typedef int key_t;
typedef struct {} data_t;
typedef int delta_t;


class TAvlTree {
public:
    node_t * baseFind(node_t * root, key_t key);
    node_t * baseInsert(node_t * root, key_t key, data_t data = data_t());
    node_t * findLeft(node_t * root);
    node_t * findRight(node_t * root);
    node_t * leftRotate(node_t * root);
    node_t * rightRotate(node_t * root);
    int ballance(node_t * root);
private:

    struct node_t {
        key_t key;
        data_t data;
        delta_t dh;
        node_t * left;
        node_t * right;
        node_t * parrent;
    };
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

