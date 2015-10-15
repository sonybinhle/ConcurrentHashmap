//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_TESTCREATOR_H
#define CONCURRENTHASHMAP_TESTCREATOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stdlib.h>
#include <time.h>
#include "Instruction.h"
#include "TestUtil.h"
#include "../Exception/TestCaseCreatorException.h"
using namespace std;

class TestCreator {
public:
    typedef Instruction<int, int> InstructionType;
    typedef vector<InstructionType> VectorType;

    TestCreator();
    VectorType getInstructions() const;
    TestCreator &createPutInstructions(const size_t &num = 10, const int &max_key = 10, const int &max_val = 30000, const bool &clear = false);
    TestCreator &createPutInstructions(VectorType &excepted, const size_t &num = 10, const int &max_key = 10, const int &max_val = 30000, const bool &clear = false);
    TestCreator &createRemoveInstructions(size_t percent = 100, const bool &clear = false);
    TestCreator &createAtInstructions(size_t percent = 100, const bool &clear = false);
    void reset();
    void print() const;
private:
    VectorType instructions;
    TestUtil testUtil;
};

TestCreator::TestCreator() {
}

TestCreator::VectorType TestCreator::getInstructions() const {
    return instructions;
}

TestCreator &TestCreator::createPutInstructions(const size_t &num, const int &max_key, const int &max_val, const bool &clear) {
    if (clear) {
        instructions.clear();
    }
    for (size_t i = 0; i < num; i++) {
        TestCreator::InstructionType instruction = TestCreator::InstructionType(InstructionEnum::PUT, rand() % max_key, rand() % max_val);
        instructions.push_back(instruction);
    }
    return *this;
}

TestCreator &TestCreator::createPutInstructions(VectorType &excepted, const size_t &num, const int &max_key, const int &max_val, const bool &clear) {
    if (clear) {
        instructions.clear();
    }
    if (num + excepted.size() >= max_key * 75 / 100) {
        throw TestCaseCreatorException();
    }
    for (size_t i = 0; i < num; i++) {
        while (true) {
            TestCreator::InstructionType instruction = TestCreator::InstructionType(InstructionEnum::PUT, rand() % max_key, rand() % max_val);
            if(std::find(excepted.begin(), excepted.end(), instruction) == excepted.end()) {
                instructions.push_back(instruction);
                break;
            }
        }
    }
    return *this;
}

TestCreator& TestCreator::createRemoveInstructions(size_t percent, const bool &clear) {
    TestCreator::VectorType minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    TestCreator::VectorType removeInstructions;

    if (percent > 100) percent = 100;
    size_t num = minifiedInstructions.size() * percent / 100;

    for (size_t i = 0; i < num; ++i) {
        TestCreator::InstructionType instruction = TestCreator::InstructionType(InstructionEnum::REMOVE, minifiedInstructions.at(i).key, 0);
        removeInstructions.push_back(instruction);
    }

    if (clear) {
        instructions.clear();
    }

    instructions.insert(instructions.end(), removeInstructions.begin(), removeInstructions.end());

    return *this;
}

TestCreator& TestCreator::createAtInstructions(size_t percent, const bool &clear) {
    TestCreator::VectorType minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    TestCreator::VectorType atInstructions;

    if (percent > 100) percent = 100;
    size_t num = minifiedInstructions.size() * percent / 100;

    for (size_t i = 0; i < num; ++i) {
        TestCreator::InstructionType instruction = TestCreator::InstructionType(InstructionEnum::AT, minifiedInstructions.at(i).key, 0);
        atInstructions.push_back(instruction);
    }

    if (clear) {
        instructions.clear();
    }

    instructions.insert(instructions.end(), atInstructions.begin(), atInstructions.end());

    return *this;
}

void TestCreator::print() const {
    for (auto& instruction: instructions) {
        switch (instruction.type) {
            case InstructionEnum::PUT:
                std::cout << "Put" << ": " << instruction.key << ", " << instruction.value << std::endl;
                break;
            case InstructionEnum::AT:
                std::cout << "At" << ": " << instruction.key << std::endl;
                break;
            case InstructionEnum::REMOVE:
                std::cout << "Remove" << ": " << instruction.key << std::endl;
                break;
        }

    }
}

void TestCreator::reset() {
    instructions.clear();
}

#endif
