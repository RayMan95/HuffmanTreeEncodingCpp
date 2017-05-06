CC=g++

default: classes
	$(CC) -c -o driver.o driver.cpp -std=c++11
	$(CC) -o huffencode driver.o HuffmanNode.o HuffmanTree.o -std=c++11
	$(CC) -g driver.cpp HuffmanNode.cpp HuffmanTree.cpp -std=c++11

debug:
	$(CC) -g driver.cpp HuffmanNode.cpp HuffmanTree.cpp -std=c++11
	gdb --args ./a.out ./data/test.txt ./data/output

test: classes
	$(CC) -c -o test.o test.cpp -std=c++11
	$(CC) -o testAss3 test.o HuffmanNode.o HuffmanTree.o -std=c++11
	./testAss3

classes:
	$(CC) -c -o HuffmanNode.o HuffmanNode.cpp -std=c++11
	$(CC) -c -o HuffmanTree.o HuffmanTree.cpp -std=c++11
	
mem_leak_check: default
	valgrind -v ./huffencode ./data/test.txt ./data/output

clean:
	rm -f *.o
	rm -f huffencode
	rm -f a.out
	rm -f ./data/output
	rm -f ./data/output.hdr
	rm -f testAss3
