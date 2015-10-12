//
// Created by Fear on 10/10/15.
//

#ifndef CELERAONEEX2_TESTCASE1_H
#define CELERAONEEX2_TESTCASE1_H

#include "ITestCase.h"
#include "../Interface/IHashmap.h"

class TestCase1 : public ITestCase {
public:
    TestCase1(){};
    string getClassName() const;
protected:
    double runCheck(HashmapType &hashmap);
    double runWithTimer(HashmapType &hashmap, VectorType &instructions);
};

string TestCase1::getClassName() const {
    return "Testcase 1(Check correctness)";
}

double TestCase1::runWithTimer(HashmapType &hashmap, VectorType &instructions) {
    RunnerType runner;
    auto start = std::chrono::system_clock::now();

    runner.run(hashmap, instructions);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> wallClockTime = end - start;
    return wallClockTime.count();
}

double TestCase1::runCheck(HashmapType &hashmap) {
    TestCreator testCreator;
    VectorType instructions, minifiedInstructions;
    double time = 0;

    //Test 1: Put only
    hashmap.clear();
    instructions = testCreator
            .createPutInstructions()
            .createAtInstructions()
            .getInstructions();
    minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    runWithTimer(hashmap, instructions);

    if (minifiedInstructions.size() != hashmap.size()) {
        throw HashmapInvalidImplementationException();
    }

    for (InstructionType &in : minifiedInstructions) {
        if (hashmap.at(in.key) != in.value) {
            throw HashmapInvalidImplementationException();
        }
    }

    //Test 2: Put and delete all
    hashmap.clear();
    instructions = testCreator
            .createRemoveInstructions()
            .getInstructions();
    minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    time += runWithTimer(hashmap, instructions);

    if (!hashmap.isEmpty()) {
        throw HashmapInvalidImplementationException();
    }

    for (InstructionType &in : minifiedInstructions) {
        if (hashmap.at(in.key) != in.value) {
            throw HashmapInvalidImplementationException();
        }
    }

    //Test 3: Append Put instructions with a large data
    hashmap.clear();
    instructions = testCreator
            .createPutInstructions(10000, 2000, 30000)
            .createAtInstructions()
            .getInstructions();
    minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    time += runWithTimer(hashmap, instructions);

    if (minifiedInstructions.size() != hashmap.size()) {
        throw HashmapInvalidImplementationException();
    }

    for (InstructionType &in : minifiedInstructions) {
        if (hashmap.at(in.key) != in.value) {
            throw HashmapInvalidImplementationException();
        }
    }

    //Test 4: Append Delete all
    hashmap.clear();
    instructions = testCreator.createRemoveInstructions().getInstructions();
    minifiedInstructions = testUtil.getMinifiedInstructions(instructions);
    time += runWithTimer(hashmap, instructions);

    if (minifiedInstructions.size() != hashmap.size()) {
        throw HashmapInvalidImplementationException();
    }

    for (InstructionType &in : minifiedInstructions) {
        if (hashmap.at(in.key) != in.value) {
            throw HashmapInvalidImplementationException();
        }
    }

    return time;
}

#endif //CELERAONEEX2_TESTCASE1_H
