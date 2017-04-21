CC=g++

default:
	$(CC) -c -o driver.o driver.cpp -std=c++11
	$(CC) -o huffencode driver.o -std=c++11

debug:
	$(CC) -g driver.cpp -std=c++11
	gdb ./a.out

clean:
	rm -f *.o
	rm huffencode
