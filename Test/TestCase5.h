//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_TESTCASE5_H
#define CONCURRENTHASHMAP_TESTCASE5_H

#include <thread>
#include "ITestCase.h"

class TestCase5 : public ITestCase {
public:
    TestCase5() { };

    string getClassName() const;

protected:
    const unsigned long NumThread = 30;
    const unsigned long NumTry = 10;

    static void threadRun(HashmapType &hashmap, VectorType &instructions);

    double runCheck(HashmapType &hashmap);

    double runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions, VectorType &removeInstructions);
};

double TestCase5::runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions,
                               VectorType &removeInstructions) {
    auto start = std::chrono::system_clock::now();

    vector<thread> threads(NumThread);
    threads.clear();
    //Run one At thread and Insert threads concurrently
    thread atThread(threadRun, ref(hashmap), ref(removeInstructions));
    for (unsigned long numThread = 0; numThread < NumThread; ++numThread) {
        threads.push_back(thread(threadRun, ref(hashmap), ref(vecInstructions.at(numThread))));
    }

    //Wait for all threads until finishing
    atThread.join();
    for (auto &thread : threads) thread.join();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> wallClockTime = end - start;
    return wallClockTime.count();
}


string TestCase5::getClassName() const {
    return "Testcase 5(Check concurrency-Insert-Delete)";
}

void TestCase5::threadRun(HashmapType &hashmap, VectorType &instructions) {
    RunnerType runner;
    runner.run(hashmap, instructions);
}

double TestCase5::runCheck(HashmapType &hashmap) {
    TestCreator testCreator;
    VectorType minifiedInstructions, instructions, removeInstructions, appendInstructions;
    vector<thread> threads(NumThread);
    double time = 0;

    for (unsigned long numTry = 0; numTry < NumTry; ++numTry) {
        vector<VectorType> vecInstructions;
        hashmap.clear();
        threads.clear();
        minifiedInstructions.clear();
        removeInstructions.clear();

        //Create insert Instructions
        instructions = testCreator.createPutInstructions(10000, 30000).getInstructions();
        threadRun(hashmap, instructions);
        removeInstructions = testCreator.createRemoveInstructions(100, true).getInstructions();
        minifiedInstructions = testUtil.getMinifiedInstructions(instructions);

        //Create distributed insert instructions for threads
        for (unsigned long numThread = 0; numThread < NumThread; ++numThread) {
            testCreator.reset();
            testCreator.createPutInstructions(minifiedInstructions, 100, 100000);

            vecInstructions.push_back(testCreator.getInstructions());
        }

        time += runWithTimer(hashmap, vecInstructions, removeInstructions);

        //Check size, include all instructions
        minifiedInstructions = testUtil.getMinifiedInstructions(vecInstructions);
        if (minifiedInstructions.size() != hashmap.size()) {
            throw HashmapConcurrentException();
        }
    }
    return time;
}

#endif
