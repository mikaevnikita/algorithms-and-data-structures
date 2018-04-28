#include <iostream>
using namespace std;

template <typename T>
class ForwardList{
private:
    class Node;
public:
    class Iterator{
    private:
        Node* ptr;
        friend class ForwardList<T>;
    public:
        Iterator()
        :ptr(nullptr){
        }
        Iterator(Node* ptr){
            this->ptr=ptr;
        }
        Iterator(const Iterator& iter){
            ptr = iter.ptr;
        }
        T& operator*() const{
            return ptr->value;
        }
        Iterator& operator++(){
            if(ptr->next_node!=nullptr)
                ptr=ptr->next_node;
            else
                ptr = nullptr;
            return *this;
        }
        Iterator& operator=(const Iterator& iter){
            ptr=iter.ptr;
            return *this;
        }
        bool operator==(const Iterator& iter) const{
            if(iter.ptr == nullptr and ptr == nullptr)
                return true;
            return ptr==iter.ptr;
        }
        bool operator!=(const Iterator& iter) const{
            return !this->operator==(iter);
        }
    };
    
    Iterator begin() const{
        return Iterator(head);
    }
    Iterator end() const{
        return end_iterator;
    }
private:
    struct Node{
        T value;
        Node* next_node;
    };
    int capacity;
    Node* head;
    Iterator end_iterator;
    
public:
    ForwardList()
    :capacity(0), head(nullptr)
    {
    }
    
    ForwardList(const ForwardList& copy_from){
        capacity=0;
        head=nullptr;
        
        Node* temp_ptr=copy_from.head;
        if(temp_ptr == nullptr)
            return;
        
        head = new Node;
        head->value = temp_ptr->value;
        head->next_node = nullptr;
        capacity = 1;
        
        Node* tail = head;
        while(temp_ptr->next_node){
            tail->next_node = new Node;
            tail->next_node->value = temp_ptr->next_node->value;
            tail = tail->next_node;
            tail->next_node = nullptr;
            temp_ptr = temp_ptr->next_node;
            capacity++;
        }
    }
    
    ~ForwardList(){
        clear();
    }
    
    ForwardList<T>& operator=(const ForwardList<T>& copy_from){
        if(this == &copy_from)
            return *this;
        clear();

        Node* temp_ptr=copy_from.head;
        if(temp_ptr == nullptr)
            return;
        
        
        head = new Node;
        head->value = temp_ptr->value;
        head->next_node = nullptr;
        capacity = 1;
        
        Node* tail = head;
        while(temp_ptr->next_node){
            tail->next_node = new Node;
            tail->next_node->value = temp_ptr->next_node->value;
            tail = tail->next_node;
            tail->next_node = nullptr;
            temp_ptr = temp_ptr->next_node;
            capacity++;
        }
        
        return *this;
    }
    
    int size() const{
        return capacity;
    }
    
    bool empty() const{
        return capacity == 0;
    }
    
    void push_front(T obj){
        Node* temp_head=head;
        head=new Node;
        head->value=obj;
        head->next_node=temp_head;
        capacity++;
    }
    
    void erase_after(Iterator& iter){
        if(iter.ptr){
            Node* temp = iter.ptr->next_node;
            if(temp){
                iter.ptr->next_node = temp->next_node;
                delete temp;
                capacity--;
            }
        }
    }
    
    void clear(){
        while(head != nullptr)
            pop_front();
    }
    
    void pop_front(){
        Node* temp_head = head;
        head = head->next_node;
        if(temp_head){
            delete temp_head;
            capacity--;
        }
    }
    
    void insert_after(Iterator& iter, const T& insertion_value){
        if(iter.ptr == nullptr){
            if(head == nullptr)
                push_front(insertion_value);
            return;
        }
        Node* new_node=new Node;
        new_node->value=insertion_value;
        new_node->next_node=iter.ptr->next_node;
        iter.ptr->next_node=new_node;
        capacity++;
    }
    
};


int main(){
    ForwardList<int> fl;
    fl.push_front(3);
    fl.push_front(4);
    fl.push_front(5);
    
    for(auto it = fl.begin(); it != fl.end(); ++it)
        cout << *it << endl;
    
    return 0;
}

