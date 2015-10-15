//
// Created by Fear on 10/11/15.
//

#ifndef CONCURRENTHASHMAP_TESTCASECREATOREXCEPTION_H
#define CONCURRENTHASHMAP_TESTCASECREATOREXCEPTION_H

#include <exception>

class TestCaseCreatorException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Key not found.";
    }
};


#endif
