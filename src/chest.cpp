#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

void check_system() {
    auto sysroot = getenv("CHEST_SYSROOT");
    if(!sysroot) {
        cerr << "Environmental variable `CHEST_SYSROOT' must be set!" << endl;
        exit(EXIT_FAILURE);
    }
}

void print_help() {
    cout << "usage: chepp [--version] [--help] <command> [<args>]" << endl;
    auto sysroot_subcommand = filesystem::path(getenv("CHEST_SYSROOT"))
        / "bin" / "_chest" / "command";
    for (auto& p: filesystem::directory_iterator(sysroot_subcommand)) {
        cout << "Subcommand in " << p.path().filename() << "group:" << endl;
        for (auto& c: filesystem::directory_iterator(p)) {
            cout << "\t";
            system((c.path().string() + " --brief").c_str());
        }
    }
}

void print_version() {
    cout << "chepp version 0.1.0" << endl;
}

template <typename Indexable>
bool is_option(Indexable argv) {
    if (argv[0] == '-') {
        return true;
    } else {
        return false;
    }
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
    for (int i = command.size(); i != argc; i ++) {
        subcommand.push_back(string(argv[i]));
    }
    if (argc == 1) {
        print_help();
    }
    for (auto& p: command) {
        if (p == "--version" || p == "-v") {
            print_version();
        } else if (p == "--help" || p == "-h") {
            print_help();
        }
    }
    // Find command and invoke
    auto subc = filesystem::path(getenv("CHEST_SYSROOT"))
        / "bin" / "_chest" / "command" / subcommand[0];
    if (! filesystem::exists(subc)) {
        cerr << "Subcommand does not exist" << endl;
        print_help();
    } else {
        auto commstr = subc.string();
        for (auto& p: subcommand) {
            commstr.append(" ");
            commstr.append(p);
        }
        system(commstr.c_str());
    }
    return 0;
}
