//
// Created by user on 4/6/2015.
//


#ifndef SHAPES_CIRCULARLIST_H
#define SHAPES_CIRCULARLIST_H

template<class T>
class CircularList {
public:
    class Node {
    public:
        T item;
        Node *next;
        Node *prev;

        Node(T item, Node *next = nullptr, Node *prev = nullptr) : item(item),
                                                                   next(next),
                                                                   prev(prev) { }
    };

    int _length = 0;
    Node *current = nullptr;

public:


    CircularList() { }


    virtual ~CircularList() {
        if (this->hasNext())
            this->remove();
    }

    void append(const T &item) {
        Node *circularListItem = new Node(item);
        if (!_length) {
            current = circularListItem;
            circularListItem->next = circularListItem;
            circularListItem->prev = circularListItem;
        }
        else {
            circularListItem->prev = current;
            circularListItem->next = current->next;

            current->next->prev = circularListItem;
            current->next = circularListItem;
            current = circularListItem;
        }

        ++_length;
    }

    void remove() {
        if (_length == 0) {
            return;
        }
        else if (_length == 1) {
            delete current;
            current = nullptr;
        }
        else {
            CircularList::Node *tempNode = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->prev;
            delete tempNode;
        }


        --_length;
    }

    bool hasNext() const { return _length > 0; }

    T next() {
        current = current->next;
        T result = current->item;
        return result;
    }

    int length() const {
        return _length;
    }

};


#endif //SHAPES_CIRCULARLIST_H
