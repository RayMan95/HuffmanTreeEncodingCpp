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
        char val;
        nodePtr left, right, parent;
    public:
        const int f;
        HuffmanNode(char c, int freq): val(c),f(freq){}
        char get(void);
        int getf(void);
    };
    
    class HuffmanTree{
        typedef std::shared_ptr<HuffmanNode> nodePtr;
        nodePtr root;
    public:
        HuffmanTree(): root(nullptr){}
        HuffmanNode* getRoot(void);
        bool insert(char* cptr, int freq);
        bool compare(const HuffmanNode& a, const HuffmanNode& b);
    };
    
        
}
#endif
