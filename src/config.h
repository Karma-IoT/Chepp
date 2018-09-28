#ifndef _CONFIG_H
#define _CONFIG_H

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <bitset>

#include "chest.h"

using namespace std;

namespace chest{

class config {
public:
    config();
    config(const filesystem::path &p);
    config(const config&) = default;
    ~config() = default;
public:
    struct project_t {
        string name;
        string family;
        string version;
        vector<string maintainer;
        vector<string> upstream;
        vector<string> platform;
    };
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
    project_t &project();
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
    project_t project;
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
