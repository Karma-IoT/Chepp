#include <filesystem>
#include <iostream>

#include "chest.h"

using namespace std;
using namespace chepp;

int main() {
    auto p = "chest.toml";
    chest_t chest(p);
    cout << chest.name << endl;
    cout << chest.family << endl;
    cout << chest.version << endl;
    cout << chest.description << endl;
    
    for (const auto &x: chest.maintainer) {
        cout << x << endl;
    }
    
    for (const auto &x: chest.upstream) {
        cout << x << endl;
    }
    
    for (const auto &x: chest.platform) {
        cout << x << endl;
    }
    
    return 0;
}