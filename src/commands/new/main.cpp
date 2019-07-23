#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "utils.h"
#include "ecode/src/ecode.h"

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
    cout << "create some file(s) from template." << endl;
}

void list_templates(string name) {
    if (! filesystem::exists(templates_path)) {
        cerr << "Can't find templates directory under CHEST_SYSROOT" << endl;
        exit(EXIT_FAILURE);
    }
    auto templates_path = filesystem::path(getenv("CHEST_SYSROOT")) /
        "etc/chest/templates";
    if (name == "") {
        // list all template
        cout << "All available templates:" << endl;
    } else {
        // list template for type `name`
        cout << "Available templates for " << name <<" :" << endl;
        auto p = templates_path / name;
        if (filesystem::exists(p) && filesystem::is_regular_file(p) && filesystem::is_symlink(p)) {
            auto command_str = p.string() + " -l";
            cout << command_str << endl;
        }
    }
}

struct args_t {
    string type;
    string cls;
    string name;

    void parse(int argc, char *argv[]) {
        if (argc == 1) {
            print_help();
        }
    }
};

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
            "etc" / "chest" / "templates" / args.name;
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
            "bin/chest/command/new_types" / args.type;
        cout << comexec << endl;
        if(!filesystem::exists(comexec)) {
            cout << "Error! Template type does not exist." << endl;
            exit(EXIT_FAILURE);
        }
        auto command = comexec.string() + (" " +args.type + " " + args.cls + " " + args.name);
        system(command.c_str());
    }
    return 0;
}
