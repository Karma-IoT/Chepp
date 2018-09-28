#include <filesystem>
#include <iostream>

#include "chest.h"

using namespace std;
using namespace chepp;

int main() {
    auto p = "chest.toml";
    chest_t chest(p);
    return 0;
}