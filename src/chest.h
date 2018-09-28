#ifndef _CHEST_H
#define _CHEST_H

#include <filesystem>
#include <vector>
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
    filesystem::path &get_source();
    filesystem::path &get_binary(string platform);
public:
    string name;
    string family;
    string version;
    string description;
    vector<string> maintainer;
    vector<string> upstream;
    vector<string> platform;
private:
    filesystem::path source;
    map<string,filesystem::path> binary;
};

}

#endif
