// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"

using namespace std;

using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef shared_ptr<FKRRAY001::HuffmanNode> nodePtr;

char HNode::get(){
    return this->val;
}

void HNode::setChildren(nodePtr l, nodePtr r){
    this->left = l;
    this->right = r;
}

void HNode::setParent(nodePtr p){
    this->parent = p;
}
