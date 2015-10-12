//
// Created by Fear on 10/11/15.
//

#ifndef CELERAONEEX2_CONCURRENTLINKEDLIST_H
#define CELERAONEEX2_CONCURRENTLINKEDLIST_H

#include <mutex>
#include "LinkedList.h"

template<class K, class V, class KeyEqual = std::equal_to<K>>
class ConcurrentLinkedList : public ILinkedList<K, V, KeyEqual> {
public:
    ConcurrentLinkedList();
    ~ConcurrentLinkedList();

    void put(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    V &at(const K &key) const;
    bool contains(const K &key) const;

    virtual std::string getName() const;
    void clear();
    Node<K, V> *find(const K &key) const;
    virtual bool isEmpty() const;
    virtual size_t size() const;
protected:
    mutable std::recursive_mutex _lock;

    LinkedList<K, V, KeyEqual> *linkedList;
    const std::string className = "Concurrent Linked List";
};

template<class K, class V, class KeyEqual>
ConcurrentLinkedList<K, V, KeyEqual>::ConcurrentLinkedList() : ILinkedList<K, V, KeyEqual>() {
    linkedList = new LinkedList<K, V, KeyEqual>();
}

template<class K, class V, class KeyEqual>
ConcurrentLinkedList<K, V, KeyEqual>::~ConcurrentLinkedList() {
    linkedList->clear();
    delete linkedList;
}

template<class K, class V, class KeyEqual>
void ConcurrentLinkedList<K, V, KeyEqual>::clear() {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    linkedList->clear();
}

template<class K, class V, class KeyEqual>
void ConcurrentLinkedList<K, V, KeyEqual>::put(const K &key, const V &value) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    linkedList->put(key, value);
}

template<class K, class V, class KeyEqual>
void ConcurrentLinkedList<K, V, KeyEqual>::remove(const K &key) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    linkedList->remove(key);
}

template<class K, class V, class KeyEqual>
V &ConcurrentLinkedList<K, V, KeyEqual>::operator[](const K &key) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return linkedList->operator[](key);
}

template<class K, class V, class KeyEqual>
V &ConcurrentLinkedList<K, V, KeyEqual>::at(const K &key) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return linkedList->at(key);
}

template<class K, class V, class KeyEqual>
bool ConcurrentLinkedList<K, V, KeyEqual>::contains(const K &key) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return linkedList->contains(key);
}

template<class K, class V, class KeyEqual>
std::string ConcurrentLinkedList<K, V, KeyEqual>::getName() const {
    return className;
}

template<class K, class V, class KeyEqual>
Node<K, V> *ConcurrentLinkedList<K, V, KeyEqual>::find(const K &key) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return linkedList->find(key);
}

template<class K, class V, class KeyEqual>
bool ConcurrentLinkedList<K, V, KeyEqual>::isEmpty() const {
    return linkedList->isEmpty();
}

template<class K, class V, class KeyEqual>
size_t ConcurrentLinkedList<K, V, KeyEqual>::size() const {
    return linkedList->size();
}

#endif //CELERAONEEX2_CONCURRENTLINKEDLIST_H
