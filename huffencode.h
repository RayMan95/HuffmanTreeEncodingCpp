// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#ifndef HUFFENCODE_H
#define HUFFENCODE_H

#include <string>
#include <memory>
#include <unordered_map>
#include <queue>
#include <vector>

namespace FKRRAY001{
	
    void say(std::string s);
    
    class HuffmanNode{
        typedef std::shared_ptr<HuffmanNode> nodePtr;
        char val;
        nodePtr parent;
    public:
        struct compare{
            // TODO: check '>' or '<'
            bool operator()(const std::shared_ptr<HuffmanNode> a, const std::shared_ptr<HuffmanNode> b) const{return a->f > b->f;}
        };
        nodePtr left, right;
        unsigned f;
        HuffmanNode(char c, unsigned freq): val(c),f(freq){}
        char get(void);
        int getf(void);
        void setChildren(nodePtr l, nodePtr r);
        void setParent(nodePtr p);
        
    };
    
    class HuffmanTree{
        typedef std::shared_ptr<HuffmanNode> nodePtr;
        nodePtr root;
        int uniqueChars;
        std::unordered_map<char, int> charFreqs;
        std::unordered_map<char, std::string> codeTable;

    public:
        HuffmanTree(): root(nullptr){}
        bool insert(char* cptr, int freq);
        void buildTree(std::string fileInName);
        nodePtr getRoot(void);
        void buildCodes(nodePtr root, std::string str, const char head);
    };
    
        
}
#endif
