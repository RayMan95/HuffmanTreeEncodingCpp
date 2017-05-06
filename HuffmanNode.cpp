// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"

using namespace std;

using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef shared_ptr<FKRRAY001::HuffmanNode> nodeSPtr;


char HNode::get(){
    return this->val;
}

void HNode::setChildren(nodeSPtr l, nodeSPtr r){
    this->left = l;
    this->right = r;
}

