//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_TESTUTIL_H
#define CONCURRENTHASHMAP_TESTUTIL_H

#include <vector>
#include <set>
#include <iostream>
#include <iomanip>
#include "Instruction.h"
using namespace std;

class TestUtil {
public:
    typedef Instruction<int, int> InstructionType;
    typedef vector<InstructionType> VectorType;
    typedef multiset<int> SetType;

    TestUtil();

    VectorType getMinifiedInstructions(VectorType &instructions);
    VectorType getMinifiedInstructions(vector<VectorType> &vecInstructions);
    void printSuccessMsg(const string &testName, const string &hashName, const double &time) const;
    void printFailureMsg(const string &testName, const string &hashName, const string &exception) const;
};

TestUtil::TestUtil() { }

TestUtil::VectorType TestUtil::getMinifiedInstructions(TestUtil::VectorType &instructions) {
    TestUtil::VectorType minifiedInstructions;
    TestUtil::VectorType::reverse_iterator it = instructions.rbegin();
    SetType visited;
    for (; it != instructions.rend(); ++it) {
        if (visited.find(it->key) == visited.end()) {
            if (it->type == InstructionEnum::PUT) {
                minifiedInstructions.push_back(*it);
            }

            if (it->type != InstructionEnum::AT) {
                visited.insert(it->key);
            }
        }
    }
    return minifiedInstructions;
}

TestUtil::VectorType TestUtil::getMinifiedInstructions(vector<VectorType> &vecInstructions) {
    VectorType instructions;
    for (auto &ins : vecInstructions) {
        instructions.insert(instructions.end(), ins.begin(), ins.end());
    }
    TestUtil::VectorType minifiedInstructions;
    TestUtil::VectorType::reverse_iterator it = instructions.rbegin();
    SetType visited;
    for (; it != instructions.rend(); ++it) {
        if (visited.find(it->key) == visited.end()) {
            if (it->type == InstructionEnum::PUT) {
                minifiedInstructions.push_back(*it);
            }

            if (it->type != InstructionEnum::AT) {
                visited.insert(it->key);
            }
        }
    }
    return minifiedInstructions;
}

void TestUtil::printSuccessMsg(const string &testName, const string &hashName, const double &time) const {
    cout << setw(30) << left << testName << "  :   Passed   :  "  << setw(30) << left << hashName << "  :  time " << fixed << time << endl;
}

void TestUtil::printFailureMsg(const string &testName, const string &hashName, const string &msg) const {
    cerr << setw(30) << left << testName << "  :   Failed   :  "  << setw(30) << left << hashName << "   :   Exception-" << msg << endl;
}

#endif //CELERAONEEX2_TESTUTIL_H
