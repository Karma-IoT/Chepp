#include <args.h>

namespace chepp {

void parser::set_args(int argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
}

void parser::set_short_arguments(string &flag, char command) {
    string arg = "-" + command;
    index[arg] = flag;
}

void parser::set_long_arguments(string &flag, string &command) {
    index[command] = flag;
}

void parser::parse() {
    for (int i = 1; i != argc; ++i) {
        string seg(argv[i]);
    }
}

}
