#ifndef TCHJS_JIT_H
#define TCHJS_JIT_H

#include <napi.h>

namespace tchjs {
    Napi::Object JitInit(Napi::Env env, Napi::Object exports);
}

#endif
