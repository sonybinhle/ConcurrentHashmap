//
// Created by Fear on 10/9/15.
//

#ifndef CELERAONEEX2_KEYNOTFOUNDEXCEPTION_H
#define CELERAONEEX2_KEYNOTFOUNDEXCEPTION_H

#include <exception>

class KeyNotFoundException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Key not found.";
    }
};


#endif //CELERAONEEX2_KEYNOTFOUNDEXCEPTION_H
