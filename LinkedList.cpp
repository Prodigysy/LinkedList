#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <utility>
#include <memory>
#include <stdexcept>
#include <string>


template<typename T>
struct Node
{
    T data;
    Node* pNext;
    Node()
        :pNext{nullptr},data{T()}
    {}
    Node(const T& _data)
        :pNext{nullptr},data{_data}{}
    Node(T&& _data)
        :pNext{ nullptr }
    {
        data = std::move(_data);
    }
    ~Node(){}
};

template<typename T>
class LinkedList
{
private:
    
    Node<T>* head;
    Node<T>* tail;
    int _size;
    
    Node<T>* beforeNode(Node<T>* &key_node)
    {
        if (head == nullptr)
            return nullptr;
        
        Node<T>* p = head;
        
        while (p!=nullptr && p->pNext != key_node)
        {
            p = p->pNext;
        }
        return p;
    }
    void deleteNode(Node<T>* &del)
    {
        if (del == head)
            pop_head();
        else
            if (del == tail)
                pop_tail();
            else
            {
                Node<T>* bef = beforeNode(del);
                if (bef == nullptr)
                    return;
                bef->pNext = del->pNext;
                delete del;
                _size--;
            }
    }
