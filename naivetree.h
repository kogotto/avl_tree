#ifndef NAIVETREE_H
#define NAIVETREE_H

template<class T, class U>
struct TNodeData {
    typedef T key_t;
    typedef U data_t;

    key_t key;
    data_t data;
};

template<class T, class U, class F = TNodeData<T, U> >
class TNaiveTree {
public:
    typedef T key_t;
    typedef U data_t;
    typedef F node_data_t;
    typedef class node_t *node_pointer;
    typedef node_pointer &node_pointer_ref;

    TNaiveTree():
        root(0)
    {}

    ~TNaiveTree() {
        free(root);
    }

    class BaseFinder {
    public:

    private:
        node_pointer_ref plase;
    };

    void naive_insert(const node_data_t & node_data) {
        BaseFinder result = find(node_data->key, BaseFinder());
        result.plase = new node_t(node_data);
    }


    template<class Finder>
    Finder & find(key_t key, Finder & finder) {
        node_pointer current = root;
        while (current != 0) {
            if (finder(current)) {
                return finder;
            }
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

    }


private:
    struct node_t:
            public node_data_t {

        node_t(const node_data_t & node_data):
            node_data_t(node_data),
            left(0),
            right(0)
        {}

        node_pointer left;
        node_pointer right;
    };

    static void free(node_pointer root) {
        if (root == 0) {
            return;
        }

        free(root->left);
        free(root->right);

        delete root;
    }

    node_pointer root;
};

#endif // NAIVETREE_H
