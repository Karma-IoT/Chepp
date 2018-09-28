#include "chest.h"

#include <iostream>

#include "cpptoml.h"

namespace chepp {

chest_t::chest_t(filesystem::path ctoml) {
    auto config = cpptoml::parse_file("chest.toml");
    auto name = config->get_qualified_as<string>("project.name");
    auto family = config->get_qualified_as<string>("project.family");
    auto version = config->get_qualified_as<string>("project.version");
    if(name && family && version) {
        this -> name = *name;
        this -> family = *family;
        this -> version = *version;
    } else {
        cerr << "Error! project name, family or version must be set." << endl;
    }
    this -> description = config->get_qualified_as<string>("project.description").value_or("");
}

}