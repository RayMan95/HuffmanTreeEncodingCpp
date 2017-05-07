CC=g++
STD=-std=c++11

default: classes
	$(CC) -c -o driver.o driver.cpp $(STD)
	$(CC) -o huffencode driver.o HuffmanNode.o HuffmanTree.o $(STD)
	$(CC) -g driver.cpp HuffmanNode.cpp HuffmanTree.cpp $(STD)

debug:
	$(CC) -g driver.cpp HuffmanNode.cpp HuffmanTree.cpp $(STD)
	gdb --args ./a.out ./data/test.txt ./data/output

test:
	$(CC) -c -o test.o test.cpp $(STD)
	$(CC) -o testAss3 test.o HuffmanNode.o HuffmanTree.o $(STD)
	./testAss3 -s -o ./data/catch_output.inf
	@echo Test Passed!
	@echo Full test output sent to file ./data/catch_output.inf

classes:
	$(CC) -c -o HuffmanNode.o HuffmanNode.cpp $(STD)
	$(CC) -c -o HuffmanTree.o HuffmanTree.cpp $(STD)
	
mem_leak_check: default
	valgrind -v ./huffencode ./data/test.txt ./data/output

clean:
	rm -f *.o
	rm -f huffencode
	rm -f a.out
	rm -f ./data/output
	rm -f ./data/output.hdr
	rm -f testAss3
