#include "my_deque.hpp"

template <typename T>
class Stack:private Deque<T>{
public:
    T& front();
    T& back();
    void push(const T& val);
    void pop();
    int size();
    bool empty();
};

template <typename T>
void Stack<T>::push(const T &val) {
    Deque<T>::push_front(val);
}

template <typename T>
void Stack<T>::pop() {
    Deque<T>::pop_front();
}

template <typename T>
T& Stack<T>::front(){
    return Deque<T>::front();
}

template <typename T>
T& Stack<T>::back(){
    return Deque<T>::back();
}

template <typename T>
int Stack<T>::size(){
    return Deque<T>::size();
}

template <typename T>
bool Stack<T>::empty() {
    return Deque<T>::empty();
}