//
// Created by Fear on 10/11/15.
//

#ifndef CELERAONEEX2_TESTCASECREATOREXCEPTION_H
#define CELERAONEEX2_TESTCASECREATOREXCEPTION_H

#include <exception>

class TestCaseCreatorException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Key not found.";
    }
};


#endif //CELERAONEEX2_TESTCASECREATOREXCEPTION_H
