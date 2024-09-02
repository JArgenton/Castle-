#pragma once
#include <iostream>

namespace List
{
    template <typename T_LIST>
    class List
    {
    private:
        template <typename T_ELEM>
        class Node
        {
        private:
            T_ELEM *data;

        public:
            Node<T_ELEM> *next;
            Node<T_ELEM> *prev;
            Node()
            {
                next = nullptr;
                prev = nullptr;
                data = nullptr;
            }
            ~Node()
            {
                next = nullptr;
                prev = nullptr;
                data = nullptr;
            }

            void setData(T_ELEM *Data)
            {
                data = Data;
            }

            T_ELEM *getData()
            {
                return data;
            }

            void setNext(Node<T_ELEM> *newNode)
            {
                next = newNode;
            }

            void setPrev(Node<T_ELEM> *newNode)
            {
                prev = newNode;
            }

            Node<T_ELEM> *getNext()
            {
                return next;
            }

            Node<T_ELEM> *getPrev()
            {
                return prev;
            }
        };

        Node<T_LIST> *head;
        Node<T_LIST> *tail;
        int size;

    public:
        List();
        ~List();
        void push(T_LIST *node);
        void clear();
        int getsize();
        T_LIST *pop(T_LIST *elem);
        T_LIST *pop(int index);
        T_LIST *operator[](int index);
    };

    template <class T_LIST>
    List<T_LIST>::List() : head(nullptr),
                           tail(nullptr),
                           size(0)
    {
    }

    template <class T_LIST>
    List<T_LIST>::~List()
    {
        clear();
    }

    template <class T_LIST>
    void List<T_LIST>::push(T_LIST *elem)
    {
        if (elem)
        {
            Node<T_LIST> *newNode = new Node<T_LIST>();
            newNode->setData(elem);

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                newNode->setPrev(tail);
                tail->setNext(newNode);
                tail = newNode;
            }

            size++;
        }
        else
        {
            std::cout << "ERRO AO TENTAR INSERIR, ELEM NULO" << std::endl;
        }
    }

    template <class T_LIST>
    void List<T_LIST>::clear()
    {
        Node<T_LIST> *current = head;
        while (current != nullptr)
        {
            Node<T_LIST> *next = current->getNext();
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    template <class T_LIST>
    int List<T_LIST>::getsize()
    {
        return size;
    }

    template <class T_LIST>
    T_LIST *List<T_LIST>::pop(T_LIST *elem)
    {
        if (head == nullptr)
        {
            std::cout << "List is empty" << std::endl;
            return nullptr;
        }

        Node<T_LIST> *current = head;
        Node<T_LIST> *prev = nullptr;
        while (current != nullptr)
        {
            if (current->getData() == elem)
            {
                if (prev == nullptr)
                {
                    head = current->getNext();
                }
                else
                {
                    prev->setNext(current->getNext());
                }

                if (current == tail)
                {
                    tail = prev;
                }

                T_LIST *data = current->getData();
                delete current;
                size--;
                return data;
            }

            prev = current;
            current = current->getNext();
        }

        std::cout << "Element not found" << std::endl;
        return nullptr;
    }

    template <class T_LIST>
    T_LIST *List<T_LIST>::pop(int index)
    {
        if (index < 0 || index >= size)
        {
            std::cout << "Index out of bounds" << std::endl;
            return nullptr;
        }

        Node<T_LIST> *current = head;
        Node<T_LIST> *prev = nullptr;
        for (int i = 0; i < index; i++)
        {
            prev = current;
            current = current->getNext();
        }

        if (prev == nullptr)
        {
            head = current->getNext();
        }
        else
        {
            prev->setNext(current->getNext());
        }

        if (current == tail)
        {
            tail = prev;
        }

        T_LIST *data = current->getData();
        delete current;
        size--;
        return data;
    }

    template <class T_LIST>
    T_LIST *List<T_LIST>::operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            std::cout << "Index out of bounds" << std::endl;
            return nullptr;
        }

        Node<T_LIST> *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->getNext();
        }

        return current->getData();
    }
} // namespace List