//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_SIMPLECONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_SIMPLECONCURRENTHASHMAP_H

#include <mutex>
#include "SimpleHashmap.h"

template<class K, class V, class HASH = std::hash<K>, class KeyEqual = std::equal_to<K>>
class SimpleConcurrentHashmap : public IHashmap<K, V, HASH, KeyEqual> {
public:
    SimpleConcurrentHashmap(size_t _segmentSize = IHashmap<K, V, HASH, KeyEqual>::DEFAULT_SEGMENT_SIZE);
    ~SimpleConcurrentHashmap();

    void put(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    V &at(const K &key) const;
    bool contains(const K &key) const;

    std::string getName() const;

    void clear();

    bool isEmpty() const;

    size_t size() const;
protected:
    mutable std::recursive_mutex _lock;

    const std::string className = "Concurrent Simple Hash Map";
    SimpleHashmap<K, V> *simpleHashmap;
};

template<class K, class V, class HASH, class KeyEqual>
SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::SimpleConcurrentHashmap(size_t _segmentSize) : IHashmap<K, V, HASH, KeyEqual>(_segmentSize) {
    simpleHashmap = new SimpleHashmap<K, V>(_segmentSize);
}

template<class K, class V, class HASH, class KeyEqual>
SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::~SimpleConcurrentHashmap() {
    delete simpleHashmap;
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::put(const K &key, const V &value) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    simpleHashmap->put(key, value);
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::remove(const K &key) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    simpleHashmap->remove(key);
}

template<class K, class V, class HASH, class KeyEqual>
V &SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::operator[](const K &key) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return simpleHashmap->operator[](key);
}

template<class K, class V, class HASH, class KeyEqual>
V &SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::at(const K &key) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return simpleHashmap->at(key);
}

template<class K, class V, class HASH, class KeyEqual>
bool SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::contains(const K &key) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return simpleHashmap->contains(key);
}

template<class K, class V, class HASH, class KeyEqual>
std::string SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::getName() const {
    return className;
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::clear() {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    simpleHashmap->clear();
}

template<class K, class V, class HASH, class KeyEqual>
bool SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::isEmpty() const {
    return simpleHashmap->isEmpty();
}

template<class K, class V, class HASH, class KeyEqual>
size_t SimpleConcurrentHashmap<K, V, HASH, KeyEqual>::size() const {
    return simpleHashmap->size();
}

#endif
