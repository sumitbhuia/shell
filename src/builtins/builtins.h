// Declaration of built-in functions

#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
std::string handleEcho(const std::string &args);
std::string handleExit(const std::string &);
std::string handleType(const std::string &keyword);
std::string handlePWD(const std::string &);
std::string handleCD(const std::string &args);

#endif
