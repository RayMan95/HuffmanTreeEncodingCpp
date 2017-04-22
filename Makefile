CC=g++

default:
	$(CC) -c -o driver.o driver.cpp -std=c++11
	$(CC) -c -o HuffmanNode.o HuffmanNode.cpp -std=c++11
	$(CC) -c -o HuffmanTree.o HuffmanTree.cpp -std=c++11	
	$(CC) -o huffencode driver.o HuffmanNode.o HuffmanTree.o -std=c++11

debug:
	$(CC) -g driver.cpp HuffmanNode.cpp HuffmanTree.cpp -std=c++11
	gdb --args ./a.out test.txt output.txt

clean:
	rm -f *.o
	rm huffencode
