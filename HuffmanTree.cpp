// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;


nodePtr root;

HTree::HuffmanTree(){
    root = nullptr;
}

bool HTree::insert(char& cref){
    nodePtr n(new HNode(cref));
    if (root == nullptr){
        root = move(n);
    }
}