#include "binary_tree.h"
#include <iostream>
#include <vector>
#include <ostream>

/*
 * transplant
 * find place to add
 */

template <typename T>
std::vector<T> mikaev_sort(std::vector<T> &v){
    BinaryTree<T> tree;
    for(auto& element : v)
        tree.push(element);

    std::vector<T> sorted_vector;
    tree.in_order_traverse([&sorted_vector](Node<T>* node){
        sorted_vector.push_back(node->data);
    });
    return sorted_vector;
}

int main()
{
    std::vector<int> no_sorted = {1,-5,10,15,-100};
    auto sorted = mikaev_sort(no_sorted);
    std::copy(sorted.begin(), sorted.end(), std::ostream_iterator<int>(std::cout, " "));
    return 0;
}