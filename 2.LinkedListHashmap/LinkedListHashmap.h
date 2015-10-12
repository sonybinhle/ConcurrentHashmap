//
// Created by Fear on 10/11/15.
//

#ifndef CELERAONEEX2_LINKEDLISTHASHMAP_H
#define CELERAONEEX2_LINKEDLISTHASHMAP_H

#include "../Interface/IHashmap.h"
#include "LinkedList.h"
#include "ConcurrentLinkedList.h"

template<class K, class V, class HASH = std::hash<K>, class KeyEqual = std::equal_to<K>>
class LinkedListHashmap : public IHashmap<K, V, HASH, KeyEqual> {
public:
    LinkedListHashmap(size_t _segmentSize = IHashmap<K, V, HASH, KeyEqual>::DEFAULT_SEGMENT_SIZE, bool _concurrent = false);
    ~LinkedListHashmap();

    void put(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    V &at(const K &key) const;
    bool contains(const K &key) const;

    virtual std::string getName() const;
    virtual void clear();
    virtual bool isEmpty() const;
    virtual size_t size() const;
protected:
    const std::string className = "Linkedlist Hash Map";
    const bool concurrent;
    ILinkedList<K, V, KeyEqual> **segments;

    void initSegments();
    void resetSegments();
};

template<class K, class V, class HASH, class KeyEqual>
LinkedListHashmap<K, V, HASH, KeyEqual>::LinkedListHashmap(size_t _segmentSize, bool _concurrent)
        : concurrent(_concurrent), IHashmap<K, V, HASH, KeyEqual>(_segmentSize) {
    initSegments();
}

template<class K, class V, class HASH, class KeyEqual>
LinkedListHashmap<K, V, HASH, KeyEqual>::~LinkedListHashmap() {
    resetSegments();
}

template<class K, class V, class HASH, class KeyEqual>
void LinkedListHashmap<K, V, HASH, KeyEqual>::initSegments() {
    segments = new ILinkedList<K, V, KeyEqual>*[this->segmentSize];
    if (concurrent) {
        for (size_t i = 0; i < this->segmentSize; i++) {
            segments[i] = new ConcurrentLinkedList<K, V, KeyEqual>();
        }
    } else {
        for (size_t i = 0; i < this->segmentSize; i++) {
            segments[i] = new LinkedList<K, V, KeyEqual>();
        }
    }
}

template<class K, class V, class HASH, class KeyEqual>
void LinkedListHashmap<K, V, HASH, KeyEqual>::resetSegments() {
    for (size_t i = 0; i < this->segmentSize; i++) {
        segments[i]->clear();
    }
    delete[] segments;
}

template<class K, class V, class HASH, class KeyEqual>
void LinkedListHashmap<K, V, HASH, KeyEqual>::put(const K &key, const V &value) {
    size_t hashcode = this->hash(key);
    ILinkedList<K, V, KeyEqual> *curr = segments[hashcode];
    curr->put(key, value);
}

template<class K, class V, class HASH, class KeyEqual>
void LinkedListHashmap<K, V, HASH, KeyEqual>::remove(const K &key) {
    size_t hashcode = this->hash(key);
    ILinkedList<K, V, KeyEqual> *curr = segments[hashcode];
    curr->remove(key);
}

template<class K, class V, class HASH, class KeyEqual>
V &LinkedListHashmap<K, V, HASH, KeyEqual>::operator[](const K &key) {
    size_t hashcode = this->hash(key);
    ILinkedList<K, V, KeyEqual> *curr = segments[hashcode];

    return curr->operator[](key);
}

template<class K, class V, class HASH, class KeyEqual>
V &LinkedListHashmap<K, V, HASH, KeyEqual>::at(const K &key) const {
    size_t hashcode = this->hash(key);
    ILinkedList<K, V, KeyEqual> *curr = segments[hashcode];

    return curr->at(key);
}

template<class K, class V, class HASH, class KeyEqual>
bool LinkedListHashmap<K, V, HASH, KeyEqual>::contains(const K &key) const {
    size_t hashcode = this->hash(key);
    ILinkedList<K, V, KeyEqual> *curr = segments[hashcode];

    return curr->find(key) != nullptr;
}

template<class K, class V, class HASH, class KeyEqual>
std::string LinkedListHashmap<K, V, HASH, KeyEqual>::getName() const {
    if (concurrent) {
        return "Concurrent " + className;
    } else {
        return className;
    }
}

template<class K, class V, class HASH, class KeyEqual>
void LinkedListHashmap<K, V, HASH, KeyEqual>::clear() {
    resetSegments();
    initSegments();
    this->total = 0;
}

template<class K, class V, class HASH, class KeyEqual>
bool LinkedListHashmap<K, V, HASH, KeyEqual>::isEmpty() const {
    for (size_t i = 0; i < this->segmentSize; i++) {
        if (segments[i]->size() > 0)
            return false;
    }
    return true;
}

template<class K, class V, class HASH, class KeyEqual>
size_t LinkedListHashmap<K, V, HASH, KeyEqual>::size() const {
    size_t total = 0;
    for (size_t i = 0; i < this->segmentSize; i++) {
        total = total + segments[i]->size();
    }
    return total;
}

#endif //CELERAONEEX2_LINKEDLISTHASHMAP_H
