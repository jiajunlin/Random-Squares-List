#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include "Square.h"
using namespace std;

template <typename Object>
class List
{
private:
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node* next;

        Node(const Object& d = Object{ }, Node* n = nullptr)
            : data{ d }, next{ n } { }

        Node(Object&& d,  Node* n = nullptr)
            : data{ std::move(d) }, next{ n } { }


    };


public:
    class const_iterator
    {
    public:

        // Public constructor for const_iterator.
        const_iterator() : theList{ init() }, current { nullptr }
        { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object& operator* () const
        {
            return retrieve();
        }

        const_iterator& operator++ ()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            Node* ptr = this->theList->head->next;
            while (ptr->next != this->current) { // check for other boundary conditions here
                ptr = ptr->next;
            }
            this->current = ptr;
            return *this;
        }
        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }


        bool operator== (const const_iterator& rhs) const
        {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }




    protected:
        const List<Object>* theList; //the list for which the iterator belongs
        Node* current;

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator(const List<Object>& lst, Node* p)
            : theList{ &lst }, current{ p }
        { }

        void assertIsValid() const
        {
            if (theList == nullptr || current == nullptr || current == theList->head)
            {
                { 
                    cerr << "Invalid iterator. Exiting Program.\n"; 
                    exit(1);
                }
            }
        }

 

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object& retrieve() const
        {
            return current->data;
        }

        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
    public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator()
        { }

        Object& operator* ()
        {
            return const_iterator::retrieve();
        }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object& operator* () const
        {
            return const_iterator::operator*();
        }

        iterator& operator++ ()
        {
            if (this->current != nullptr) {
                this->current = this->current->next;
            }
            return *this;
        }

        iterator operator++ (int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            Node* ptr = this->theList->head->next;
            while (ptr->next != this->current) { // check for other boundary conditions here
                ptr = ptr->next;
            }
            this->current = ptr;
            return *this;
        }
        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }



    protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator(List<Object>& list, Node* p) : const_iterator(list, p) {}

        friend class List<Object>;

    };


public:
    List()
    {
        init();
    }

    ~List()
    {
        clear();
        //delete head;
        delete tail;
    }

    List(const List& rhs)
    {
        init();
        for (auto& x : rhs)
            push_back(x);
    }

    List& operator= (const List& rhs)
    {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }


    List(List&& rhs) noexcept
        : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List& operator= (List&& rhs) noexcept
    {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);

        return *this;
    }

    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin()
    {
        iterator itr{ *this, head };   // const_iterator itr{ head, head };   
        return ++itr;
    }

    const_iterator begin() const
    {
        const_iterator itr{ *this, head };   // const_iterator itr{ head, head };   
        return ++itr;
    }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end()
    {
        return iterator(*this, tail); 
    }

    const_iterator end() const
    {
        return const_iterator(*this, tail);
    }

    // Return number of elements currently in the list.
    int size() const
    {
        return theSize;
    }

    // Return true if the list is empty, false otherwise.
    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while (!empty())
            pop_front();
    }

    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object& front()
    {
        return *begin();
    }

    const Object& front() const
    {
        return *begin();
    }

    Object& back()
    {
        return *--end();
    }

    const Object& back() const
    {
        return *--end();
    }

    void push_front(const Object& x)
    {
        insert(begin(), x);
    }

    void push_back(const Object& x)
    {
        insert(end(), x);
    }

    void push_front(Object&& x)
    {
        insert(begin(), std::move(x));
    }

    void push_back(Object&& x)
    {
        insert(end(), std::move(x));
    }

    void pop_front()
    {
        erase(begin());
    }

    void pop_back()
    {
        if (empty()) {
            return;
        }

        else if (head->next == nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else 
        {
            Node* p = head;
            // Iterate until we reach the second-to-last node
            while (p->next != tail)
            {
                while (p->next != tail) {
                    p = p->next;
                }
            }

            // Delete the last node
            delete tail;
            tail = p;
            tail->next = nullptr;
        }
        --theSize;

    }


    // Insert x before itr.
    iterator insert(iterator itr, const Object& x)
    {
        itr.assertIsValid();
        if (itr.theList != this)
        {
            cerr << "Invalid Iterator. Exiting." << endl; 
            exit(1); 
        }
        Node* prev = nullptr; 
        if (itr.current != head)
        {
            prev = itr.theList->head; 
            while (prev != nullptr && prev->next != itr.current)
            {
                prev = prev->next; 
            }
        }
        ++theSize;
        auto newNode = new Node{ x, itr.current }; 
        if (prev != nullptr)
        {
            prev->next = newNode; 
        }
        else {
            head = newNode;
        }
        return iterator(*this, newNode);
    }

    // Insert x before itr.
    iterator insert(iterator itr, Object&& x)
    {
        Node* p = itr.current;
        ++theSize;
        return iterator(p->next = p->next = new Node{ std::move(x), p });
    }

    // Erase item at itr.
    iterator erase(iterator itr)
    {
        if (itr.current == nullptr)
        {
            cerr << "Iterator is invalid. Exiting." << endl;
            exit(1);
        }

        Node* prev = nullptr;
        // Find the previous node
        for (auto current = head; current != nullptr; current = current->next)
        {
            if (current->next == itr.current)
            {
                prev = current;
                break; 
            }
        }
        // Check if iterator is pointing to tail
        if (itr.current == tail) {
            tail = prev;
            prev->next = nullptr; 
        }

        // Update prev to skip over deleted node
        if (prev != nullptr) {
            prev->next = itr.current->next;
        }
        else
        {
            head = itr.current->next; 
        }
        // Delete node and return iterator to next node
        iterator retVal{ *this, itr.current->next };
        delete itr.current;
        --theSize;
        return retVal;
    }

    iterator erase(iterator from, iterator to)
    {
        for (iterator itr = from; itr != to; )
            itr = erase(itr);

        return to;
    }

private:
    int   theSize;
    Node* head;
    Node* tail;

    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;

    }
};


#endif
