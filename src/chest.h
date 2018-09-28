#ifndef _CHEST_H
#define _CHEST_H

namespace chepp {

class chest {
public:
    chest();
    chest(filesystem::path ctoml);
    chest(const chest&) = default;
    ~chest() = default;
public:
    enum class remote_type {
        source,
        local
    };
public:
    void download();
    bool checksum();
    void build();
    filesystem::path &source();
    filesystem::path &binary(string platform);
public:
    string name;
    remote_type type;
    vector<string> upstream;
    string version;
private:
    filesystem::path source;
    map<string,filesystem::path> binary;
};

}

#endif
