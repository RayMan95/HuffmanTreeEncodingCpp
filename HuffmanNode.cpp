// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"

using namespace std;

using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef shared_ptr<FKRRAY001::HuffmanNode> nodeSPtr;

// Move constr
HNode::HuffmanNode(HNode && rhs){
    val = move(rhs.get());
    f = move(rhs.f);
    left = move(rhs.left);
    right = move(rhs.right);
}

// TODO: review these 2
// CopyAss op
HNode& HNode::operator=(HNode & rhs){
    val = rhs.get();
    f = rhs.f;
    left = rhs.left;
    right = rhs.right;
}

// MoveAss op
HNode& HNode::operator=(HNode && rhs){
    val = move(rhs.get());
    f = move(rhs.f);
    left = move(rhs.left);
    right = move(rhs.right);
}

char HNode::get(){
    return this->val;
}

void HNode::setChildren(nodeSPtr l, nodeSPtr r){
    this->left = l;
    this->right = r;
}

