#include "trim.h"
using std::string;
const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trimWhitespace(const string &s) { return rtrim(ltrim(s)); }

string stringToken(const string &mainString, const string &delim) {
    unsigned long pos = mainString.find(delim);
    if (pos != string::npos)
        return mainString.substr(pos + 1, mainString.length() - pos - 1);

    return "";
}