#include <memory>
#include <stdexcept>

#include "Node.hpp"

template <class T, class Compare = std::less<T>> class PairingHeap {
protected:
    NodePtr<T> root;

    static NodePtr<T> merge(const NodePtr<T> &node1, const NodePtr<T> &node2);
    static NodePtr<T> twoPassMerge(const NodePtr<T> &node);

public:
    bool empty() const { return root == nullptr; }

    T min() const;

    void popMin();

    void insert(T x);

    void clear() { root = nullptr; }

    void absorb(PairingHeap<T, Compare> &rhs) {
        root = merge(root, rhs.root);
        rhs.root = nullptr;
    }
};

template <class T, class Compare>
NodePtr<T> PairingHeap<T, Compare>::merge(const NodePtr<T> &node1,
                                          const NodePtr<T> &node2) {
    if (node1 == nullptr) {
        return node2;
    }

    if (node2 == nullptr) {
        return node1;
    }

    if (Compare()(node1->getValue(), node2->getValue())) {
        node1->addChild(node2);
        return node1;
    } else {
        node2->addChild(node1);
        return node2;
    }

    return nullptr;
}

template <class T, class Compare>
NodePtr<T> PairingHeap<T, Compare>::twoPassMerge(const NodePtr<T> &node) {
    if (node == nullptr || node->getNextSibling() == nullptr) {
        return node;
    }

    auto first = node;
    auto second = node->getNextSibling();
    auto rest = node->getNextSibling()->getNextSibling();

    first->setNextSibling(nullptr);
    second->setNextSibling(nullptr);

    return merge(merge(first, second), twoPassMerge(rest));
}

template <class T, class Compare> T PairingHeap<T, Compare>::min() const {
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return root->getValue();
}

template <class T, class Compare> void PairingHeap<T, Compare>::popMin() {
    root = twoPassMerge(root->getLeftChild());
}

template <class T, class Compare> void PairingHeap<T, Compare>::insert(T x) {
    root = merge(root, std::make_shared<Node<T>>(x));
}
