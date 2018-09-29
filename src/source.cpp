#include <iostream>
#include <string>

#include "chest.h"
#include "utils.h"

using namespace std;
using namespace chepp;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Error! Wrong number of parameters." << endl;
        exit(EXIT_FAILURE);
    }
    string type = argv[1];
    string cls = argv[2];
    string name = argv[3];
    auto proot = find_root();
    chest_t chest(proot / "chest.toml");
    
    auto target = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates" / (cls + "." + type);

    if(!filesystem::exists(target)) {
        cerr << "Error! Template does not exist." << endl;
        exit(EXIT_FAILURE);
    }
    
    ifstream ifs(target);
    ofstream ofs(name + "." + type);
    string buffer;
    while(!ifs.eof()) {
        getline(ifs,buffer);
        auto pos = string::npos;
        if(!((pos = buffer.find("%project_name%")) == string::npos)) {
            buffer.replace(pos,14,"\"" +project.name + "\"");
        } else if(!((pos = buffer.find("%family%")) == string::npos)) {
            buffer.replace(pos,8,"\"" +project.family + "\"");
        }
    }
    
    
    cout << "Use " << target.filename().string() << " to initial project" << endl;


    return 0;
}