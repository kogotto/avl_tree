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

private:
    struct node_t:
            public node_data_t {
        node_pointer left;
        node_pointer right;
    };

    static void free(node_)

    node_pointer root;
};

#endif // NAIVETREE_H
