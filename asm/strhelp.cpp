#include "strhelp.h"
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

bool found(unsigned int pos) { return pos != string::npos; }

string strBetween(const string &s, unsigned int start, unsigned int end) {
    return s.substr(start + 1, end - start - 1);
}

string strBefore(const string &s, unsigned int end) { return s.substr(0, end); }

string strAfter(const string &s, unsigned int start) {
    return s.substr(start + 1);
}
