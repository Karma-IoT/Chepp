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
    auto upstream = project->get_array_of<string>("upstream");
    for (auto &x: *upstream) {
        this -> upstream.push_back(x);
    }
    auto platform = project->get_array_of<string>("platform");
    for (auto &x: *platform) {
        this -> upstream.push_back(x);
    }
}

}