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
        typedef std::shared_ptr<HuffmanNode> nodeSPtr;
        
        char val;
    public:
        struct compare{
            // TODO: check '>' or '<'
            bool operator()(const std::shared_ptr<HuffmanNode> a, const std::shared_ptr<HuffmanNode> b) const{return a->f > b->f;}
        };
        nodeSPtr left, right;
        unsigned f;
        HuffmanNode(char c, unsigned freq): val(c),f(freq){}
        ~HuffmanNode() = default;
        // Copy constr
	HuffmanNode(HuffmanNode & rhs): val(rhs.get()), f(rhs.f), left(rhs.left), right(rhs.right){};
	// Move constr
        HuffmanNode(HuffmanNode && rhs);
	// CopyAss op
        HuffmanNode& operator=(HuffmanNode & rhs);
        // MoveAss op
        HuffmanNode& operator=(HuffmanNode && rhs);
        char get(void);
        void setChildren(nodeSPtr l, nodeSPtr r);
        
    };
    
    class HuffmanTree{
        typedef std::shared_ptr<HuffmanNode> nodeSPtr;
        
        
        int uniqueChars;
        std::unordered_map<char, int> charFreqs;
        std::unordered_map<char, std::string> codeTable;
        // is a min-queue
        std::priority_queue<nodeSPtr, std::vector<nodeSPtr>, HuffmanNode::compare> myQueue;
        void buildCodes(nodeSPtr root, std::string str, const char head);

    public:
        nodeSPtr root;
        
        HuffmanTree(): root(nullptr){}
        ~HuffmanTree();
        // Copy constr
	HuffmanTree(HuffmanTree & rhs): root(rhs.root), uniqueChars(rhs.getUniqueChars()), 
            codeTable(*rhs.getCodeTable()), charFreqs(*rhs.getFreqtable()), myQueue(*rhs.getPQueue()){};
	// Move constr
        HuffmanTree(HuffmanTree && rhs);
	// CopyAss op
        HuffmanTree& operator=(HuffmanTree & rhs);
        // MoveAss op
        HuffmanTree& operator=(HuffmanTree && rhs);
        
        int buildTree(std::string fileInName);
        nodeSPtr getRoot(void);
        int getUniqueChars();
        std::unordered_map<char, std::string>* getCodeTable();
        std::unordered_map<char, int>* getFreqtable();
        std::priority_queue<nodeSPtr, std::vector<nodeSPtr>, HuffmanNode::compare>* getPQueue();
        bool encode(std::string fileInName, std::string fileOutName);
    };
    
        
}
#endif
