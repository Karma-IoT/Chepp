#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "utils.h"

using namespace std;
using namespace chepp;

void print_help() {
    cout << "usage: chepp new [-h|--help] [--brief] [-t|--type <type>] [-c|--class <class>]" << endl; 
    cout << "[-l|--list] [-a|--add] [-d|--delete] <name|class>" << endl;
    cout << endl;
    cout << "Create some file(s) from template." << endl;
    cout << endl;
    cout << "  -t, --type    file type." << endl;
    cout << "  -c, --class   file template class" << endl;
    cout << "  -l, --list    list all file template class" << endl;
    cout << "  -a, --add     add a template" << endl;\
    cout << "  -d, --delete  delete a template" << endl;
    cout << endl;
}

void print_brief() {
    cout << "  new        create some file(s) from template." << endl;
}

void list_templates() {
    
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
        cout << "Error! Add and delete cannot be set at the same time." << endl;
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
            }
        } else {
            args.name = string(argv[i]);
        }
    }
    check_args(args);
    cout << args.name << endl;
    // call init project.
    return 0;
}