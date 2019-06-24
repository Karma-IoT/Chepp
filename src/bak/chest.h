#ifndef _CHEST_H
#define _CHEST_H

#include <filesystem>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

namespace chepp {

class chest_t {
public:
    chest_t() = default;
    chest_t(filesystem::path ctoml);
    chest_t(const chest_t&) = default;
    ~chest_t() = default;

public:
    void download();
    bool checksum();
    void build();
    
    void add_chest(const chest_t &chest);
    void add_deps(const chest_t &chest);
    
    filesystem::path &get_source();
    filesystem::path &get_binary(string platform);
public:
    string name;
    string family;
    string version;
    string description;
    vector<string> maintainer;
    set<string> arch;
    set<string> vendor;
    set<string> framework;
    set<string> OS;
    set<string> compiler;
private:
    filesystem::path source;
    map<string,filesystem::path> binary;
};

class chest_packages{
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
    enum class init_type {
        file,command
    };
    struct init_t {
        init_type type;
        bool require;
        vector<string> info;
    };
    
private:
    vector<chest_t> chest;
    map<string,rule_t> rule;
    map<string,build_t> build;
    map<string,string> variable;
    map<string,string> command;
    map<string,init_t> init;
    map<string,chest_t> deps;
};

}

#endif
