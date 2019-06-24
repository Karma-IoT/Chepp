#include <iostream>
#include <vector>
#include <string>

#include "utils.h"

using namespace std;
using namespace chepp;

void print_help() {
    cout << "usage: chepp init [-h|--help] [--brief]" << endl;
    cout << endl;
    cout << "Init project in currect project." << endl;
    cout << endl;
}

void print_brief() {
    cout << "init currect project." << endl;
}

int main(int argc, char *argv[]) {
    vector<string> agrs;
    for (int i = 1; i != argc; i ++) {
        if (is_option(argv[i])) {
            agrs.push_back(string(argv[i]));
        } else {
            break;
        }
    }
    for (auto& p: agrs) {
        if (p == "--help" || p == "-h") {
            print_help();
			break;
        } else if (p == "--brief") {
            print_brief();
        }
    }
    // call init project.
    return 0;
}