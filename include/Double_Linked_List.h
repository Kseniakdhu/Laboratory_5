#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <memory_resource>
#include "Fixed_Block_Memory_Resource.h"
#include <iostream>
#include <iterator>

template<typename T>
class double_linked_list{
    private:
        struct Node{
            T data;
            Node* next;
            Node* prev;
            Node(const T& value, Node* n = nullptr, Node* p = nullptr)
            : data(value), next(n), prev(p){}
        };

        Node* head;
        Node* tail;
        std:: size_t size;
        std::pmr::polymorphic_allocator<Node> allocator;

    public:
        explicit double_linked_list(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : head(nullptr), tail(nullptr), size(0), allocator(resource) {}

        ~double_linked_list(){
            clear();
        }

        
        void push_back(const T& value){
            Node* node = allocator.allocate(1);
            try{
                allocator.construct(node, value, nullptr, tail);
            }
            catch(...){
                allocator.deallocate(node, 1);
                throw;
            }
            node->prev = tail;
            if (tail != nullptr){
                tail->next = node;
            }
            if (head == nullptr){
                head = node;
            }
            tail = node;
            ++size;
        }


        void push_front(const T& value){
             Node* node = allocator.allocate(1);
            try{
                allocator.construct(node, value, head, nullptr);
            }
            catch(...){
                allocator.deallocate(node, 1);
                throw;
            }
            node->next = head;
            if (head != nullptr){
                head->prev = node;
            }
            else{
                tail = node;
            }
            head = node;
            ++size;
        }


        void pop_back(){
            if (tail == nullptr){
                return;
            }
            Node* node = tail;
            tail = tail->prev;
            if (tail != nullptr){
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            allocator.destroy(node);
            allocator.deallocate(node, 1);
            --size;
        }


        void pop_front(){
            if (head == nullptr){
                return;
            }
            Node* node = head;
            head = head->next;
            if (head != nullptr){
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            allocator.destroy(node);
            allocator.deallocate(node, 1);
            --size;
        }


        void clear(){
            while (!empty()){
                pop_front();
            }
        }
        

        bool empty() const { return size == 0; }
        std::size_t size_() const { return size; }

  
        class iterator{
            private:
                Node* current;
            
                public:
                    using value_type = T;
                    using size_type = size_t;
                    using difference_type = ptrdiff_t;
                    using pointer = T*;
                    using reference = T&;

                    explicit iterator(Node* node = nullptr) : current(node) {}

                    reference operator*() const { return current->data; }
        
                    pointer operator->() const { return &current->data; }

                    iterator& operator++(){
                            if (current){
                                current = current->next;
                            }
                            return *this;
                    }

                    iterator operator++(int){
                        iterator temp = *this;
                        ++(*this);
                        return temp;
                    }

                    bool operator==(const iterator& other) const { return current == other.current; }
                    bool operator!=(const iterator& other) const { return current != other.current; }

        };

        iterator begin() { return iterator(head); }
        iterator end() { return iterator(nullptr); }
    };

#endif
