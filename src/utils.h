#ifndef TCHJS_UTILS_H
#define TCHJS_UTILS_H

#include <napi.h>
#include <stdlib.h>

namespace tchjs {
    std::vector<int64_t> napiArrayToVector(Napi::Array arr);
}

#endif
