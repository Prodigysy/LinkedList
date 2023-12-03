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
