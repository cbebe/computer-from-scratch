#ifndef _TRIM_H_
#define _TRIM_H_

#include <algorithm>
#include <string>

std::string trimWhitespace(const std::string &s);
std::string stringToken(const std::string &mainString,
                        const std::string &delim);

#endif