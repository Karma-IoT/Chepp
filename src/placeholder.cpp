#include "placeholder.h"

string &placeholder::replace(string &str) {
    if (auto prefix = string::npos;
            str.find("$#<") != string::npos) {
        auto suffix = str.find(">");
        auto express = str.substr(prefix + 3,suffix - prefix - 3);
        auto sem0 = string::npos;
        auto sem1 = string::npos;
        vector<string> exp;
        do {
            sem0 = sem1;
            sem1 = express.find("|");
            exp.push_back(express.substr(sem0,sem1 - sem0));
        } while (sem != npos);
        // deal vector
        str = this -> vars[str];
        for (int i = 1; i != exp.size(); i++) {
            auto op = this -> ops;
            str = op(str);
        }
    }
    return str;
}

void placeholder::set_var(const string &name,const string &val) {
    this -> vars[name] = val;
}

void placeholder::set_op(const string &name,const function<string&(string&)> &op) {
    this -> ops[name] = op;
}

