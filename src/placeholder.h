#ifndef _PLACEHOLDER_H
#define _PLACEHOLDER_H

#include <string>
#include <functional>
#include <map>

using namespace std;

namespace chepp {

class placeholder {
public:
    placeholder() = default;
    placeholder(const placeholder &) = default;
    ~placeholder() = default;
public:
    void set_var(const string &name,const string &val);
    void set_op(const string &name,const function<string&(string&)> &op);
    string &replace(string &str);
private:
    map<string,string> vars;
    map<string,function<string&(string&)>> ops;
};

}

#endif
