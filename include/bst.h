// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        explicit Node(T value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* addNode(Node* root, T value);
    Node* delNode(Node* root, T value);
    void delTree(Node* root);
    int searchNode(Node* root, T value);
    void printTree(Node* root);
    int getHeight(Node* root);
    void toVector(Node* node, std::vector<std::pair<T, int>>& vec);

 public:
    explicit BST() : root(nullptr) {}
    ~BST();
    void add(T value);
    void del(T value);
    void clear();
    int search(T value);
    void print();
    int depth();
    void toVector(std::vector<std::pair<T, int>>& vec);
};

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
    if (root == nullptr) {
        root = new Node(value);
        return root;
    } else if (value < root->data) {
        root->left = addNode(root->left, value);
    } else if (value > root->data) {
        root->right = addNode(root->right, value);
    } else {
        root->count++;
    }
    return root;
}

template <typename T>
typename BST<T>::Node* BST<T>::delNode(Node* root, T value) {
    Node* p, * v;
    if (root == nullptr) {
        return root;
    } else if (value < root->value) {
        root->left = delNode(root->left, value);
    } else if (value > root->value) {
        root->right = delNode(root->right, value);
    } else {
        p = root;
        if (root->right == nullptr) {
            root = root->left;
        } else if (root->left == nullptr) {
            root = root->right;
        } else {
            v = root->left;
            if (v->right) {
                while (v->right->right)
                    v = v->right;
                root->value = v->right->value;
                root->count = v->right->count;
                p = v->right;
                v->right = v->right->left;
            } else {
                root->value = v->value;
                root->count = v->count;
                p = v;
                root->left = root->left->left;
            }
        }
        delete p;
    }
    return root;
}

template <typename T>
void BST<T>::delTree(Node* root) {
    if (!root) return;
    delTree(root->left);
    delTree(root->right);
    delete root;
}

template <typename T>
int BST<T>::searchNode(Node* root, T value) {
    if (!root) return 0;
    if (value < root->data) {
        return searchNode(root->left, value);
    } else if (value > root->data) {
        return searchNode(root->right, value);
    } else {
        return root->count;
    }
}

template <typename T>
void BST<T>::printTree(Node* root) {
    if (!root) return;
    printTree(root->left);
    for (int i = 0; i < root->count; ++i) {
        std::cout << root->data << " ";
    }
    printTree(root->right);
}

template <typename T>
int BST<T>::getHeight(Node* root) {
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 0;
    int lefth = getHeight(root->left);
    int righth = getHeight(root->right);
    return std::max(lefth, righth) + 1;
}

template <typename T>
BST<T>::~BST() {
    clear();
}

template <typename T>
void BST<T>::add(T value) {
    root = addNode(root, value);
}

template <typename T>
void BST<T>::del(T value) {
    root = delNode(root, value);
}

template <typename T>
void BST<T>::clear() {
    delTree(root);
    root = nullptr;
}

template <typename T>
int BST<T>::search(T value) {
    return searchNode(root, value);
}

template <typename T>
void BST<T>::print() {
    printTree(root);
    std::cout << std::endl;
}

template <typename T>
int BST<T>::depth() {
    return getHeight(root);
}

template <typename T>
void BST<T>::toVector(std::vector<std::pair<T, int>>& vec) {
    toVector(root, vec);
}

template <typename T>
void BST<T>::toVector(Node* node, std::vector<std::pair<T, int>>& vec) {
    if (!node) return;
    toVector(node->left, vec);
    vec.emplace_back(node->data, node->count);
    toVector(node->right, vec);
}

#endif  // INCLUDE_BST_H_
