//
//  Node.cpp
//  AVLTree
//
//  Created by apple on 17.08.2017.
//  Copyright © 2017 apple. All rights reserved.
//

#include "Node.hpp"

Node::Node(int value) {
    this->height = 0;
    this->value = value;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}
