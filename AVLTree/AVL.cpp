//
//  AVLTree.cpp
//
//
//  Created by apple on 19.08.2017.
//
//
#include <algorithm>

struct Node {
    int value;
    Node* leftChild;
    Node* rightChild;
        int getHeight();
    int getBalance();
    Node(int value);
};

class AVLTree {
    Node* root;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* insert(int value, Node* node);
    Node* settleViolation(Node* node);
    Node* remove(int value, Node* node);
    Node* getPredecessor(Node* node);
public:
    AVLTree(): root{nullptr}{}
    void insert(int value);
    void remove(int value);
    
};


Node::Node(int value) {
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->value = value;
}

int Node::getBalance() {
    return this->leftChild->getHeight() - this->rightChild->getHeight();
}

int Node::getHeight() {
    int left_height = this->leftChild !=nullptr ? this->leftChild->getHeight() : -1;
    int right_height = this->rightChild !=nullptr ? this->rightChild->getHeight() : -1;
    
    return std::max(left_height, right_height) + 1;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* temp = node->rightChild;
    
    node->rightChild = temp;
    temp->leftChild = node;
    
    return temp;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* temp = node->leftChild;
    
    node->leftChild = temp->rightChild;
    temp->rightChild = node;
    
    return temp;
}

void AVLTree::insert(int value) {
    this->root = this->insert(value, this->root);
}

Node* AVLTree::insert(int value, Node* node) {
    if(node == nullptr) return new Node(value);
    
    if(value < node->value) {
        node->leftChild = this->insert(value, node->leftChild);
    }else {
        node->rightChild = this->insert(value, node->rightChild);
    }
    
    return this->settleViolation(node);
}

Node* AVLTree::settleViolation(Node* node) {
    int balance = node->getBalance();
    
    if(balance >1 && node->leftChild->getBalance() >0) {
        return this->rotateRight(node);
    }
    if(balance <-1 && node->rightChild->getBalance() < 0) {
        return this->rotateLeft(node);
    }
    if(balance >1 && node->leftChild->getBalance() < 0) {
        node->leftChild = this->rotateLeft(node->leftChild);
        return this->rotateRight(node);
    }
    if(balance <-1 && node->rightChild->getBalance() >0 ) {
        node->rightChild = this->rotateRight(node->rightChild);
        return this->rotateLeft(node);
    }
    
    return node;
}

void AVLTree::remove(int value) {
    if(this->root == nullptr) throw "empty tree";
    
    this->root = this->remove(value, this->root);
}

Node* AVLTree::remove(int value, Node* node) {
    if(node == nullptr) return nullptr;
        
        if(value < node->value) {
            node->leftChild = this->remove(value, node->leftChild);
        }else if(value > node->value) {
            node->rightChild = this->remove(value, node->rightChild);
        }else {
            if(node->leftChild == nullptr && node->rightChild == nullptr) {
                delete node;
                return nullptr;
            }else if(node->leftChild == nullptr) {
                Node* temp = node->rightChild;
                delete node;
                return temp;
            }else if(node->rightChild == nullptr) {
                Node* temp = node->leftChild;
                delete node;
                return temp;
            }else {
                Node* pred = this->getPredecessor(node->leftChild);
                node->value = pred->value;
                pred->value = value;
                return this->remove(value, node->leftChild);
            }
        }
    
    return this->settleViolation(node);
}

Node* AVLTree::getPredecessor(Node* node) {
    if(node->rightChild == nullptr) return node;
    
    return this->getPredecessor(node->rightChild);
}









