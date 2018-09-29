#include <iostream>
#include <filesystem>
#include <fstream>

#include "chest.h"

using namespace std;
using namespace chepp;

int main(int argc, char *argv[]) {
    auto target = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates" / (string("pro.") + argv[2] + ".toml");

    if(!filesystem::exists(target)) {
        cerr << "Error! Template does not exist." << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Use " << target.filename().string() << " to initial project" << endl;
    
    chest_t project;
    
    auto default_name = filesystem::current_path().filename().string();
    cout << "Project name (" << default_name << "): ";
    getline(cin,project.name);
    if (project.name == "")
        project.name = default_name;
    
    cout << "Family name (" << "): ";
    getline(cin,project.family);
    // TODO: get default from configs.
    
    cout << "Version ( 0.1.0 ): ";
    getline(cin,project.version);
    if (project.version == "")
        project.version = "0.1.0";
    
    cout << "Description: ";
    getline(cin,project.description);
    
    if(filesystem::exists("chest.toml")) {
        cerr << "Error! chest.toml already exist." << endl;
        exit(EXIT_FAILURE);
    }
    ifstream ifs(target);
    ofstream ofs("chest.toml");
    string buffer;
    while(!ifs.eof()) {
        getline(ifs,buffer);
        auto pos = string::npos;
        if(!((pos = buffer.find("%name%")) == string::npos)) {
            buffer.replace(pos,6,"\"" +project.name + "\"");
        } else if(!((pos = buffer.find("%family%")) == string::npos)) {
            buffer.replace(pos,8,"\"" +project.family + "\"");
        } else if(!((pos = buffer.find("%version%")) == string::npos)) {
            buffer.replace(pos,9,"\"" +project.version + "\"");
        } else if(!((pos = buffer.find("%description%")) == string::npos)) {
            buffer.replace(pos,13,"\"" +project.description + "\"");
        } 
        ofs << buffer << endl;
    }
    return 0;
}