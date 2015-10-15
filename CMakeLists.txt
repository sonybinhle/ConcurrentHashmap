cmake_minimum_required(VERSION 3.3)
project(ConcurrentHashmap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp 1.SimpleHashmap/SimpleHashmap.h Exception/KeyNotFoundException.h Interface/ICollection.h Test/TestCreator.h Test/TestRunner.h Test/Instruction.h Test/TestCase1.h Test/TestCase2.h Test/TestCase3.h Test/TestCase4.h Exception/HashmapInvalidImplementationException.h Test/TestUtil.h Exception/HashmapConcurrentException.h 1.SimpleHashmap/SimpleConcurrentHashmap.h Test/TestCase4.h Test/ITestCase.h 2.LinkedListHashmap/LinkedListHashmap.h 2.LinkedListHashmap/LinkedList.h Interface/IHashmap.h Interface/ILinkedList.h Interface/Node.h 2.LinkedListHashmap/ConcurrentLinkedList.h Test/TestCase5.h Exception/TestCaseCreatorException.h)
add_executable(ConcurrentHashmap ${SOURCE_FILES})