#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "utils.h"
#include "placeholder.h"

using namespace std;
using namespace chepp;

void print_help() {
    cout << "usage: chepp new [-h|--help] [--brief] [-t|--type <type>] [-c|--class <class>]" << endl; 
    cout << "[-l|--list] [-a|--add] [-d|--delete] <name|class>" << endl;
    cout << endl;
    cout << "Create some file(s) from template." << endl;
    cout << endl;
    cout << "  -t, --type    file type." << endl;
    cout << "  -c, --class   file template class." << endl;
    cout << "  -l, --list    list all file template class." << endl;
    cout << "  -a, --add     add a template." << endl;
    cout << "  -d, --delete  delete a template." << endl;
    cout << "  -h, --help    show this help message." << endl;
    cout << "  --brief       brief description." << endl;
    cout << endl;
}

void print_brief() {
    cout << "  new        create some file(s) from template." << endl;
}

void list_templates() {
    cout << "All available templates:" << endl;
    auto templates_path = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates";
    cout << endl;
    cout << "  type |   class   | description" << endl;
    cout << " ------|-----------|------------" << endl;
    for (auto& c: filesystem::directory_iterator(templates_path)) {
        auto file = c.path();
        ifstream ifs(c.path());
        string commit;
        getline(ifs,commit);
        placeholder p;
        p.set_op("set",[&p](string &str) -> string &{
            return p.set(str);
        });
        p.eval(commit);
        cout << "  " << right << setw(5)  << file.extension().string().erase(0,1) << "|"
             << right << setw(11) << file.stem().string() << "|"
             << p.vars["brief"] << endl;
        ifs.close();
    }
    cout << endl;
}

struct args_t {
    string type;
    string cls;
    bool add;
    bool del;
    string name;
    args_t():add(false),del(false){}
};

void check_args(const args_t &args) {
    if(args.add & args.del) {
        cerr << "Error! Add and delete cannot be set at the same time." << endl;
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char *argv[]) {
    args_t args;
    if (argc == 1) {
        print_help();
        return 0;
    }
    for (int i = 1; i != argc; i ++) {
        if (is_option(argv[i])) {
            auto option = string(argv[i]);
            if (option == "-t" ||option == "--type") {
                args.type  = argv[ ++ i ];
            } else if (option == "-c" ||option == "--class") {
                args.cls = argv[ ++ i ];
            } else if (option == "-a" ||option == "--add" ) {
                args.add = true;
            } else if (option == "-d" ||option == "--delete") {
                args.del = true;
            } else if (option == "-l" ||option == "--list") {
                list_templates();
                return 0;
            } else if (option == "-h" ||option == "--help") {
                print_help();
                return 0;
            } else if (option == "--brief") {
                print_brief();
                return 0;
            } else {
                cerr << "Error! Option " << argv[i] << " does not exist." << endl;
                exit(EXIT_FAILURE);
            }
        } else {
            args.name = string(argv[i]);
        }
    }
    check_args(args);
    if( args.del ) {
        auto path = filesystem::path(getenv("CHEST_SYSROOT")) /
            "etc/chest/templates" / args.name;
        if(filesystem::exists(path)) {
            remove(path);
            return 0;
        } else {
            cerr << "Error! Template does not exist." << endl;
            exit(EXIT_FAILURE);
        }
    }
    
	if( args.add ) {
        auto target = filesystem::path(getenv("CHEST_SYSROOT")) /
            "etc/chest/templates" / args.name;
        auto origin = filesystem::path(args.name);
        if(filesystem::exists(target)) {
            cout << "Error! Template already exists." << endl;
            exit(EXIT_FAILURE);
        } else {
            filesystem::copy(origin,target);
        }
    }
    
    if( args.type != "") {
        if(args.cls == "") 
            args.cls = "default";
        auto comexec = filesystem::path(getenv("CHEST_SYSROOT")) /
            "bin/_chest/new_type" / args.type;
        if(!filesystem::exists(comexec)) {
            cout << "Error! Template type does not exist." << endl;
            exit(EXIT_FAILURE);
        }
        auto command = comexec.string() + (" " +args.type + " " + args.cls + " " + args.name);
        system(command.c_str());
    }
    return 0;
}