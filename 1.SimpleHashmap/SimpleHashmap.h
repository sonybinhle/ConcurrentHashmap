//
// Created by Fear on 10/9/15.
//

#ifndef CONCURRENTHASHMAP_HASHMAP_H
#define CONCURRENTHASHMAP_HASHMAP_H

#include "../Interface/IHashmap.h"
#include "../Exception/KeyNotFoundException.h"

template<class K, class V, class HASH = std::hash<K>, class KeyEqual = std::equal_to<K>>
class SimpleHashmap : public IHashmap<K, V, HASH, KeyEqual> {
public:
    SimpleHashmap(size_t _segmentSize = IHashmap<K, V, HASH, KeyEqual>::DEFAULT_SEGMENT_SIZE);

    virtual ~SimpleHashmap();

    void put(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    V &at(const K &key) const;
    bool contains(const K &key) const;

    std::string getName() const;

    void clear();
protected:
    struct Node {
        Node(Node *_next, const K &_key, const V &_value) {
            key = _key;
            value = _value;
            next = _next;
        }
        K key;
        V value;
        Node *next;
    };
    const std::string className = "Simple Hash Map";
    Node **segments;

    void initSegments();
    void resetSegments();
    Node *insert(const K &key, const V &value);
    Node *find(const K &key) const;
};

template<class K, class V, class HASH, class KeyEqual>
SimpleHashmap<K, V, HASH, KeyEqual>::SimpleHashmap(size_t _segmentSize) : IHashmap<K, V, HASH, KeyEqual>(_segmentSize) {
    initSegments();
}

template<class K, class V, class HASH, class KeyEqual>
SimpleHashmap<K, V, HASH, KeyEqual>::~SimpleHashmap() {
    resetSegments();
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleHashmap<K, V, HASH, KeyEqual>::initSegments() {
    segments = new Node*[this->segmentSize];

    for (size_t i = 0; i < this->segmentSize; i++) {
        segments[i] = nullptr;
    }
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleHashmap<K, V, HASH, KeyEqual>::resetSegments() {
    for (size_t i = 0; i < this->segmentSize; i++) {
        Node *curr = segments[i];

        while (curr != nullptr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
    delete[] segments;
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleHashmap<K, V, HASH, KeyEqual>::put(const K &key, const V &value) {
    Node *curr = find(key);

    if (curr == nullptr) {
        insert(key, value);
    } else {
        curr->value = value;
    }
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleHashmap<K, V, HASH, KeyEqual>::remove(const K &key) {
    size_t hashcode = this->hash(key);
    Node *curr = segments[hashcode];
    Node *prev = nullptr;

    while (curr != nullptr && !KeyEqual()(curr->key, key)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        throw KeyNotFoundException();
    } else {
        if (prev == nullptr) {
            segments[hashcode] = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
        --this->total;
    }
}

template<class K, class V, class HASH, class KeyEqual>
V &SimpleHashmap<K, V, HASH, KeyEqual>::operator[](const K &key) {
    Node *curr = find(key);

    if (curr == nullptr) {
        curr = insert(key, V());
    }

    return curr->value;
}

template<class K, class V, class HASH, class KeyEqual>
V &SimpleHashmap<K, V, HASH, KeyEqual>::at(const K &key) const {
    Node *curr = find(key);

    if (curr == nullptr) {
        throw KeyNotFoundException();
    } else {
        return curr->value;
    }
}

template<class K, class V, class HASH, class KeyEqual>
bool SimpleHashmap<K, V, HASH, KeyEqual>::contains(const K &key) const {
    return find(key) != nullptr;
}

template<class K, class V, class HASH, class KeyEqual>
std::string SimpleHashmap<K, V, HASH, KeyEqual>::getName() const {
    return className;
}

template<class K, class V, class HASH, class KeyEqual>
void SimpleHashmap<K, V, HASH, KeyEqual>::clear() {
    resetSegments();
    initSegments();
    this->total = 0;
}

template<class K, class V, class HASH, class KeyEqual>
typename SimpleHashmap<K, V, HASH, KeyEqual>::Node *SimpleHashmap<K, V, HASH, KeyEqual>::insert(const K &key, const V &value) {
    size_t hashcode = this->hash(key);
    segments[hashcode] = new Node(segments[hashcode], key, value);
    ++this->total;
    return segments[hashcode];
}

template<class K, class V, class HASH, class KeyEqual>
typename SimpleHashmap<K, V, HASH, KeyEqual>::Node *SimpleHashmap<K, V, HASH, KeyEqual>::find(const K &key) const {
    size_t hashcode = this->hash(key);
    Node *curr = segments[hashcode];

    while (curr != nullptr && !KeyEqual()(curr->key, key)) {
        curr = curr->next;
    }

    return curr;
}

#endif
