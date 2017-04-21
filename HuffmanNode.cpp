// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"

using namespace std;

using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;

int f;
char val;
nodePtr left, right, parent;

char HNode::get(){
    return this->val;
}