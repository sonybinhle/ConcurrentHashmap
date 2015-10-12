//
// Created by Fear on 10/10/15.
//

#ifndef CELERAONEEX2_HASHIMPLEMENTATIONEXCEPTION_H
#define CELERAONEEX2_HASHIMPLEMENTATIONEXCEPTION_H

#include <exception>

class HashmapInvalidImplementationException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Your hashmap implementation is not correct.";
    }
};

#endif //CELERAONEEX2_HASHIMPLEMENTATIONEXCEPTION_H
