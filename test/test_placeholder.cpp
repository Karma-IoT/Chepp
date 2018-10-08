#include <filesystem>
#include <iostream>

#include "placeholder.h"

using namespace std;
using namespace chepp;

int main() {
    placeholder p;
    p.set_op("set",[&p](string &str)->string &{
        return p.set(str);
    });
    
    string buf("sdafsf$#<test = hello | set>");
    cout << p.eval(buf) << endl;
    cout << p.vars["test"] << endl;
    return 0;
}
