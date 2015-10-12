//
// Created by Fear on 10/10/15.
//

#ifndef CELERAONEEX2_TestCase2_H
#define CELERAONEEX2_TestCase2_H

#include <thread>
#include "ITestCase.h"

class TestCase2 : public ITestCase {
public:
    TestCase2(){};
    string getClassName() const;
protected:
    const unsigned long NumThread = 30;
    const unsigned long NumTry = 10;

    static void threadRun(HashmapType &hashmap, VectorType &instructions);
    double runCheck(HashmapType &hashmap);
    double runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions);
};

string TestCase2::getClassName() const {
    return "Testcase 2(Check concurrency-Insert)";
}

void TestCase2::threadRun(HashmapType &hashmap, VectorType &instructions) {
    RunnerType runner;
    runner.run(hashmap, instructions);
}

double TestCase2::runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions) {
    auto start = std::chrono::system_clock::now();

    vector<thread> threads(NumThread);
    threads.clear();

    //Run threads concurrently
    for (unsigned long numThread = 0; numThread < NumThread; ++numThread) {
        threads.push_back(std::thread(threadRun, std::ref(hashmap), std::ref(vecInstructions.at(numThread))));
    }

    //Wait for all threads until finishing
    for (auto &thread : threads) thread.join();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> wallClockTime = end - start;
    return wallClockTime.count();
}

double TestCase2::runCheck(HashmapType &hashmap) {
    TestCreator testCreator;
    VectorType minifiedInstructions;
    double time = 0;

    for (unsigned long numTry = 0; numTry < NumTry; ++numTry) {
        vector<VectorType> vecInstructions;
        hashmap.clear();
        minifiedInstructions.clear();

        //Create distributed instructions for threads
        for (unsigned long numThread = 0; numThread < NumThread; ++numThread) {
            testCreator.reset();
            testCreator.createPutInstructions(1000, 100);

            vecInstructions.push_back(testCreator.getInstructions());
        }

        time += runWithTimer(hashmap, vecInstructions);

        //Check size
        minifiedInstructions = testUtil.getMinifiedInstructions(vecInstructions);
        if (minifiedInstructions.size() != hashmap.size()) {
            throw HashmapConcurrentException();
        }
    }

    return time;
}

#endif //CELERAONEEX2_TestCase2_H