#ifndef _UTILS_H

#include <filesystem>

using namespace std;

namespace chepp {
    
template <typename Indexable>
bool is_option(Indexable argv) {
    if (argv[0] == '-') {
        return true;
    } else {
        return false;
    }
}

filesystem::path find_root() {
    auto &&current = filesystem::current_path();
    do {
        current = current.parent_path();
    }while (!filesystem::exists(current / "chest.toml") && current.has_parent_path());
    if (current.has_parent_path()) {
        cerr << "Error! Can not find chest.toml" << endl;
        exit(EXIT_FAILURE);
    }
    return current;
}

void replace_str(string &buffer,const string &search, const string &str) {
    if (auto pos = string::npos; !((pos = buffer.find(search)) == string::npos ) ) {
        buffer.replace(pos, search.size(), str);
    }
}

}

#endif