//
//  AVLTree.hpp
//  AVLTree
//
//  Created by apple on 17.08.2017.
//  Copyright © 2017 apple. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp


class Node;

class AVLTree {
    Node* root;
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* insert(int value, Node* node);
    Node* settleViolation(int value, Node* node);
    
public:
    AVLTree(): root{nullptr} {}
    void insert(int value);
    
};

#endif /* AVLTree_hpp */
