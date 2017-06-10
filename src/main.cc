#include <iostream>

#include "heap.h"

using namespace std;

int main(int argc, char *argv[]) {
    Heap *heap = new Heap();

    heap->push(new Node(10, 'a'));
    heap->push(new Node(20, 'b'));
    heap->push(new Node(30, 'c'));

    while (!heap->empty()) {
        Node *node = heap->pop();
        std::cout << node->value << " ";
        delete node;
    }
    std::cout << "\n";

    delete heap;

    return EXIT_SUCCESS;
}
