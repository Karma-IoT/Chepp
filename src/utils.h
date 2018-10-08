#ifndef _UTILS_H
#define _UTILS_H

#include <filesystem>
#include <string>
#include <iostream>

using namespace std;

namespace chepp {
    
bool is_option(const string &argv);

filesystem::path find_root();

void replace_str(string &buffer,const string &search, const string &str);

vector<string> split(const string &express, const string &sep);

string& trim(string &s);

}

#endif
