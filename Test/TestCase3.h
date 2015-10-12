//
// Created by Fear on 10/10/15.
//

#ifndef CELERAONEEX2_TestCase3_H
#define CELERAONEEX2_TestCase3_H

#include <thread>

class TestCase3 : public ITestCase {
public:
    TestCase3(){};
    string getClassName() const;
protected:
    const unsigned long NumThread = 30;
    const unsigned long NumTry = 10;

    static void threadRun(HashmapType &hashmap, VectorType &instructions);
    double runCheck(HashmapType &hashmap);
    double runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions);
};

double TestCase3::runWithTimer(HashmapType &hashmap, vector<VectorType> &vecInstructions) {
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

string TestCase3::getClassName() const {
    return "Testcase 3(Check concurrency-Delete)";
}

void TestCase3::threadRun(HashmapType &hashmap, VectorType &instructions) {
    RunnerType runner;
    runner.run(hashmap, instructions);
}

double TestCase3::runCheck(HashmapType &hashmap) {
    TestCreator testCreator;
    VectorType instructions, removeInstructions, minifiedInstructions;
    RunnerType runner;
    double time = 0;
    int counter;

    for (unsigned long numTry = 0; numTry < NumTry; ++numTry) {
        vector<VectorType> vecInstructions(NumThread);
        hashmap.clear();
        testCreator.reset();
        instructions.clear();
        removeInstructions.clear();
        minifiedInstructions.clear();

        //Create Put instructions first
        instructions = testCreator.createPutInstructions(10000, 7000, 30000).getInstructions();
        runner.run(hashmap, instructions);

        //Append Remove Instructions and distribute equally to threads
        removeInstructions = testCreator.createRemoveInstructions(100, true).getInstructions();
        counter = 0;
        while (removeInstructions.size() > 0) {
            (vecInstructions[counter]).push_back(removeInstructions.back());
            removeInstructions.pop_back();
            ++counter;
            if (counter >= NumThread) {
                counter = 0;
            }
        }

        time += runWithTimer(hashmap, vecInstructions);

        //Check size
        if (hashmap.size() != 0) {
            throw HashmapConcurrentException();
        }
    }
    return time;
}

#endif //CELERAONEEX2_TestCase3_H
