//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_ITESTCASE_H
#define CONCURRENTHASHMAP_ITESTCASE_H

#include <chrono>
#include "../Interface/ICollection.h"
#include "TestCreator.h"
#include "TestRunner.h"
#include "TestUtil.h"
#include "../Exception/HashmapInvalidImplementationException.h"
#include "../Exception/HashmapConcurrentException.h"

class ITestCase {
public:
    typedef ICollection<int, int> HashmapType;
    typedef TestRunner<int, int> RunnerType;
    typedef Instruction<int, int> InstructionType;
    typedef vector<InstructionType> VectorType;

    void check(HashmapType &hashmap);

    virtual string getClassName() const = 0;

protected:
    TestUtil testUtil;

    virtual double runCheck(HashmapType &hashmap) = 0;
};

void ITestCase::check(ITestCase::HashmapType &hashmap) {
    try {
        double wallClockTime = runCheck(hashmap);
        testUtil.printSuccessMsg(getClassName(), hashmap.getName(), wallClockTime);
    } catch (exception &e) {
        testUtil.printFailureMsg(getClassName(), hashmap.getName(), e.what());
    } catch (...) {
        testUtil.printFailureMsg(getClassName(), hashmap.getName(), "Implementation failed.");
    }

}

#endif
