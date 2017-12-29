#ifndef MY_STACK_HPP
#define MY_STACK_HPP

template <typename T>
class Stack{
private:
    int capacity;
    struct Node{
        T value;
        Node *next;
    };
    Node *tos;
public:
    Stack();
    Stack(Stack<T> &from);
    ~Stack();
    int size() const;
    bool empty() const;
    void clear();
    void pop();
    void push(const T& pushed_value);
    T& top() const;
};


template <typename T>
T& Stack<T>::top() const{
    return tos->value;
}

template <typename T>
void Stack<T>::clear(){
    while(!empty())
        pop();
}

template <typename T>
bool Stack<T>::empty() const {
    return capacity==0;
}

template <typename T>
int Stack<T>::size() const{
    return capacity;
}

template <typename T>
Stack<T>::~Stack(){
    clear();
}

template <typename T>
Stack<T>::Stack() {
    tos=nullptr;
    capacity=0;
}

template <typename T>
Stack<T>::Stack(Stack<T> &from){
    Stack<T> temp1, temp2;
    while(!from.empty()){
        temp1.push(from.top());
        temp2.push(from.top());
        from.pop();
    }
    while(!temp1.empty())
        from.push(temp1.pop());//Восстанавливаем стек из которого копировали
    while(!temp2.empty())
        this->push(temp2.pop());//Заполняем стек
}

template <typename T>
void Stack<T>::push(const T& pushed_value) {
    Node * temp = new Node();
    temp->next=tos;//Поставили указатель на старую вершину, новой будет temp.
    temp->value=pushed_value;
    tos=temp;//Переназначили вершину стека
    capacity++;
}

template <typename T>
void Stack<T>::pop() {
    if(!empty()){
        Node * temp=tos;//Берем текущую вершину стека
        T temp_value=tos->value;
        tos=temp->next;//Смещаем вершину стека
        delete temp;//Удаляем старую вершину
        capacity--;
    }
}

#endif
