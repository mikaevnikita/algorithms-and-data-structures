#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "node.h"

#include <iostream>
#include <functional>
#include <queue>
#include <forward_list>


//Избавиться от рекурсии

template <typename DataType>
class BinaryTree
{
    Node<DataType>* root;

public:
    BinaryTree() noexcept;
    BinaryTree(const DataType&);
    BinaryTree(Node<DataType>*) noexcept;//Создание с поддерева
    BinaryTree(const BinaryTree<DataType>&) noexcept;
    ~BinaryTree() noexcept;

    void push(const DataType&);
    void clear() noexcept;
    void remove(const DataType&) noexcept;//Удалить все вхождения элемента
    void cut(const DataType&) noexcept;
    Node<DataType>* search_first(const DataType&);
    std::forward_list< Node<DataType>* > search_all(const DataType&);

    const DataType& min() noexcept;
    const DataType& max() noexcept;

    void add_subtree(const BinaryTree<DataType>&) noexcept;
    BinaryTree<DataType> get_subtree(const DataType&) noexcept;

    void pre_order_traverse(std::function<void (Node<DataType>*)>) noexcept;//Обход в прямом порядке
    void in_order_traverse(std::function<void (Node<DataType>*)>) noexcept;//Обход в симметричном порядке
    void post_order_traverse(std::function<void (Node<DataType>*)>) noexcept;//Обход в обратном порядке
    void breadth_first_traverse(std::function<void (Node<DataType>*)>) noexcept;//Обход в ширину

    int depth() noexcept;

    const BinaryTree<DataType>& operator=(const BinaryTree<DataType>&) noexcept ;

private:
    void free_resources(Node<DataType>*) noexcept;
    void transplant(Node<DataType>*, Node<DataType>*) noexcept;
    Node<DataType>* minimum_node(Node<DataType>*) noexcept;
    Node<DataType>* maximum_node(Node<DataType>*) noexcept;

    Node<DataType>* find_place_to_add(const DataType&) noexcept;

    void _pre_order_traverse(Node<DataType>*, std::function<void (Node<DataType>*)>) noexcept;
    void _in_order_traverse(Node<DataType>*, std::function<void (Node<DataType>*)>) noexcept;
    void _post_order_traverse(Node<DataType>*, std::function<void (Node<DataType>*)>) noexcept;

    int _depth(Node<DataType>*) noexcept;
public:
    Node<DataType>* big_right_rotate(Node<DataType>* node);
    Node<DataType>* big_left_rotate(Node<DataType>* node);
    Node<DataType>* small_right_rotate(Node<DataType>* node);
    Node<DataType>* small_left_rotate(Node<DataType>* node);
};


