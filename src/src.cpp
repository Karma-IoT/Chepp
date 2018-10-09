#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "chest.h"
#include "utils.h"
#include "placeholder.h"

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
    placeholder p;
    p.set_op("set",[&p](string &str) -> string & { return p.set(str);});
    p.set_op("upper",[](string &str) -> string & {
        transform(str.begin(),str.end(),str.begin(),::toupper);
        return str;
    });
    p.set_op("cast(/,_)", [](string &str) -> string & {
        for (auto p = str.begin(); p != str.end(); p++){
            if (*p == '/')
                *p = '_';
        }
        return str;
    });
    p.set_var("project.name",chest.name);
    p.set_var("file.name",name);
    
    ifstream ifs(target);
    auto spiled = split(cls,".");
    auto srcpath = proot / "src/" / (name + "." + spiled[0]);
    
    p.set_var("file.path",relative(srcpath,proot / "src").replace_extension(""));
    
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
    
    /*
    cout << "Use " << target.filename().string() << " to initial project" << endl;

*/
    return 0;
}