#ifndef _STRHELP_H_
#define _STRHELP_H_

#include <string>

// helper methods for string extraction/manipulation

bool found(unsigned int pos);

std::string trimWhitespace(const std::string &s);

std::string strBetween(const std::string &s, unsigned int start,
                       unsigned int end);
std::string strBefore(const std::string &s, unsigned int end);
std::string strAfter(const std::string &s, unsigned int start);

#endif