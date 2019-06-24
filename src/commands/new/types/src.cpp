#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "chest.h"
#include "utils.h"
#include "ecode/src/ecode.h"

using namespace std;
using namespace chepp;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Error! Wrong number of parameters." << endl;
        exit(EXIT_FAILURE);
    }
    string type = argv[1];
    string cls = argv[2];
    string name = string(argv[3]);
    auto proot = find_root();
    chest_t chest(proot / "chest.pro");
    
    
    auto target = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates" / (cls + ".src");

    if(!filesystem::exists(target)) {
        cerr << "Error! Template does not exist." << endl;
        exit(EXIT_FAILURE);
    }
    ecode p;
    p.ops["cast(/,_)"] = [](string &str) -> string & {
        for (auto p = str.begin(); p != str.end(); p++){
            if (*p == '/')
                *p = '_';
        }
        return str;
    };
    p.ops["cast(.,_)"] = [](string &str) -> string & {
        for (auto p = str.begin(); p != str.end(); p++){
            if (*p == '.')
                *p = '_';
        }
        return str;
    };
    p.vars["project.name"] = chest.name;
    p.vars["file.name"] = name;
    
    ifstream ifs(target);
    auto spiled = split(cls,".");
    //auto srcpath = proot / "src/" / (name + "." + spiled[0]);
    auto srcpath = proot / "src/" / name;
    
    p.vars["file.path"] = relative(srcpath,proot / "src");
    
    auto srcdir = srcpath;
    
    if (!filesystem::exists(srcdir.remove_filename()))
        create_directory(srcdir);
    
    
    if (filesystem::exists(srcpath)) {
        cerr << "Error! Target file already exists." << endl;
        exit(EXIT_FAILURE);
    }
    
    ofstream ofs(srcpath);
    string buffer;
    while(!ifs.eof()) {
        getline(ifs,buffer);
        buffer = p.eval(buffer);
        ofs << buffer << endl;
    }
    return 0;
}