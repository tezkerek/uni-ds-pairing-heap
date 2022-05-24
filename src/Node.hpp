#include <memory>

template <class T> class Node;

template <class T> using NodePtr = std::shared_ptr<Node<T>>;

template <class T> class Node {
protected:
    T value;
    NodePtr<T> next;
    NodePtr<T> left;

public:
    Node(T value);

    T getValue() const;

    NodePtr<T> getLeftChild() const;
    void setLeftChild(const NodePtr<T> &node);

    NodePtr<T> getNextSibling() const;
    void setNextSibling(const NodePtr<T> &node);

    void addChild(const NodePtr<T> &node);
};

template <class T>
Node<T>::Node(T value) : value(value), next(nullptr), left(nullptr) {}

template <class T> T Node<T>::getValue() const { return value; }

template <class T> NodePtr<T> Node<T>::getLeftChild() const { return left; }

template <class T> void Node<T>::setLeftChild(const NodePtr<T> &node) {
    left = node;
}

template <class T> NodePtr<T> Node<T>::getNextSibling() const { return next; }

template <class T> void Node<T>::setNextSibling(const NodePtr<T> &node) {
    next = node;
}

template <class T> void Node<T>::addChild(const NodePtr<T> &node) {
    if (left != nullptr) {
        node->next = left;
    }
    left = node;
}
