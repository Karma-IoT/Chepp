#include "placeholder.h"

#include "utils.h"

namespace chepp {
    
string &placeholder::eval(string &str) {
    auto prefix = string::npos;
    while ((prefix = str.find("$#<")) != string::npos) {
        auto suffix = str.find(">",prefix + 3);
        auto express = str.substr(prefix + 3,suffix - (prefix + 3));
        auto exp = split(express, "|");
        auto buffer = trim(exp[0]);
        if (buffer.empty()) {
            buffer = "";
        } else if (buffer[0] == '$') {
            buffer = vars[trim(buffer).erase(0,1)];
        }
        for (int i = 1; i != exp.size(); i++) {
            auto op = this -> ops[trim(exp[i])];
            if (op) {
                buffer = op(buffer);
            }
        }
        str = str.replace(prefix,suffix - prefix + 1,buffer);
    }
    return str;
}

void placeholder::set_var(const string &name,const string &val) {
    this -> vars[name] = val;
}

void placeholder::set_op(const string &name,const function<string&(string&)> &op) {
    this -> ops[name] = op;
}

string &placeholder::set(string &str) {
    auto vec = split(str,"=");
    this -> set_var(trim(vec[0]), trim(vec[1]));
    str = "";
    return str;
}

}
