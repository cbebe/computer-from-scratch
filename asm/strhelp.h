#ifndef _STRHELP_H_
#define _STRHELP_H_

#include <string>

// helper methods for string extraction/manipulation

bool found(size_t pos);

std::string trimWhitespace(const std::string &s);

std::string strBetween(const std::string &s, size_t start, size_t end);
std::string strBefore(const std::string &s, size_t end);
std::string strAfter(const std::string &s, size_t start);

#endif