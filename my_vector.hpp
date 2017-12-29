#ifndef MY_VECTOR
#define MY_VECTOR

#include <iostream>
#include <stdexcept>
#include <new>
using namespace std;


template <typename T>
class Vector{
private:
    const int step_for_reallocation=2;
    T *arr;

    int size;
    int capacity;

    void reallocation(const int& new_capacity);
public:
    Vector(T *const ptr_from_copy,const int& size_of_copy);
    Vector(const int& new_capacity=0);
    Vector(const Vector<T>& source_for_copy);
    ~Vector();

    int Size()const;
    int Capacity()const;
    bool Empty()const;

    Vector<T>& operator=(const Vector<T>& from);

    T& operator[](const int& index) const;
    T& at(const int& index) const;

    void push_back(const T& obj);
    void pop_back();

    class Iterator{
    private:
        T* ptr;
    public:
        Iterator(T *const ptr_);
        Iterator(const Iterator& iter);
        T& operator*() const;
        Iterator& operator++();
        Iterator& operator--();
        Iterator& operator=(const Iterator& iter);
        bool operator==(const Iterator& iter) const;
        bool operator!=(const Iterator& iter) const;
        bool operator>(const Iterator& iter) const;
        bool operator<(const Iterator& iter) const;
        bool operator>=(const Iterator& iter) const;
        bool operator<=(const Iterator& iter) const;
    };

    class ConstIterator{
    private:
        const T* ptr;
    public:
        ConstIterator(const T *const ptr_);
        ConstIterator(const ConstIterator& c_iter);
        const T& operator*() const;
        ConstIterator& operator++();
        ConstIterator& operator--();
        ConstIterator& operator=(const ConstIterator& iter);
        bool operator==(const ConstIterator& iter) const;
        bool operator!=(const ConstIterator& iter) const;
        bool operator>(const ConstIterator& iter) const;
        bool operator<(const ConstIterator& iter) const;
        bool operator>=(const ConstIterator& iter) const;
        bool operator<=(const ConstIterator& iter) const;
    };
    Iterator begin() const;
    Iterator end() const;
    ConstIterator c_begin() const;
    ConstIterator c_end() const;
};

template <typename T>
bool Vector<T>::ConstIterator::operator<=(const ConstIterator& iter) const{
    return ptr<=iter.ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator>=(const ConstIterator& iter) const{
    return ptr>=iter.ptr;
}


template <typename T>
bool Vector<T>::ConstIterator::operator<(const ConstIterator& iter) const{
    return ptr<iter.ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator>(const ConstIterator& iter) const{
    return ptr>iter.ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator!=(const ConstIterator& iter) const{
    return ptr!=iter.ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator==(const ConstIterator& iter) const{
    return ptr==iter.ptr;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator=(const ConstIterator& iter){
    ptr=iter.ptr;
    return *this;
}


template <typename T>
bool Vector<T>::Iterator::operator<=(const Iterator& iter) const{
    return ptr<=iter.ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator>=(const Iterator& iter) const{
    return ptr>=iter.ptr;
}


template <typename T>
bool Vector<T>::Iterator::operator<(const Iterator& iter) const{
    return ptr<iter.ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator>(const Iterator& iter) const{
    return ptr>iter.ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& iter) const{
    return ptr!=iter.ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& iter) const{
    return ptr==iter.ptr;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& iter){
    ptr=iter.ptr;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const{
    return Iterator(arr);
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::c_begin() const{
    return ConstIterator(arr);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const{
    if(Empty())
        return begin();
    return Iterator(arr+size+(Empty() ? -1 : 0));
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::c_end() const{
    if(Empty())
        return c_begin();
    return ConstIterator(arr+size+(Empty() ? -1 : 0));
}

template <typename T>
Vector<T>::Iterator::Iterator(T *const ptr_) {
    ptr=ptr_;
}

template <typename T>
Vector<T>::ConstIterator::ConstIterator(const T *const ptr_){
    ptr=ptr_;
}

template <typename T>
Vector<T>::Iterator::Iterator(const Iterator& iter) {
    ptr=iter.ptr;
}

template <typename T>
Vector<T>::ConstIterator::ConstIterator(const ConstIterator &c_iter) {
    ptr=c_iter.ptr;
}

template <typename T>
T& Vector<T>::Iterator::operator*() const{
    return *ptr;
}

template <typename T>
const T& Vector<T>::ConstIterator::operator*() const{
    return *ptr;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
    ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++() {
    ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
    ptr--;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--() {
    ptr--;
    return *this;
}


template <typename T>
Vector<T>::Vector(T *const ptr_from_copy, const int &size_of_copy) {
    if(size_of_copy<0){
        throw std::invalid_argument("Size argument should be >0");
    }
    arr=nullptr;
    size=0;
    capacity=0;
    reallocation(size_of_copy);
    size=size_of_copy;
    for(int i=0;i<size;i++)
        arr[i]=ptr_from_copy[i];
}

template <typename T>
void Vector<T>::reallocation(const int& new_capacity) {
    if(new_capacity==capacity)
        return;
    if(arr==nullptr){
        try {
            arr=new T[new_capacity];
        }
        catch(std::bad_alloc& e){
            std::cerr << e.what() << endl;
            throw e;
        }
    }
    else {
        T *temp_ptr;
        try {
            temp_ptr = new T[new_capacity];
        }
        catch (std::bad_alloc &e) {
            std::cerr << e.what() << endl;
            throw e;
        }
        if(size > new_capacity){
            size=new_capacity;
        }
        for (int i = 0; i < size; i++)
            temp_ptr[i] = arr[i];
        delete[] arr;
        arr = temp_ptr;
    }
    capacity=new_capacity;
}

template <typename T>
Vector<T>::Vector(const int& new_capacity) {
    arr=nullptr;
    size=0;
    capacity=0;

    if(new_capacity<0)
        throw std::invalid_argument("Capacity should be >=0");
    reallocation(new_capacity);
}

template <typename T>
Vector<T>::Vector(const Vector<T> &source_for_copy) {
    arr=nullptr;
    size=0;
    capacity=0;

    reallocation(source_for_copy.capacity);
    size=source_for_copy.size;
    for(int i=0;i<size;i++)
        arr[i]=source_for_copy.arr[i];
}

template <typename T>
Vector<T>::~Vector(){
    delete[] arr;
}

template <typename T>
int Vector<T>::Size() const {
    return size;
}

template <typename T>
int Vector<T>::Capacity() const {
    return capacity;
}

template <typename T>
bool Vector<T>::Empty() const {
    return size==0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &source_for_copy) {
    delete[] arr;
    size=0;
    capacity=0;
    arr=nullptr;

    reallocation(source_for_copy.capacity);
    size=source_for_copy.size;
    for(int i=0;i<size;i++)
        arr[i]=source_for_copy.arr[i];
    return *this;
}

template <typename T>
T& Vector<T>::operator[](const int& index) const{
    return arr[index];
}

template <typename T>
T& Vector<T>::at(const int& index) const{
    if(index<0 or index>=capacity)
        throw std::invalid_argument("Index should be >=0 and <capacity");
    return arr[index];
}

template <typename T>
void Vector<T>::push_back(const T& obj) {
    if(size==capacity){
        if(capacity==0)
            reallocation(step_for_reallocation);
        else
            reallocation(capacity*step_for_reallocation);
    }
    arr[size]=obj;
    size++;
}

template <typename T>
void Vector<T>::pop_back() {
    int size_after_pop=size-1;
    if(size_after_pop <= capacity/2){
        reallocation(capacity/2);
    }
    else
        size--;
}
#endif