template <typename DataType>
Node<DataType>* BinaryTree<DataType>::big_right_rotate(Node<DataType> *node) {
    Node<DataType>* b = node->left;
    Node<DataType>* c = nullptr;
    if(b){
        c = b->right;
        small_left_rotate(b);
        small_right_rotate(node);
    }
    return c;
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::big_left_rotate(Node<DataType> *node) {
    Node<DataType>* b = node->right;
    Node<DataType>* c = nullptr;
    if(b){
        c = b->left;
        small_right_rotate(b);
        small_left_rotate(node);
    }
    return c;
}


template <typename DataType>
Node<DataType>* BinaryTree<DataType>::small_right_rotate(Node<DataType> *node){
    if(!node)
        return nullptr;

    Node<DataType>* b = node->left;

    if(b) {
        Node<DataType>* c = b->right;
        node->left = c;

        if(node->parent){
            if(node->parent->left == node)
                node->parent->left = b;
            if(node->parent->right == node)
                node->parent->right = b;
        }
        b->parent = node->parent;
        node->parent = b;

        if(c)
            c->parent = node;

        b->right = node;
    }

    return b;
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::small_left_rotate(Node<DataType> *node){
    if(!node)
        return nullptr;

    Node<DataType>* b = node->right;

    if(b) {
        Node<DataType>* c = b->left;
        node->right = c;

        if(node->parent){
            if(node->parent->left == node)
                node->parent->left = b;
            if(node->parent->right == node)
                node->parent->right = b;
        }

        b->parent = node->parent;
        node->parent = b;

        if(c)
            c->parent = node;

        b->left = node;
    }

    return b;
}

template <typename DataType>
BinaryTree<DataType>::BinaryTree() noexcept
{
    root = nullptr;
}

template <typename DataType>
BinaryTree<DataType>::BinaryTree(const DataType& data)
{
    root = new Node<DataType>;

    root->data = data;

    root->right = nullptr;
    root->left = nullptr;

    root->parent = nullptr;
}

template <typename DataType>
BinaryTree<DataType>::BinaryTree(Node<DataType>* new_root) noexcept
{
    root = nullptr;

    auto func = [this] (Node<DataType>* node)
    {
        push(node->data);
    };

    _pre_order_traverse(new_root, func);
}

template <typename DataType>
BinaryTree<DataType>::BinaryTree(const BinaryTree<DataType>& other) noexcept
{
    root = nullptr;

    auto func = [this] (Node<DataType>* node)
    {
        push(node->data);
    };

    _pre_order_traverse(other.root, func);
}

template <typename DataType>
BinaryTree<DataType>::~BinaryTree() noexcept
{
    free_resources(root);
}

template <typename DataType>
void BinaryTree<DataType>::push(const DataType& data)
{
    Node<DataType>* node = new Node<DataType>;

    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    Node<DataType>* temp = nullptr;
    Node<DataType>* y = root;

    while(y != nullptr)
    {
        temp = y;

        if(data < y->data)
        {
            y = y->left;
        }
        else
        {
            y = y->right;
        }
    }

    node->parent = temp;

    if(temp == nullptr)
    {
        root = node;
    }
    else
    {
        if(data < temp->data)
        {
            temp->left = node;
        }
        else
        {
            temp->right = node;
        }
    }
}

template <typename  DataType>
void BinaryTree<DataType>::clear() noexcept
{
    free_resources(root);

    root = nullptr;
}

template <typename DataType>
void BinaryTree<DataType>::remove(const DataType& data) noexcept
{
    std::forward_list< Node<DataType>* > nodes = search_all(data);

    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        free_resources(*it);
    }
}

template <typename DataType>
void BinaryTree<DataType>::cut(const DataType& data) noexcept
{
    std::forward_list< Node<DataType>* > nodes = search_all(data);

    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        Node<DataType>* node = *it;

        if (node->left == nullptr)
        {
            transplant(node, node->right);
        }
        else if (node->right == nullptr)
        {
            transplant(node, node->left);
        }
        else
        {
            Node<DataType> *temp = minimum_node(node->right);
            if (temp->parent != node)
            {
                transplant(temp, temp->right);
                temp->right = node->right;
                temp->right->parent = temp;
            }
            transplant(node, temp);
            temp->left = node->left;
            temp->left->parent = temp;
        }

        node = nullptr;
    }
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::search_first(const DataType& data)
{
    Node<DataType>* node = root;

    while(node != nullptr)
    {
        if(data == node->data)
        {
            return node;
        }
        else if(data < node->data)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
}

template <typename DataType>
std::forward_list< Node<DataType>* > BinaryTree<DataType>::search_all(const DataType& data)
{
    std::forward_list< Node<DataType>* > nodes;

    auto _search_all = [&nodes, data] (Node<DataType>* node)
    {
        if(node->data == data) nodes.push_front(node);
    };

    _pre_order_traverse(root, _search_all);

    return nodes;
}

template <typename DataType>
const DataType& BinaryTree<DataType>::min() noexcept
{
    return minimum_node(root)->data;
}

template <typename DataType>
const DataType& BinaryTree<DataType>::max() noexcept
{
    return maximum_node(root)->data;
}

template <typename DataType>
void BinaryTree<DataType>::add_subtree(const BinaryTree<DataType>& subtree) noexcept
{
    Node<DataType>* temp = find_place_to_add(subtree.root->data);

    BinaryTree<DataType>* temp_tree = new BinaryTree<DataType>;
    *temp_tree = subtree;

    if(temp_tree->root->data < temp->data)
    {
        temp->left = temp_tree->root;
        temp_tree->root->parent = temp->left;
    }
    else
    {
        temp->right = temp_tree->root;
        temp_tree->root->parent = temp->right;
    }
}

template <typename DataType>
BinaryTree<DataType> BinaryTree<DataType>::get_subtree(const DataType& data) noexcept
{
    Node<DataType>* node = search_first(data);

    return BinaryTree<DataType>(node);
}

template <typename DataType>
void BinaryTree<DataType>::pre_order_traverse(std::function<void(Node<DataType> *)> function) noexcept
{
    _pre_order_traverse(root, function);
}

template <typename DataType>
void BinaryTree<DataType>::in_order_traverse(std::function<void(Node<DataType>*)> function) noexcept
{
    _in_order_traverse(root, function);
}

template <typename DataType>
void BinaryTree<DataType>::post_order_traverse(std::function<void(Node<DataType> *)> function) noexcept
{
    _post_order_traverse(root, function);
}

template <typename DataType>
void BinaryTree<DataType>::breadth_first_traverse(std::function<void(Node<DataType> *)> function) noexcept
{
    std::queue<Node<DataType>*> queue;
    queue.push(root);

    while(!queue.empty())
    {
        Node<DataType>* temp = queue.front();
        queue.pop();

        if(temp->left != nullptr)
            queue.push(temp->left);
        if(temp->right != nullptr)
            queue.push(temp->right);

        function(temp);
    }
}

template <typename DataType>
int BinaryTree<DataType>::depth() noexcept
{
    return _depth(root);
}

template <typename DataType>
const BinaryTree<DataType>& BinaryTree<DataType>::operator=(const BinaryTree<DataType>& other) noexcept
{
    if(root != nullptr)
    {
        free_resources(root);
    }

    auto func = [this](Node<DataType>* node)
    {
        push(node->data);
    };

    _pre_order_traverse(other.root, func);

    return *this;
}



template <typename DataType>
void BinaryTree<DataType>::free_resources(Node<DataType>* node) noexcept
{
    auto func = [] (Node<DataType>* node)
    {
        if(node == nullptr)
            return;

        if(node->parent != nullptr)
        {
            if (node->data < node->parent->data)
            {
                node->parent->left = nullptr;
            }
            else
            {
                node->parent->right = nullptr;
            }
        }

        delete node;
        node = nullptr;
    };

    _post_order_traverse(node,func);
}

template<typename DataType>
void BinaryTree<DataType>::transplant(Node<DataType>* u, Node<DataType>* v) noexcept
{
    if(u->parent == nullptr)
    {
        root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    if(v != nullptr)
    {
        v->parent = u->parent;
    }
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::minimum_node(Node<DataType>* node) noexcept
{
    Node<DataType>* temp = node;

    while(temp->left != nullptr)
    {
        temp = temp->left;
    }

    return temp;
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::maximum_node(Node<DataType>* node) noexcept
{
    Node<DataType>* temp = node;

    while(temp->right != nullptr)
    {
        temp = temp->right;
    }

    return temp;
}

template <typename DataType>
Node<DataType>* BinaryTree<DataType>::find_place_to_add(const DataType& data) noexcept
{
    Node<DataType>* node = root;

    while(node->left != nullptr or node->right != nullptr)
    {
        if(node->left != nullptr and data < node->data)
            node = node->left;
        else if(node->right != nullptr)
            node = node->right;
        else
            break;
    }

    return node;
}

template <typename DataType>
void BinaryTree<DataType>::_pre_order_traverse(Node<DataType>* node, std::function<void (Node<DataType>*)> function) noexcept
{
    //Обход в прямом порядке
    function(node);

    if(node->left != nullptr)
        _pre_order_traverse(node->left, function);

    if(node->right != nullptr)
        _pre_order_traverse(node->right, function);
}

template <typename DataType>
void BinaryTree<DataType>::_in_order_traverse(Node<DataType>* node, std::function<void (Node<DataType>*)> function) noexcept
{
    if(node->left != nullptr)
        _in_order_traverse(node->left, function);

    function(node);

    if(node->right != nullptr)
        _in_order_traverse(node->right, function);
}

template <typename DataType>
void BinaryTree<DataType>::_post_order_traverse(Node<DataType>* node, std::function<void (Node<DataType>*)> function) noexcept
{
    if(node->left != nullptr)
        _post_order_traverse(node->left, function);

    if(node->right != nullptr)
        _post_order_traverse(node->right, function);

    function(node);
}

/*template <typename DataType>
int BinaryTree<DataType>::_depth(Node<DataType>* node) noexcept
{
    if(node == nullptr) return 0;

    int left = 0;
    int right = 0;

    if(node->left != nullptr)
        left = _depth(node->left);
    else left = -1;

    if(node->right != nullptr)
        right = _depth(node->right);
    else right = -1;

    int max = left > right ? left : right;

    return max+1;
}*/

template <typename DataType>
int BinaryTree<DataType>::_depth(Node<DataType>* node) noexcept {
    int k = 0;
    auto func = [&k](Node<DataType>* node){
        if(node != nullptr)
            k+=1;
    };
    pre_order_traverse(func);
    return k+1;
}


#endif //BINARY_TREE_H
