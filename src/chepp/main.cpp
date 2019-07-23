#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdio>
#include <iomanip>

#include "utils.h"

using namespace std;
using namespace chepp;

void check_system() {
    auto sysroot = getenv("CHEST_SYSROOT");
    if(!sysroot) {
        cerr << "Error! Environmental variable `CHEST_SYSROOT' must be set!" << endl;
        exit(EXIT_FAILURE);
    }
}

void print_help() {
    cout << "usage: chepp [-v|--version] [-h|--help] <subcommand> [<args>]" << endl;
    cout << endl;
    cout << "Chest is an universal packages manager." << endl;
    cout << "Chepp is an implemention for Chest." << endl;
    cout << endl;
    
    cout << "Available options:" << endl;
    cout << "  -h, --help      show this help message." << endl;
    cout << "  -v, --version   version." << endl;
    cout << endl;
    
    auto sysroot_subcommand = filesystem::path(getenv("CHEST_SYSROOT"))
        / "bin" / ".chest" / "commands";
    cout << "Available subcommands:" << endl;
    if (! filesystem::exists(sysroot_subcommand)) {
        cerr << "Can't find command directory under ${CHEST_SYSROOT}" << endl;
        exit(EXIT_FAILURE);
    } else {
        for (auto& c: filesystem::directory_iterator(sysroot_subcommand)) {
            if (filesystem::is_regular_file(c) || filesystem::is_symlink(c)) {
                FILE *p = popen((c.path().string() + " --brief").c_str(),"r");
                if (p == NULL) {
                    cout << (c.path().string() + " --brief") << endl;
                } else {
                    char tmp[1024];
                    fgets(tmp,1024,p);
                    cout << "  " << left << setw(6) << c.path().filename().string()
                         << " "<< tmp;
                    fclose(p);
                }
            }
        }
        cout << endl;
    }
}

void print_version() {
    cout << "chepp version 0.1.0" << endl;
}

int main(int argc, char *argv[]) {
    check_system();
    vector<string> command;
    vector<string> subcommand;
    for (int i = 1; i != argc; i ++) {
        if (is_option(argv[i])) {
            command.push_back(string(argv[i]));
        } else {
            break;
        }
    }
    for (int i = command.size() + 1; i != argc; i ++) {
        subcommand.push_back(string(argv[i]));
    }
    if (argc == 1) {
        print_help();
        return 0;
    }
    for (auto& p: command) {
        if (p == "--version" || p == "-v") {
            print_version();
			break;
        } else if (p == "--help" || p == "-h") {
            print_help();
			break;
        }
    }

    // Find command and invoke
	
	if (!subcommand.empty()) {
		auto subc = filesystem::path(getenv("CHEST_SYSROOT"))
			/ "bin/.chest/commands" / subcommand[0];
		if (! filesystem::exists(subc)) {
			cerr << "Subcommand does not exist" << endl;
			print_help();
            exit(EXIT_FAILURE);
		} else if(filesystem::is_regular_file(subc) || filesystem::is_symlink(subc)) {
			auto commstr = subc.string();
			for (auto p = subcommand.cbegin() + 1; p != subcommand.cend(); p++) {
				commstr.append(" ");
				commstr.append(*p);
			}
			system(commstr.c_str());
		}
	}
    return 0;
}
