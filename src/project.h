#ifndef _PROJECT_H
#define _PROJECT_H

#include <filesystem>
#include <string>
#include <map>

using namespace std;

namespace chest{

class config {
public:
    config();
    config(const filesystem::path &p);
    config(const config&) = default;
    ~config() = default;
private:
    filesystem::path tpath;
    struct {
        string name;
        string family;
        string version;
        string maintainer;
        string upstream;
        string platform;
    } project;
    map<string,string> chest;
    
};

}

#endif
