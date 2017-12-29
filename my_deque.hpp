#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include <exception>
#include <iostream>

template <typename T>
class Deque {
private:
    struct Node
    {
        Node (const T& el) : data (el)
        {}
        Node* previous;
        Node* next;
        T data;
    };

    Node* head;
    Node* tail;
    int _size;

public:
    Deque () : head(nullptr), tail(nullptr), _size(0){}
    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    T& front();
    T& back();
    int size();
    bool empty();
};

template <typename T>
void Deque<T>::push_back(const T &val) {
    try{
        if(tail!=nullptr){
            Node* new_tail = new Node(val);
            new_tail->previous=tail;
            new_tail->next=nullptr;
            tail->next=new_tail;
            tail=new_tail;
        }
        else{
            head=tail=new Node(val);
            head->previous=nullptr;
            head->next=nullptr;
        }
        ++_size;
    }
    catch(std::bad_alloc& error){
        std::cerr << error.what() << std::endl;
    }
}

template <typename T>
void Deque<T>::push_front(const T &val) {
    try{
        if(head!=nullptr){
            Node* new_head=new Node(val);
            new_head->next=head;
            new_head->previous=nullptr;
            head->previous=new_head;
            head=new_head;
        }
        else{
            head=tail=new Node(val);
            head->previous=nullptr;
            head->next=nullptr;
        }
        ++_size;
    }
    catch(std::bad_alloc& error){
        std::cerr << error.what() << std::endl;
    }
}

template <typename T>
void Deque<T>::pop_back() {
    if(empty())
        return;
    Node* temp = tail;
    tail = tail->previous;
    delete temp;
    _size--;

    if(tail)
        tail->next=nullptr;
    else
        head=nullptr;
}

template <typename T>
void Deque<T>::pop_front() {
    if(empty())
        return;
    Node* temp = head;
    head = head->next;
    delete temp;
    _size--;

    if (head)
        head->previous = nullptr;

    else
        tail = nullptr;
}

template <typename T>
T& Deque<T>::front(){
    try
    {
        if (head == nullptr)
            throw std::out_of_range("Error: Deque is empty!");

        return head->data;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
T& Deque<T>::back() {
    try{
        if(tail == nullptr)
            throw std::out_of_range("Error: Deque is empty!");

        return tail->data;
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
int Deque<T>::size(){
    return _size;
}

template <typename T>
bool Deque<T>::empty(){
    return _size==0;
}


#endif
