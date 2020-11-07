#include "strhelp.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

const string WHITESPACE = " \n\r\t\f\v";

bool found(size_t pos) { return pos != string::npos; }

string strBetween(const string &s, size_t start, size_t end) {
    return s.substr(start + 1, end - start - 1);
}

string strBefore(const string &s, size_t end) { return s.substr(0, end); }

string strAfter(const string &s, size_t start) { return s.substr(start + 1); }

string ltrim(const string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return found(start) ? s.substr(start) : "";
}

string rtrim(const string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return found(end) ? s.substr(0, end + 1) : "";
}

string trimWhitespace(const string &s) { return rtrim(ltrim(s)); }

vector<string> split(const string &s, string delim) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(delim);
    while (found(end)) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    tokens.push_back(s.substr(start, end));
    return tokens;
}