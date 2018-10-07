#include <filesystem>
#include <iostream>

#include "placeholder.h"

using namespace std;
using namespace chepp;

int main() {
    placeholder p;
    p.set_var("hello", "test");
    p.set_var("hello1", "test1");
    p.set_op("upper",[](string &str) -> string& {
        transform(str.begin(),str.end(),str.begin(),::toupper);
        return str;
    });
    p.set_op("test",[](string &str) -> string& {
        cout << str << endl;
        return str;
    });
    
    string buf("$#<hello | test | upper> $#<hello1 | test >");
    cout << p.replace(buf) << endl;
    return 0;
}