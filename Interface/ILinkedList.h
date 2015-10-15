//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_ILinkedList_H
#define CONCURRENTHASHMAP_ILinkedList_H

#include "../Interface/ICollection.h"
#include "../Interface/Node.h"

template<class K, class V, class KeyEqual = std::equal_to<K>>
class ILinkedList : public ICollection<K, V, KeyEqual> {
public:
    ILinkedList();
    ~ILinkedList();

    virtual void put(const K &key, const V &value) = 0;
    virtual void remove(const K &key) = 0;
    virtual V &operator[](const K &key) = 0;
    virtual V &at(const K &key) const = 0;
    virtual bool contains(const K &key) const = 0;

    virtual std::string getName() const = 0;
    virtual void clear() = 0;
    virtual Node<K, V> *find(const K &key) const = 0;
};

template<class K, class V, class KeyEqual>
ILinkedList<K, V, KeyEqual>::ILinkedList() : ICollection<K, V, KeyEqual>() {
}

template<class K, class V, class KeyEqual>
ILinkedList<K, V, KeyEqual>::~ILinkedList() {
}

#endif
