//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_LINKEDLIST_H
#define CONCURRENTHASHMAP_LINKEDLIST_H

#include "../Exception/KeyNotFoundException.h"
#include "../Interface/ILinkedList.h"

template<class K, class V, class KeyEqual = std::equal_to<K>>
class LinkedList : public ILinkedList<K, V, KeyEqual> {
public:
    LinkedList();
    ~LinkedList();

    void put(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    V &at(const K &key) const;
    bool contains(const K &key) const;

    virtual std::string getName() const;
    void clear();
    Node<K, V> *find(const K &key) const;
protected:
    Node<K, V> *first;
    const std::string className = "Linked List";

    Node<K, V> *insert(const K &key, const V &value);
};

template<class K, class V, class KeyEqual>
LinkedList<K, V, KeyEqual>::LinkedList() : ILinkedList<K, V, KeyEqual>() {
    first = nullptr;
}

template<class K, class V, class KeyEqual>
LinkedList<K, V, KeyEqual>::~LinkedList() {
    clear();
}

template<class K, class V, class KeyEqual>
void LinkedList<K, V, KeyEqual>::clear() {
    if ( first != nullptr ) {
        Node<K, V> *prev;

        while (first != nullptr) {
            prev = first;
            first = first->next;
            delete prev;
        }
    }
    this->total = 0;
}

template<class K, class V, class KeyEqual>
void LinkedList<K, V, KeyEqual>::put(const K &key, const V &value) {
    Node<K, V> *curr = find(key);

    if (curr == nullptr) {
        insert(key, value);
    } else {
        curr->value = value;
    }
}

template<class K, class V, class KeyEqual>
void LinkedList<K, V, KeyEqual>::remove(const K &key) {\
    Node<K, V> *curr = first;
    Node<K, V> *prev = nullptr;

    while (curr != nullptr && !KeyEqual()(curr->key, key)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        throw KeyNotFoundException();
    } else {
        if (prev == nullptr) {
            first = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
        --this->total;
    }
}

template<class K, class V, class KeyEqual>
V &LinkedList<K, V, KeyEqual>::operator[](const K &key) {
    Node<K, V> *curr = find(key);

    if (curr == nullptr) {
        curr = insert(key, V());
    }

    return curr->value;
}

template<class K, class V, class KeyEqual>
V &LinkedList<K, V, KeyEqual>::at(const K &key) const {
    Node<K, V> *curr = find(key);

    if (curr == nullptr) {
        throw KeyNotFoundException();
    } else {
        return curr->value;
    }
}

template<class K, class V, class KeyEqual>
bool LinkedList<K, V, KeyEqual>::contains(const K &key) const {
    return find(key) != nullptr;
}

template<class K, class V, class KeyEqual>
std::string LinkedList<K, V, KeyEqual>::getName() const {
    return className;
}

template<class K, class V, class KeyEqual>
Node<K, V> *LinkedList<K, V, KeyEqual>::insert(const K &key, const V &value) {
    first = new Node<K, V>(first, key, value);
    ++this->total;
    return first;
}

template<class K, class V, class KeyEqual>
Node<K, V> *LinkedList<K, V, KeyEqual>::find(const K &key) const {
    Node<K, V> *curr = first;

    while (curr != nullptr && !KeyEqual()(curr->key, key)) {
        curr = curr->next;
    }

    return curr;
}

#endif
