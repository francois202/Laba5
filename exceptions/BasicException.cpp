#include "BasicException.h"


BasicException::BasicException(string msg)  { this->msg = msg; };
BasicException::BasicException() = default;

const char* BasicException::getError() {return this->msg.c_str();}
