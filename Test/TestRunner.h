//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_TESTRUNNER_H
#define CONCURRENTHASHMAP_TESTRUNNER_H

#include "TestCreator.h"
#include "../Interface/ICollection.h"

template <class K, class V>
class TestRunner {
public:
    void run(ICollection<K, V> &hashmap, vector<Instruction<K, V>> &instructions);
};

template <class K, class V>
void TestRunner<K, V>::run(ICollection<K, V> &hashmap, vector<Instruction<K, V>> &instructions) {
    for (Instruction<K, V> &instruction : instructions )
    {
        switch (instruction.type) {
            case InstructionEnum::PUT:
                hashmap.put(instruction.key, instruction.value);
                break;
            case InstructionEnum::REMOVE:
                hashmap.remove(instruction.key);
                break;
            case InstructionEnum::AT:
                hashmap.at(instruction.key);
                break;
        }
    }
}

#endif //CELERAONEEX2_TESTRUNNER_H
