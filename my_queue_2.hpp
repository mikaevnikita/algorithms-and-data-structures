#include "my_deque.hpp"

template <typename T>
class Queue:private Deque<T>{
public:
    T& front();
    T& back();
    void push(const T& val);
    void pop();
    int size();
    bool empty();
};

template <typename T>
void Queue<T>::push(const T &val) {
    Deque<T>::push_back(val);
}

template <typename T>
void Queue<T>::pop() {
    Deque<T>::pop_front();
}

template <typename T>
T& Queue<T>::front(){
    return Deque<T>::front();
}

template <typename T>
T& Queue<T>::back(){
    return Deque<T>::back();
}

template <typename T>
int Queue<T>::size(){
    return Deque<T>::size();
}

template <typename T>
bool Queue<T>::empty() {
    return Deque<T>::empty();
}