#include <gsl/gsl>

#include "minqueue.h"

minqueue_node::minqueue_node(char value, unsigned int score) {
    this->value = value;
    this->score = score;

    this->left = nullptr;
    this->right = nullptr;
}

minqueue_node::~minqueue_node() {
    if (this->left != nullptr) delete this->left;
    if (this->right != nullptr) delete this->right;
}

bool cmp_minqueue_nodes::operator()(
    const gsl::not_null<minqueue_node*> left, const gsl::not_null<minqueue_node*> right
) {
    return right->score < left->score;
}
