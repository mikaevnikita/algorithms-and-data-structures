#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <stdexcept>

template <typename T>
class ForwardList{
private:
    struct Node{
        T value;
        Node* next_node;
    };
    int capacity;
    Node* head;
    Node* tail;
    void base_init();
    void free_memory();
    void eraseNode(Node* node_for_del);
public:
    ForwardList(const int& capacity);
    ForwardList();
    ForwardList(T* const ptr_from_copy, const int& size_of_array);
    ForwardList(const ForwardList& copy_from);
    ~ForwardList();

    ForwardList<T>& operator=(const ForwardList<T>& copy_from);

    int size() const;
    bool empty() const;
    void push_back(const T& obj);
    void push_front(const T& obj);

    class Iterator{
    private:
        Node* ptr;
        friend class ForwardList<T>;
    public:
        Iterator(Node *const ptr_);
        Iterator(const Iterator& iter);
        T& operator*() const;
        Iterator& operator++();
        Iterator& operator=(const Iterator& iter);
        bool operator==(const Iterator& iter) const;
        bool operator!=(const Iterator& iter) const;
    };


    Iterator begin() const;
    Iterator end() const;

    void erase(Iterator& iter);
    void pop_front();
    void pop_back();
    void insert_after(Iterator& iter, const T& insertion_value);

};

template <typename T>
void ForwardList<T>::insert_after(Iterator &iter,const T& insertion_value) {
    if(head == nullptr and tail == nullptr) {
        push_back(insertion_value);
        return;
    }
    Node* new_node=new Node;
    new_node->value=insertion_value;
    if(iter.ptr==head and iter.ptr==tail){
        tail=new_node;
        tail->next_node=nullptr;
        head->next_node=tail;
    }
    else{
        new_node->next_node=iter.ptr->next_node;
        iter.ptr->next_node=new_node;
    }
    capacity++;
}

template <typename T>
void ForwardList<T>::pop_back() {
    eraseNode(tail);
}

template <typename T>
void ForwardList<T>::pop_front() {
    eraseNode(head);
}

template <typename T>
void ForwardList<T>::erase(ForwardList<T>::Iterator& iter){
    eraseNode(iter.ptr);
}

template <typename T>
void ForwardList<T>::eraseNode(Node* node_for_del) {
    if(node_for_del==head) {
        if (head == tail)
            tail = nullptr;
        head = head->next_node;
    }
    else{
        Node* temp=head;
        while(temp->next_node != node_for_del)
            temp=temp->next_node;
        temp->next_node=node_for_del->next_node;
    }
    delete node_for_del;
    capacity--;
}


template <typename T>
void ForwardList<T>::free_memory() {
    for(int i=0;i<capacity;i++){
        Node* node = head;
        head = head -> next_node;
        delete node;
    }
    base_init();
}

template <typename T>
void ForwardList<T>::base_init() {
    capacity=0;
    head=nullptr;
    tail=nullptr;
}

template <typename T>
ForwardList<T>::ForwardList() {
    base_init();
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T> &copy_from) {
    if(this == &copy_from)
        return *this;
    free_memory();
    Node* temp_ptr=copy_from.head;
    for(int i=0;i<copy_from.capacity;i++){
        push_back(temp_ptr->value);
        temp_ptr=temp_ptr->next_node;
    }
    return *this;
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList &copy_from) {
    base_init();
    Node* temp_ptr=copy_from.head;
    while(temp_ptr!=nullptr){
        push_back(temp_ptr->value);
        temp_ptr=temp_ptr->next_node;
    }
}

template <typename T>
ForwardList<T>::ForwardList(T *const ptr_from_copy, const int &size_of_array) {
    if(size_of_array<0)
        throw std::invalid_argument("Size of array should be >=0");
    base_init();
    for(int i=0;i<size_of_array;i++)
        push_back(ptr_from_copy[i]);
}

template <typename T>
ForwardList<T>::~ForwardList() {
    free_memory();
}

template <typename T>
int ForwardList<T>::size() const {
    return capacity;
}

template <typename T>
bool ForwardList<T>::empty() const {
    return capacity == 0;
}

template <typename T>
void ForwardList<T>::push_back(const T& obj) {
    if(capacity == 0){
        head=new Node;
        tail=head;
        tail->value=obj;
    }
    else{
        Node* temp_tail = tail;
        tail=new Node;
        tail->value=obj;
        temp_tail->next_node=tail;
    }
    tail->next_node=nullptr;
    capacity++;
}

template <typename T>
void ForwardList<T>::push_front(const T &obj) {
    if(capacity == 0){
        head=new Node;
        tail=head;
        head->value=obj;
        tail->next_node=nullptr;
    }
    else{
        Node* temp_head=head;
        head=new Node;
        head->value=obj;
        head->next_node=temp_head;
    }
    capacity++;
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin() const{
    return Iterator(head);
}

template <typename T>
ForwardList<T>::Iterator::Iterator(Node *const ptr_) {
    ptr=ptr_;
}

template <typename T>
ForwardList<T>::Iterator::Iterator(const Iterator &iter) {
    ptr=iter.ptr;
}

template <typename T>
T& ForwardList<T>::Iterator::operator*() const {
    return ptr->value;
}

template <typename T>
typename ForwardList<T>::Iterator& ForwardList<T>::Iterator::operator++() {
    if(ptr->next_node!=nullptr)
        ptr=ptr->next_node;
    return *this;
}

template <typename T>
bool ForwardList<T>::Iterator::operator==(const Iterator &iter) const {
    return ptr==iter.ptr;
}

template <typename T>
typename ForwardList<T>::Iterator& ForwardList<T>::Iterator::operator=(const Iterator &iter) {
    ptr=iter.ptr;
}

template <typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator &iter) const {
    return ptr!=iter.ptr;
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end() const{
    return Iterator(tail);
}


template <typename T>
ForwardList<T>::ForwardList(const int &capacity) {
    if(capacity<0)
        throw std::invalid_argument("Capacity should be >=0");
    base_init();
    for(int i=0;i<capacity;i++)
        push_back(T());
}
#endif
