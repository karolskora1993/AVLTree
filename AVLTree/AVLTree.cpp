//
//  AVLTree.cpp
//  AVLTree
//
//  Created by apple on 17.08.2017.
//  Copyright © 2017 apple. All rights reserved.
//

#include "AVLTree.hpp"
#include "Node.hpp"
#include <algorithm>

int AVLTree::getHeight(Node* node) {
    if(node ==  nullptr) return -1;
    
    return node->height;
}

int AVLTree::getBalance(Node* node) {
    if(node == nullptr) return 0;
    
    return this->getHeight(node->leftChild) - this->getHeight(node->rightChild);
}

Node* AVLTree::rotateRight(Node* node) {
    Node* temp = node->leftChild;
    node->leftChild = temp->rightChild;
    temp->rightChild = node;
    node->height = std::max(this->getHeight(node->leftChild), this->getHeight(node->rightChild)) + 1;
    temp->height = std::max(this->getHeight(temp->leftChild), this->getHeight(temp->rightChild)) + 1;
    
    return temp;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* temp = node->rightChild;
    node->rightChild = temp->leftChild;
    temp->leftChild = node;
    node->height = std::max(this->getHeight(node->leftChild), this->getHeight(node->rightChild)) + 1;
    temp->height = std::max(this->getHeight(temp->leftChild), this->getHeight(temp->rightChild)) + 1;
    
    return temp;
}

void AVLTree::insert(int value) {
    if(this->root ==nullptr) {
        this->root = new Node(value);
    }else {
        this->root = this->insert(value, root);
    }
}

Node* AVLTree::insert(int value, Node *node) {
    if(node == nullptr) return new Node(value);
    
    if(value < node->value) {
        node->leftChild = this->insert(value, node->leftChild);
    }else {
        node->rightChild = this->insert(value, node->rightChild);
    }
    
    node->height = std::max(this->getHeight(node->leftChild), this->getHeight(node->rightChild)) + 1;
    return this->settleViolation(value, node);
}

Node* AVLTree::settleViolation(int value, Node *node) {
    
    int balance = this->getBalance(node);
    if(balance > 1 && value < node->value) {
        return this->rotateRight(node);
    }else if(balance <-1 && value > node->value) {
        return this->rotateLeft(node);
    }else if(balance >1 && value > node->value) {
        node->leftChild = this->rotateLeft(node->leftChild);
        return this->rotateRight(node);
    }else {
        node->rightChild = this->rotateRight(node->rightChild);
        return this->rotateLeft(node);
    }
}

