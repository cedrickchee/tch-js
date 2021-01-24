#include <napi.h>
#include "jit.h"
#include "script_module.h"
#include "tensor.h"
#include "utils.h"
#include <stdlib.h>

namespace tchjs {
    Napi::Object randn(const Napi::CallbackInfo &info) {
        Napi::Array shape = info[0].As<Napi::Array>();
        at::Tensor tensor = torch::randn(napiArrayToVector(shape), torch::requires_grad(false));
        auto napiTensor = Tensor::NewInstance();
        Napi::ObjectWrap<Tensor>::Unwrap(napiTensor)->setTensor(tensor);
        return napiTensor;
    }

    Napi::Object ones(const Napi::CallbackInfo &info) {
        Napi::Array shape = info[0].As<Napi::Array>();
        at::Tensor tensor = torch::ones(napiArrayToVector(shape), torch::requires_grad(false));
        auto napiTensor = Tensor::NewInstance();
        Napi::ObjectWrap<Tensor>::Unwrap(napiTensor)->setTensor(tensor);
        return napiTensor;
    }

    Napi::Object tensor(const Napi::CallbackInfo &info) {
        Napi::Float32Array arr = info[0].As<Napi::Float32Array>();
        size_t elements = arr.ElementLength();
        torch::TensorOptions options;
        at::Tensor tensor = torch::tensor(at::ArrayRef<float>(arr.Data(), elements), options);
        auto napiTensor = Tensor::NewInstance();
        Napi::ObjectWrap<Tensor>::Unwrap(napiTensor)->setTensor(tensor);
        return napiTensor;
    }

    Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
        JitInit(env, exports);
        ScriptModule::Init(env, exports);
        Tensor::Init(env, exports);
        exports.Set(Napi::String::New(env, "randn"), Napi::Function::New(env, randn));
        exports.Set(Napi::String::New(env, "ones"), Napi::Function::New(env, ones));
        exports.Set(Napi::String::New(env, "tensor"), Napi::Function::New(env, tensor));
        return exports;
    }

    NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
}
