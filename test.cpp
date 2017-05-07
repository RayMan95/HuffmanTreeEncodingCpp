#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "huffencode.h"
#include <iostream>

using namespace std;

TEST_CASE("test.txt"){
    
    
    SECTION("1)Encoding"){
        FKRRAY001::HuffmanTree * ht = new FKRRAY001::HuffmanTree();
        
        REQUIRE(ht->buildTree("./data/test.txt") == 6);        
        REQUIRE(ht->buildTree("not_an_existing_file.txt") == -1);
        
        char special[] = "~";
        REQUIRE(ht->getRoot()->get() == special[0]); // special parent character
        
        char vals[] = "abcdef";
        REQUIRE(ht->getRoot()->left->get() == vals[5]); // correct highest frequency char
        REQUIRE(ht->getRoot()->left->f == 45); // correct frequency
        
        // Not entirely sure how to show the tree is built as expected, but 
        // I'll essentially go to certain nodes to show they are where 
        // I expect them to be
        
        REQUIRE(ht->getRoot()->right->right->right->get() == vals[4]); // e
        REQUIRE(ht->getRoot()->right->right->left->left->get() == vals[0]); // a
        REQUIRE(ht->getRoot()->right->left->right->get() == vals[3]); // d
        REQUIRE(ht->getRoot()->right->left->get() == special[0]); // parent node
        
        REQUIRE(ht->encode("./data/test.txt", "./data/test_out")); // completes encode
        
        unordered_map<char, int> eCF;
        eCF[vals[0]] = 5;
        eCF[vals[1]] = 9;
        eCF[vals[2]] = 12;
        eCF[vals[3]] = 13;
        eCF[vals[4]] = 16;
        eCF[vals[5]] = 45;
        
        unordered_map<char, int> iCF = *ht->getFreqMap();
        
        bool allMatch = true;
        for (auto a : iCF){ // chars in iCF
            int x = eCF[a.first]; // value of chars in eCF
            if (x != a.second){
                allMatch = false;
                break;
            }
        }
        REQUIRE(allMatch); // all frequencies match characters
        REQUIRE_FALSE(iCF[vals[5]] == 44);
        
        unordered_map<char, string> eCT;
        eCT[vals[0]] = "1100";
        eCT[vals[1]] = "1101";
        eCT[vals[2]] = "100";
        eCT[vals[3]] = "101";
        eCT[vals[4]] = "111";
        eCT[vals[5]] = "0";
        
        unordered_map<char, string> iCT = *ht->getCodeTable();
        
        allMatch = true;
        for (auto a : iCT){ // chars in iCT
            string x = eCT[a.first]; // value of chars in eCT
            if (x != a.second){
                allMatch = false;
                break;
            }
        }
        REQUIRE(allMatch); // all encoded characters match
        REQUIRE_FALSE(iCT[vals[5]] == "1");
        
        
        ifstream ifile("./data/test_out.hdr");
        REQUIRE(ifile.is_open()); // creates output hdr file
        
        string line;
        while (getline(ifile, line)){
            if (line.length() == 1) // first line of file is num of unique chars
                REQUIRE(line == "6");
            else{
                // code table in file matches code table map
                REQUIRE(iCT[line[0]] == eCT[line[0]]);
            }
        }
        ifile.close();
        
        delete ht;
    }
    
    SECTION("2)Special members"){
        SECTION("  a)HuffmanTree"){
            FKRRAY001::HuffmanTree * HT = new FKRRAY001::HuffmanTree();
            HT->buildTree("./data/test.txt");
            HT->encode("./data/test.txt", "./data/test_output");
            
            SECTION("    a)Copy constructor"){
                FKRRAY001::HuffmanTree htTest(*HT);

                unordered_map<char, int> iCF = *htTest.getFreqMap();
                unordered_map<char, int> eCF = *HT->getFreqMap();

                bool allMatch = true;
                for (auto a : iCF){ // chars in iCF
                    int x = eCF[a.first]; // value of chars in eCF
                    if (x != a.second){
                        allMatch = false;
                        break;
                    }
                }
                REQUIRE(allMatch); // all frequencies match characters

                unordered_map<char, string> eCT = *HT->getCodeTable();
                unordered_map<char, string> iCT = *htTest.getCodeTable();
                for (auto a : iCF){ // chars in iCF
                    int x = eCF[a.first]; // value of chars in eCF
                    if (x != a.second){
                        allMatch = false;
                        break;
                    }
                }
                REQUIRE(allMatch); // all encoded characters match
                REQUIRE(HT->getUniqueChars() == htTest.getUniqueChars());
                
            }
            
            SECTION("    b)Copy assignment operator"){
                FKRRAY001::HuffmanTree htTest = *HT;
                
                unordered_map<char, int> iCF = *htTest.getFreqMap();
                unordered_map<char, int> eCF = *HT->getFreqMap();

                bool allMatch = true;
                for (auto a : iCF){ // chars in iCF
                    int x = eCF[a.first]; // value of chars in eCF
                    if (x != a.second){
                        allMatch = false;
                        break;
                    }
                }
                REQUIRE(allMatch); // all frequencies match characters

                unordered_map<char, string> eCT = *HT->getCodeTable();
                unordered_map<char, string> iCT = *htTest.getCodeTable();
                for (auto a : iCF){ // chars in iCF
                    int x = eCF[a.first]; // value of chars in eCF
                    if (x != a.second){
                        allMatch = false;
                        break;
                    }
                }
                REQUIRE(allMatch); // all encoded characters match
                REQUIRE(HT->getUniqueChars() == htTest.getUniqueChars());
            }
            
            delete HT;
            
        }
        
        SECTION("  b)HuffmanNode"){
            
        }
    }
    
}

#endif
