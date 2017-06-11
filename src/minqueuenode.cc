#include "minqueue.h"

using namespace std;

MinQueueNode::MinQueueNode(char value, unsigned int score) {
    this->value = value;
    this->score = score;

    this->left = nullptr;
    this->right = nullptr;
}

MinQueueNode::~MinQueueNode() {
    if (this->left != nullptr) delete this->left;
    if (this->right != nullptr) delete this->right;
}

bool CompareMinQueueNodes::operator()(const MinQueueNode *left, const MinQueueNode *right) {
    return right->score < left->score;
}
