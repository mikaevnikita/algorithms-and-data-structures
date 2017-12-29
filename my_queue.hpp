#ifndef MY_QUEUE_HPP
#define MY_QUEUE_HPP

template<typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head;
    Node* tail;
    int capacity;
public:
    Queue();
    Queue(Queue<T>& from);
    ~Queue();
    void push(const T& pushed_value);
    void pop();
    void clear();
    T& front() const;
    bool empty() const;
    int size();
};

template <typename T>
void Queue<T>::clear(){
    while(!empty())
        pop();
}

template <typename T>
bool Queue<T>::empty() const{
    return capacity==0;
}

template <typename T>
int Queue<T>::size() {
    return capacity;
}

template <typename T>
T& Queue<T>::front() const{
    return head->value;
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
Queue<T>::Queue() {
    head=tail=nullptr;
    capacity=0;
}

template <typename T>
Queue<T>::Queue(Queue<T> &from) {
    Queue<T> temp1,temp2;
    while(!from.empty()){
        temp1.push(from.front());
        temp2.push(from.front());
        from.pop();
    }
    while(!temp1.empty()){
        from.push(temp1.front());
        temp1.pop();
    }
    while(!temp2.empty()){
        this->push(temp2.front());
        temp2.pop();
    }
}

template <typename T>
void Queue<T>::push(const T& pushed_value) {
    Node* n = new Node;
    n->next = nullptr;
    n->value = pushed_value;
    if(head != nullptr) {
        tail->next = n;
        tail = n;
    }
    else
        head = tail = n;
    capacity++;
}

template <typename T>
void Queue<T>::pop(){
    Node* temp = head;
    if(temp != nullptr){
        head = head->next;
        delete temp;
        capacity--;
    }
    if(head == nullptr)
        tail = nullptr;
}

#endif //MY_QUEUE_HPP
