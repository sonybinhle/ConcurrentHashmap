//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_IHASHMAP_H
#define CONCURRENTHASHMAP_IHASHMAP_H

#include "ICollection.h"

template<class K, class V, class HASH = std::hash<K>, class KeyEqual = std::equal_to<K>>
class IHashmap : public ICollection<K, V, KeyEqual>{
public:
    static const size_t DEFAULT_SEGMENT_SIZE = 16;

    IHashmap(const size_t _segmentSize = DEFAULT_SEGMENT_SIZE);
    ~IHashmap();
protected:
    static const size_t MAX_SEGMENT_SIZE = 1 << 16;

    size_t segmentSize;
    size_t hash(const K &key) const;
};

template<class K, class V, class HASH, class KeyEqual>
IHashmap<K, V, HASH, KeyEqual>::IHashmap(const size_t _segmentSize) {
    if (_segmentSize > MAX_SEGMENT_SIZE) {
        segmentSize = MAX_SEGMENT_SIZE;
    } else {
        segmentSize = _segmentSize;
    }
}

template<class K, class V, class HASH, class KeyEqual>
IHashmap<K, V, HASH, KeyEqual>::~IHashmap() {
}

template<class K, class V, class HASH, class KeyEqual>
size_t IHashmap<K, V, HASH, KeyEqual>::hash(const K &key) const {
    return  HASH()(key) % segmentSize;
}

#endif
