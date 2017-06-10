CC = clang++
CFLAGS = -std=c++14 -Wall -Werror
DEBUG_CFLAGS = $(CFLAGS) -g
SRC_DIR = src

all: build

build:
	$(CC) $(CFLAGS) $(SRC_DIR)/*.cc -o huffman

debug:
	$(CC) $(DEBUG_CFLAGS) $(SRC_DIR)/*.cc -o huffman

leakcheck: debug
	valgrind --log-file=valgrind.log --leak-check=full ./huffman

.PHONY: clean
clean:
	rm -f a.out
	rm -f huffman
	rm -rf *.dSYM
