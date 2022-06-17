#ifndef MATRIX_BASIC_EXCEPTION_H
#define MATRIX_BASIC_EXCEPTION_H

#include <string>

using namespace std;


/**
 * Standard Exception class
 */
class BasicException: public std::exception {
public:
    explicit BasicException(string msg);
    explicit BasicException();
    const char* getError();
private:
    string msg;
};


#endif //MATRIX_BASIC_EXCEPTION_H
