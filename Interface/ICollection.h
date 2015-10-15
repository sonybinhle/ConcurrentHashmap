//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_ICOLLECTION_H
#define CONCURRENTHASHMAP_ICOLLECTION_H

#include <functional>
#include <string>

template<class K, class V, class KeyEqual = std::equal_to<K>>
class ICollection {
public:
    ICollection();
    ~ICollection();

    virtual void put(const K &key, const V &value) = 0;
    virtual void remove(const K &key) = 0;
    virtual V &operator[](const K &key) = 0;
    virtual V &at(const K &key) const = 0;
    virtual bool contains(const K &key) const = 0;
    virtual std::string getName() const = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() const;
    virtual size_t size() const;
protected:
    size_t total;
};

template<class K, class V, class KeyEqual>
ICollection<K, V, KeyEqual>::ICollection() {
    total = 0;
}

template<class K, class V, class KeyEqual>
ICollection<K, V, KeyEqual>::~ICollection() {
    total = 0;
}

template<class K, class V, class KeyEqual>
bool ICollection<K, V, KeyEqual>::isEmpty() const {
    return total == 0;
}

template<class K, class V, class KeyEqual>
size_t ICollection<K, V, KeyEqual>::size() const {
    return total;
}

#endif
