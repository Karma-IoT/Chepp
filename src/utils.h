#ifndef _UTILS_H

namespace chepp {
    
template <typename Indexable>
bool is_option(Indexable argv) {
    if (argv[0] == '-') {
        return true;
    } else {
        return false;
    }
}

}

#endif