#include <iostream>
#include <filesystem>
#include <fstream>

#include "chest.h"
#include "utils.h"

using namespace std;
using namespace chepp;

int main(int argc, char *argv[]) {
    auto target = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates" / ( argv[2] + string(".pro"));

    if(!filesystem::exists(target)) {
        cerr << "Error! Template does not exist." << endl;
        exit(EXIT_FAILURE);
    }
    
    if(filesystem::exists("chest.pro")) {
        cerr << "Error! chest.pro already exist." << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Use " << target.filename().string() << " to initial project." << endl;
    cout << endl;
    
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
    
    cout << "Maintainer(s): ";
    // TODO: get default maintainer from configs.
    string maintainer;
    getline(cin,maintainer);
    project.maintainer.push_back(maintainer);
    if(maintainer != ""){
        while(maintainer != "") {
            cout << "Next maintainer: ";
            getline(cin,maintainer);
            if (maintainer != "")
                project.maintainer.push_back(maintainer);
        }
    }

#define chest_with_default(label,item) \
    cout << label <<": (general) "; \
    string item; \
    getline(cin,item); \
    if (item == "") \
        project.item.insert("general"); \
    else \
        project.item.insert(item); \
    if (item != "general") { \
        while(item != "") { \
            cout << "Next " << label << ": "; \
            getline(cin,item); \
            if (item != "") \
                project.arch.insert(item); \
        } \
    }
    
    chest_with_default("Architecture",arch);
    chest_with_default("Vendor",vendor);
    chest_with_default("Framework",framework);
    chest_with_default("OS",OS);
    chest_with_default("compiler",compiler);

    
    
    
    for (const auto &x: project.arch) {
        cout << x << endl;
    }
    
    /*ifstream ifs(target);
    ofstream ofs("chest.pro");
    string buffer;
    while(!ifs.eof()) {
        getline(ifs,buffer);
        auto pos = string::npos;
        replace_str(buffer, "%name%", "\"" +project.name + "\"");
        replace_str(buffer, "%family%", "\"" +project.family + "\"");
        replace_str(buffer, "%version%", "\"" +project.version + "\"");
        replace_str(buffer, "%description%", "\"" +project.description + "\"");
        if (buffer.find("%brief%") == string::npos) {
            ofs << buffer << endl;
        }
    }
    */
    return 0;
}