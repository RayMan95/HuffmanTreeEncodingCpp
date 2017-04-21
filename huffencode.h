// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#ifndef HUFFENCODE_H
#define HUFFENCODE_H

#include <string>
#include <memory>

namespace FKRRAY001{
	
    void say(std::string s);
    
    class HuffmanNode{
        typedef std::shared_ptr<HuffmanNode> nodePtr;
        
        nodePtr left, right, parent;
        HuffmanNode(): left(nullptr), right(nullptr), parent(nullptr){}
        HuffmanNode(nodePtr l, nodePtr r, nodePtr p): left(l), right(r), parent(p){}
    };
    
    class HuffmanTree{
        typedef std::shared_ptr<HuffmanNode> nodePtr;
        nodePtr root;
        HuffmanTree():root(nullptr){}
        
        bool insert(nodePtr n);
    };
    
        
}
#endif
