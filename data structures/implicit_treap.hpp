#include <iostream>
#include <exception>
using namespace std;

/*
Декартово дерево с неявным ключом и контейнер адаптер к нему - вектор
Все операции за O(lgN)
*/

template <typename T>
class ImplicitTreap{
private:
    class Node {
    public:
        int y;   //приоритет вершины
        int size;  //размер поддерева
        T value; //значение в узле
        Node* left_node;
        Node* right_node;
    };

    Node* newNode(T value)
    {
        Node* node = new Node;
        node->y = rand();//рандомизированный приоритет
        node->size = 1;
        node->value = value;
        node->left_node = node->right_node = nullptr;
        return node;
    }

    int getSize(Node* node) const
    {
        if (node == nullptr)
            return 0;
        return node->size;
    }

    void updateSize(Node* node)
    {
        if (node == nullptr)
            return;
        node->size = 1 + getSize(node->left_node) + getSize(node->right_node);
    }

    Node* merge(Node* t1, Node *t2)
    {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;
        if (t1->y > t2->y)
        {
            t1->right_node = merge(t1->right_node, t2);
            updateSize(t1);
            return t1;
        }
        else
        {
            t2->left_node = merge(t1, t2->left_node);
            updateSize(t2);
            return t2;
        }
    }

    void split(Node* t, int x, Node* &t1, Node* &t2)
    {
        if (t == nullptr)
        {
            t1 = t2 = nullptr;
            return;
        }
        if (getSize(t->left_node) < x)
        {
            split(t->right_node, x - getSize(t->left_node) - 1, t->right_node, t2);
            t1 = t;
        }
        else
        {
            split(t->left_node, x, t1, t->left_node);
            t2 = t;
        }
        updateSize(t);
    }

    void print_tree(Node *t)
    {
        if (t == nullptr) { return; }
        print_tree(t->left_node);
        cout << t->value << " ";
        print_tree(t->right_node);
    }

    Node* root;

public:
    ImplicitTreap()
        :root(nullptr)
    {
    }

    ImplicitTreap(const std::initializer_list<T>& il)
        :root(nullptr)
    {
        for (auto it = il.begin(); it != il.end(); ++it)
            root = merge(root, newNode(*it));
    }

    int getSize() const{
        return getSize(root);
    }

    void add(int pos, T val)
    {
        Node* t1;
        Node* t2;
        split(root, pos, t1, t2);
        Node* new_tree = newNode(val);
        root = merge(merge(t1, new_tree), t2);
    }

    void add(const std::initializer_list<T>& il)
    {
        for(auto it = il.begin(); it != il.end(); it++){
            root = merge(root, newNode(*it));
        }
    }

    void remove(int pos)
    {
        if(pos < 0)
            return;
        Node* t1;
        Node* t2;
        Node* t3;
        Node* t4;
        split(root, pos, t1, t2);
        split(t2, 1, t3, t4);
        root = merge(t1, t4);
        delete t3;
    }


    T& get(int pos) const
    {
        Node* t = root;
        for(;;){
            if(t == nullptr)
                throw std::invalid_argument("Unknown position");
            int index = getSize(t->left_node);
            if (pos < index)
            {
                t = t->left_node;
                continue;
            }
            else if (pos == index)
                break;
            else
            {
                t = t->right_node;
                pos = pos - index - 1;
            }
        }
        return t->value;
    }

    void print_tree(){
        print_tree(root);
    }

};

template<typename T>
class Vector{
    //ImplicitTreap Adapter
private:
    ImplicitTreap<T> implicit_treap;
    int size;
public:
    Vector()
        :size(0)
    {

    }

    Vector(const std::initializer_list<T>& il)
        :size(il.size())
    {
        implicit_treap.add(il);
    }

    void push_back(const T& value){
        implicit_treap.add(size++, value);
    }

    void insert(int index, const T& value){
        implicit_treap.add(index, value);
        size++;
    }

    void remove(int index){
        implicit_treap.remove(index);
        size = implicit_treap.getSize();//пересчет размера
    }

    void set(int index, const T& value){
        T& ref_value = implicit_treap.get(index);
        ref_value = value;
    }

    T at(int index){
        return implicit_treap.get(index);
    }

    int getSize() const{
        return size;
    }

    void print(){
        implicit_treap.print_tree();
    }
};

int main()
{
    Vector<int> v { {1,2,3} };
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    cout << v.print() << endl;
    return 0;
}
