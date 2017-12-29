#ifndef TREE_NODE_H
#define TREE_NODE_H

template <typename DataType>
struct Node
{
    DataType data;

    Node* right;
    Node* left;

    Node* parent;
};

#endif //TREE_NODE_H
