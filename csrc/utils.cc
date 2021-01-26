#include <napi.h>
#include <stdlib.h>
#include "utils.h"

namespace tchjs {
    std::vector<int64_t> napiArrayToVector(Napi::Array arr) {
        std::vector<int64_t> vec;
        size_t len = arr.Length();
        for (size_t i = 0; i < len; i++) {
            vec.push_back(arr.Get(i).ToNumber().Int64Value());
        }
        return vec;
    }
}
