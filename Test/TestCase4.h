//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_TESTCASE4_H
#define CONCURRENTHASHMAP_TESTCASE4_H

#include <thread>
#include "ITestCase.h"

class TestCase4 : public ITestCase {
public:
    TestCase4() { };

    string getClassName() const;

protected:
    const unsigned long NumThread = 30;
    const unsigned long NumTry = 10;

    static void threadRun(HashmapType &hashmap, VectorType &instructions);

    double runCheck(HashmapType &hashmap);

    double runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions, VectorType &atInstructions);
};

double TestCase4::runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions, VectorType &atInstructions) {
    auto start = std::chrono::system_clock::now();

    vector<thread> threads(NumThread);
    threads.clear();
    //Run one At thread and Insert threads concurrently
    thread atThread(threadRun, ref(hashmap), ref(atInstructions));
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


string TestCase4::getClassName() const {
    return "Testcase 4(Check concurrency-Insert-Lookup)";
}

void TestCase4::threadRun(HashmapType &hashmap, VectorType &instructions) {
    RunnerType runner;
    runner.run(hashmap, instructions);
}

double TestCase4::runCheck(HashmapType &hashmap) {
    TestCreator testCreator;
    VectorType minifiedInstructions, instructions, atInstructions, appendInstructions;
    double time = 0;

    for (unsigned long numTry = 0; numTry < NumTry; ++numTry) {
        vector<VectorType> vecInstructions;
        hashmap.clear();
        minifiedInstructions.clear();
        atInstructions.clear();

        //Create insert Instructions
        instructions = testCreator.createPutInstructions(10000, 4000).getInstructions();
        threadRun(hashmap, instructions);
        atInstructions = testCreator.createAtInstructions(true).getInstructions();
        minifiedInstructions = testUtil.getMinifiedInstructions(instructions);


        //Create distributed insert instructions for threads
        for (unsigned long numThread = 0; numThread < NumThread; ++numThread) {
            testCreator.reset();
            testCreator.createPutInstructions(1000, 10000);

            vecInstructions.push_back(testCreator.getInstructions());
        }

        time += runWithTimer(hashmap, vecInstructions, atInstructions);

        //Check size, include all instructions
        appendInstructions = testUtil.getMinifiedInstructions(vecInstructions);
        minifiedInstructions.insert(minifiedInstructions.end(), appendInstructions.begin(), appendInstructions.end());
        minifiedInstructions = testUtil.getMinifiedInstructions(minifiedInstructions);
        if (minifiedInstructions.size() != hashmap.size()) {
            throw HashmapConcurrentException();
        }
    }
    return time;
}

#endif
