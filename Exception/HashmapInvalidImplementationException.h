//
// Created by Fear on 10/10/15.
//

#ifndef CONCURRENTHASHMAP_HASHIMPLEMENTATIONEXCEPTION_H
#define CONCURRENTHASHMAP_HASHIMPLEMENTATIONEXCEPTION_H

#include <exception>

class HashmapInvalidImplementationException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Your hashmap implementation is not correct.";
    }
};

#endif //CELERAONEEX2_HASHIMPLEMENTATIONEXCEPTION_H
