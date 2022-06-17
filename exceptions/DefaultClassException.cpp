#include "DefaultClassException.h"

DefaultClassException::DefaultClassException(std::string class_name, std::string method):
class_name(std::move(class_name)), method(std::move(method)) {}

std::string DefaultClassException::getError() {
    std::string main_msg = "Some problems have appeared into " + method + " method of " +  class_name + " class.";
    return main_msg;
}