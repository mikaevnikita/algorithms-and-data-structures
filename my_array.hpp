#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>
#include <new>
#include <iostream>

/*
    Array<int>::Iterator iter = a.begin();//Можно все
    const Array<int>::Iterator iter2=a.begin();//Не можем смещать итератор
    Array<int>::ConstIterator c_iter=a.c_begin();//Можно смещать, но нельзя изменять объект
    const Array<int>::ConstIterator c_iter2=a.c_begin();//Ничего нельзя
 */

template <typename T>
class Array{
private:
    T* array;
    long capacity;
public:
    Array<T>(T *const ptr_from_copy,const long& capacity_);
    Array<T>(const long& capacity_);
    Array<T>(const Array<T>& obj);
    ~Array<T>();

    T& operator[](const long& index);
    const T& operator[](const long& index) const;
    T& at(const long& index);
    const T& at(const long& index) const;

    long size() const;
    bool empty() const;
    void fill(const T& value);

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

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
    ConstIterator c_begin() const;
    Iterator end() const;
    ConstIterator c_end() const;


};
template <typename T>
bool Array<T>::ConstIterator::operator<=(const ConstIterator& iter) const{
    return ptr<=iter.ptr;
}

template <typename T>
bool Array<T>::ConstIterator::operator>=(const ConstIterator& iter) const{
    return ptr>=iter.ptr;
}


template <typename T>
bool Array<T>::ConstIterator::operator<(const ConstIterator& iter) const{
    return ptr<iter.ptr;
}

template <typename T>
bool Array<T>::ConstIterator::operator>(const ConstIterator& iter) const{
    return ptr>iter.ptr;
}

template <typename T>
bool Array<T>::ConstIterator::operator!=(const ConstIterator& iter) const{
    return ptr!=iter.ptr;
}

template <typename T>
bool Array<T>::ConstIterator::operator==(const ConstIterator& iter) const{
    return ptr==iter.ptr;
}

template <typename T>
typename Array<T>::ConstIterator& Array<T>::ConstIterator::operator=(const ConstIterator& iter){
    ptr=iter.ptr;
    return *this;
}


template <typename T>
bool Array<T>::Iterator::operator<=(const Iterator& iter) const{
    return ptr<=iter.ptr;
}

template <typename T>
bool Array<T>::Iterator::operator>=(const Iterator& iter) const{
    return ptr>=iter.ptr;
}


template <typename T>
bool Array<T>::Iterator::operator<(const Iterator& iter) const{
    return ptr<iter.ptr;
}

template <typename T>
bool Array<T>::Iterator::operator>(const Iterator& iter) const{
    return ptr>iter.ptr;
}

template <typename T>
bool Array<T>::Iterator::operator!=(const Iterator& iter) const{
    return ptr!=iter.ptr;
}

template <typename T>
bool Array<T>::Iterator::operator==(const Iterator& iter) const{
    return ptr==iter.ptr;
}

template <typename T>
typename Array<T>::Iterator& Array<T>::Iterator::operator=(const Iterator& iter){
    ptr=iter.ptr;
    return *this;
}

template <typename T>
typename Array<T>::Iterator Array<T>::begin() const{
    return Iterator(array);
}

template <typename T>
typename Array<T>::ConstIterator Array<T>::c_begin() const{
    return ConstIterator(array);
}

template <typename T>
typename Array<T>::Iterator Array<T>::end() const{
    if(empty())
        return begin();
    return Iterator(array+capacity+(empty() ? -1 : 0));
}

template <typename T>
typename Array<T>::ConstIterator Array<T>::c_end() const{
    if(empty())
        return c_begin();
    return ConstIterator(array+capacity+(empty() ? -1 : 0));
}

template <typename T>
Array<T>::Iterator::Iterator(T *const ptr_) {
    ptr=ptr_;
}

template <typename T>
Array<T>::ConstIterator::ConstIterator(const T *const ptr_){
    ptr=ptr_;
}

template <typename T>
Array<T>::Iterator::Iterator(const Iterator& iter) {
    ptr=iter.ptr;
}

template <typename T>
Array<T>::ConstIterator::ConstIterator(const ConstIterator &c_iter) {
    ptr=c_iter.ptr;
}

template <typename T>
T& Array<T>::Iterator::operator*() const{
    return *ptr;
}

template <typename T>
const T& Array<T>::ConstIterator::operator*() const{
    return *ptr;
}

template <typename T>
typename Array<T>::Iterator& Array<T>::Iterator::operator++() {
    ptr++;
    return *this;
}

template <typename T>
typename Array<T>::ConstIterator& Array<T>::ConstIterator::operator++() {
    ptr++;
    return *this;
}

template <typename T>
typename Array<T>::Iterator& Array<T>::Iterator::operator--() {
    ptr--;
    return *this;
}

template <typename T>
typename Array<T>::ConstIterator& Array<T>::ConstIterator::operator--() {
    ptr--;
    return *this;
}

template <typename T>
Array<T>::Array(T *const ptr_from_copy, const long &capacity_) {
    if(capacity_<0){
        throw std::invalid_argument("Size argument should be >0");
    }
    try{
        array=new T[capacity_];
    }
    catch (const std::bad_alloc &e){
        std::cerr << "Allocation failed " << e.what() << std::endl;
        throw e;
    }
    capacity=capacity_;
    for(int i=0;i<capacity;i++)
        array[i]=ptr_from_copy[i];
}

template <typename T>
Array<T>::Array(const long& capacity_) {
    if(capacity_<0){
        throw std::invalid_argument("Size argument should be >0");
    }
    try{
        array=new T[capacity_];
    }
    catch (const std::bad_alloc &e){
        std::cerr << "Allocation failed " << e.what() << std::endl;
        throw e;
    }
    capacity=capacity_;
}

template <typename T>
Array<T>::Array(const Array& obj) {
    try{
        array=new T[obj.capacity];
    }
    catch(std::bad_alloc& e){
        std::cerr << "Allocation failed " << e.what() << std::endl;
        throw e;
    }
    capacity=obj.capacity;
    for(int i=0;i<capacity;i++)
        array[i]=obj.array[i];

}

template <typename T>
Array<T>::~Array() {
    delete[] array;
}

template <typename T>
T& Array<T>::operator[](const long &index) {
    return array[index];
}

template <typename T>
const T& Array<T>::operator[](const long &index) const {
    return array[index];
}

template <typename T>
T& Array<T>::at(const long &index) {
    if(index<0 or index>=capacity)
        throw std::invalid_argument("Index should be >0");
    return array[index];
}

template <typename T>
const T& Array<T>::at(const long &index) const {
    if(index<0 or index>=capacity)
        throw std::invalid_argument("Index should be >0");
    return array[index];
}

template <typename T>
long Array<T>::size() const {
    return capacity;
}

template <typename T>
bool Array<T>::empty() const {
    return capacity==0;
}

template <typename T>
void Array<T>::fill(const T& value){
    for(int i=0;i<capacity;i++)
        array[i]=value;
}

template <typename T>
T& Array<T>::front(){
    return *array;
}

template <typename T>
const T& Array<T>::front() const {
    return *array;
}

template <typename T>
T& Array<T>::back(){
    return *(array+capacity+(empty() ? 0 : -1));
}

template <typename T>
const T& Array<T>::back() const {
    return *(array+capacity+(empty() ? 0 : -1));
}


#endif
