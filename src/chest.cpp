#include "chest.h"

#include <iostream>

#include "cpptoml.h"

namespace chepp {

chest_t::chest_t(filesystem::path ctoml) {
    auto config = cpptoml::parse_file("chest.toml");
    auto project = config->get_table("project");
    auto name = project->get_as<string>("name");
    auto family = project->get_as<string>("family");
    auto version = project->get_as<string>("version");
    if(name && family && version) {
        this -> name = *name;
        this -> family = *family;
        this -> version = *version;
    } else {
        cerr << "Error! project name, family or version must be set." << endl;
    }
    this -> description = project->get_as<string>("description").value_or("");
    auto maintainers = project->get_array_of<string>("maintainer");
    for (auto &x: *maintainers) {
        this -> maintainer.push_back(x);
    }
    
    auto arch = project->get_array_of<string>("arch");
    for (auto &x: *arch) {
        this -> arch.insert(x);
    }
    auto vendor = project->get_array_of<string>("vendor");
    for (auto &x: *vendor) {
        this -> vendor.insert(x);
    }
    auto framework = project->get_array_of<string>("framework");
    for (auto &x: *framework) {
        this -> framework.insert(x);
    }
    auto OS = project->get_array_of<string>("OS");
    for (auto &x: *OS) {
        this -> OS.insert(x);
    }
    auto compiler = project->get_array_of<string>("compiler");
    for (auto &x: *compiler) {
        this -> compiler.insert(x);
    }
}

}