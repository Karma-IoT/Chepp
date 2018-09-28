#ifndef _CONFIG_H
#define _CONFIG_H

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <bitset>

#include "chest.h"

using namespace std;

namespace chepp {

class config {
public:
    config();
    config(const filesystem::path &p);
    config(const config&) = default;
    ~config() = default;
public:
    struct rule_t {
        string command;
        map<string,string> variable;
    };
    struct build_t {
        rule_t rule;
        string in;
        string out;
        map<string,string> variable;
    };
    struct init_t {
        init_type type;
        bool require;
        vector<string> info;
    };
public:
    // some getter
public:
    string get_unique_name();
public:
    void add_chest(const chest_t &chest);
    void add_deps(const chest_t &chest);
public:
    void do_ninja();
    void do_init();
private:
    filesystem::path tpath;
    chest_t project;
    vector<chest_t> chest;
    map<string,rule_t> rule;
    map<string,build_t> build;
    map<string,string> variable;
    map<string,string> command;
    map<string,init_t> init;
    map<string,chest_t> deps;
    ostream &out;
};

}

#endif
