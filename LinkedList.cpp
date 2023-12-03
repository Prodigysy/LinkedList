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
public:

    LinkedList()
        :_size{0},head{nullptr},tail{nullptr}
    {}
    
    LinkedList(int sz, const T& fil)
    {
        if (sz <= 0)
            throw std::out_of_range("Out of ranges");
        int cur = 0;
        while (cur < sz)
        {
            push_tail(fil);
            cur++;
        }
    }

    LinkedList(const LinkedList<T>& ls)
        :LinkedList()
    {
        for (int i = 0; i < ls.size(); i++)
             push_tail(ls[i]);
    }

    LinkedList(LinkedList<T>&& ls)
        :LinkedList()
    {
        this->head = ls.head;
        this->tail = ls.tail;
        this->_size = ls.size();
        ls.head = nullptr;
        ls.tail = nullptr;
        ls._size = 0;
    }

    ~LinkedList()
    {
        clear();
    }

    bool empty()const { return this->head == nullptr; }

    void push_tail(const T& data)
    {
        if (this->head == nullptr)
        {
            this->head = new Node<T>(data);
            if (this->head == nullptr)
                throw std::bad_alloc();
            this->tail = this->head;
            this->_size++;
        }
        else
        {
            Node<T>* nw = new Node<T>(data);
            if (nw == nullptr)
                throw std::bad_alloc();
            this->tail->pNext = nw;
            this->tail = nw;
            this->_size++;
        }
    }
    
    void push_tail(const LinkedList<T>& ls)
    {
        if (ls.empty())
            throw std::underflow_error("List is empty");

        for (int i = 0; i < ls.size(); i++)
             push_tail(ls[i]);
    }
    
    void push_head(const T& data)
    {
        if (head == nullptr)
        {
            this->head = new Node<T>(data);
            this->tail = this->head;
            if (head == nullptr)
                throw std::bad_alloc();
            this->_size++;

        }
        else
        {
            Node<T>* p = new Node<T>(data);
            if (p == nullptr)
                throw std::bad_alloc();
            p->pNext = this->head;
            this->head = p;
            this->_size++;
        }
    }
    
    void push_head(const LinkedList<T>& ls)
    {
        if (ls.empty())
            throw std::underflow_error("List is empty");

        for (int i = 0; i < ls.size(); i++)
            push_head(ls[i]);
    }
    
    int size()const { return _size;}

    void clear()
    {
        Node<T>* p = this->head;
        while (p != nullptr)
        {
            Node<T>* im = p;
            p = p->pNext;
            delete im;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->_size = 0;
    }
     
    const T& front()const
    {
        if (this->size()<=0)
            std::logic_error("List is empty");

        return head->data;
    }
    
    const T& back()const
    {

        if (this->size()<=0)
            throw std::logic_error("List is empty");

        return tail->data;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= _size)
            throw std::out_of_range("index out of ranges");
        Node<T>* p = this->head;
        int i = 0;
        while (i < index && p!=nullptr)
        {
            p = p->pNext;
            i++;
        }
        return p->data;
    }

    const T& operator[](int index)const
    {
        if (index < 0 || index >= _size)
            throw std::out_of_range("index out of ranges");
        
        Node<T>* p = this->head;
        int i = 0;   
        while (i < index && p != nullptr)
        {
            p = p->pNext;
            i++;
        }

        return p->data;
    }

    void pop_tail()
    {
        if (head == nullptr)
            throw std::underflow_error("List is empty");
        
        if (tail == head)
        {
            delete tail;
            tail = nullptr;
            head = nullptr;
            _size = 0;
        }
        
        else
        {
            Node<T>* p = this->head;
            while (p->pNext != this->tail)
                p = p->pNext;
            delete this->tail;
            this->tail = p;
            this->tail->pNext = nullptr;
            _size--;
        }
    }
    
    void pop_head()
    {

        if (head == nullptr)
            throw std::underflow_error("List is empty");
        if (head == tail)
        {
            delete head;
            this->head = nullptr;
            this->tail = nullptr;
            _size = 0;
        }
        else
        {
            Node<T>* pn = head->pNext;
            delete head;
            head = pn;
            _size--;
        }
    }

    void delByValue(const T& delNode)
    {
        Node<T>* p = this->head;
        while (p != nullptr)
        {
            Node<T>* cur = p;
            p = p->pNext;
            if (cur->data == delNode)
                deleteNode(cur);
        }

    }

    