#ifndef CHEPP_ARGS_H
#define CHEPP_ARGS_H

namespace chepp {

class parser {
public:
    parser() = default;
    parser(int argc, char *argv[]):argc(argc), argv(argv)  {}
    ~parser() = default;

public:
    void set_args(int argc, char *argv[]);
    void set_short_arguments(string &flag, char command);
    void set_long_arguments(string &flag, string &command);
    void parse();

public:
    string name;
    string subcommand;
    map<string,string> args;

private:
    int argc;
    char *argv[];
    map<string,string> index;
};

};

#endif
