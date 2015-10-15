//
// Created by Fear on 10/9/15.
//

#ifndef CONCURRENTHASHMAP_KEYNOTFOUNDEXCEPTION_H
#define CONCURRENTHASHMAP_KEYNOTFOUNDEXCEPTION_H

#include <exception>

class KeyNotFoundException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Key not found.";
    }
};


#endif
