#ifndef _UTILS_H

#include <filesystem>
#include <string>

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

vector<string> split(const string &express, const string &sep) {
    auto sem0 = 0;
    auto sem1 = express.find_first_of(sep,sem0);
    vector<string> exp;
    while (sem1 != string::npos) {
        exp.push_back(express.substr(sem0,sem1 - sem0));
        sem0 = sem1 + 1;
        sem1 = express.find_first_of(sep,sem0);
    }
    if (sem1 - sem0 > 0) {
        exp.push_back(express.substr(sem0,sem1 - sem0));
    }
    return exp;
}

string& trim(string &s) {
    if (s.empty()) {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

}

#endif
