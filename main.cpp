#include <iostream>
#include "Test/TestCase1.h"
#include "Test/TestCase2.h"
#include "Test/TestCase3.h"
#include "Test/TestCase4.h"
#include "Test/TestCase5.h"
#include "1.SimpleHashmap/SimpleHashmap.h"
#include "1.SimpleHashmap/SimpleConcurrentHashmap.h"
#include "2.LinkedListHashmap/LinkedListHashmap.h"
using namespace std;

int main ()
{
    TestUtil testUtil;
    size_t size = IHashmap<int, int>::DEFAULT_SEGMENT_SIZE;
    try {
        SimpleHashmap<int, int> simpleHashmap(size);
        SimpleConcurrentHashmap<int, int>  simpleConcurrentHashmap(size);
        LinkedListHashmap<int, int> linkedListHashmap(size);
        LinkedListHashmap<int, int> concurrentLinkedListHashmap(size, true);
        TestCase1 test1;
        TestCase2 test2;
        TestCase3 test3;
        TestCase4 test4;
        TestCase5 test5;

        test1.check(simpleHashmap);
        test1.check(linkedListHashmap);
        test1.check(simpleConcurrentHashmap);
        test1.check(concurrentLinkedListHashmap);

        test2.check(simpleHashmap);
        test2.check(linkedListHashmap);
        test2.check(simpleConcurrentHashmap);
        test2.check(concurrentLinkedListHashmap);

        //Enable this line may return exit code 11, EXC_BAD_ACCESS, which can not be catched
        //Print error message instead
        //test3.check(simpleHashmap);
        //test3.check(linkedListHashmap);
        testUtil.printFailureMsg("Testcase 3(Check concurrency-Delete)", "Simple Hash Map", "Conccurency implementation failed-Bad Access.");
        testUtil.printFailureMsg("Testcase 3(Check concurrency-Delete)", "Linked List Hash Map", "Conccurency implementation failed-Bad Access.");
        test3.check(simpleConcurrentHashmap);
        test3.check(concurrentLinkedListHashmap);

        test4.check(simpleHashmap);
        test4.check(linkedListHashmap);
        test4.check(simpleConcurrentHashmap);
        test4.check(concurrentLinkedListHashmap);

        //Enable this line may return exit code 11, EXC_BAD_ACCESS, which can not be catched
        //Print error message instead
        //test5.check(simpleHashmap);
        //test5.check(linkedListHashmap);
        testUtil.printFailureMsg("Testcase 5(Check concurrency-Insert-Delete)", "Simple Hash Map", "Conccurency implementation failed-Bad Access.");
        testUtil.printFailureMsg("Testcase 5(Check concurrency-Insert-Delete)", "Linked List Hash Map", "Conccurency implementation failed-Bad Access.");
        test5.check(simpleConcurrentHashmap);
        test5.check(concurrentLinkedListHashmap);

    } catch (exception &e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}