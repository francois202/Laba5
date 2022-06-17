#ifndef MATRIX_DEFAULTCLASS_EXCEPTION_H
#define MATRIX_DEFAULTCLASS_EXCEPTION_H

#include <string>

class DefaultClassException: public std::exception {

public:
    DefaultClassException(std::string class_name, std::string method);
    std::string getError();

protected:
    std::string class_name;
    std::string method;
};

#endif //MATRIX_DEFAULT_CLASS_EXCEPTION_H
