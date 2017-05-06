#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "huffencode.h"

TEST_CASE("First test file: test.txt"){
    FKRRAY001::HuffmanTree * ht = new FKRRAY001::HuffmanTree();
    
    SECTION("buildTree"){
        REQUIRE(ht->buildTree("./data/test.txt") == 6);
    }
    
    SECTION("Highest frequency char"){
        char c[] = "f";
        int f = 45;
//        REQUIRE(ht->getRoot()->left->get() == c[0]);
//        REQUIRE(ht->getRoot()->left->f == f);
    }
    
    
    delete ht;
}

#endif
