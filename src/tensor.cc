#include <napi.h>
#include "tensor.h"

namespace tchjs {
    Napi::FunctionReference Tensor::constructor;

    Napi::Object Tensor::Init(Napi::Env env, Napi::Object exports) {
        Napi::HandleScope scope(env);

        Napi::Function func = DefineClass(env, "Tensor", {
                InstanceMethod("toString", &Tensor::toString),
                InstanceMethod("toUint8Array", &Tensor::toUint8Array),
                InstanceMethod("toFloat32Array", &Tensor::toFloat32Array),
                InstanceMethod("view", &Tensor::view)
        });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("Tensor", func);
        return exports;
    }

    Tensor::Tensor(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Tensor>(info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
    }

    Napi::Object Tensor::NewInstance() {
        return constructor.New({});
    }

    void Tensor::setTensor(at::Tensor tensor) {
        this->tensor = tensor;
    }

    torch::Tensor Tensor::getTensor() {
        return this->tensor;
    }

    Napi::Value Tensor::toString(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);

        std::stringstream ss;
        ss << "Type=" << this->tensor.options() << std::endl;
        ss << ", Size=" << this->tensor.sizes() << std::endl;
        return Napi::String::New(env, ss.str());
    }

    Napi::Value Tensor::toFloat32Array(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);

        uint64_t size = this->tensor.numel();
        // Make float32 type tensor
        auto floatData = this->tensor.contiguous().data_ptr<float>();
        // Wrap in NAPI float32 array
        auto arr = Napi::Float32Array::New(env, size);
        for (uint64_t i = 0; i < size; i++) {
            arr[i] = floatData[i];
        }
        return arr;
    }

    Napi::Value Tensor::toUint8Array(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);

        uint64_t size = this->tensor.numel();
        // Make uint8 type tensor
        auto byteTensor = this->tensor.clamp(0, 255).to(at::ScalarType::Byte);
        auto byteData = byteTensor.contiguous().data_ptr<uint8_t>();
        // Wrap in NAPI uint8 array
        auto arr = Napi::Uint8Array::New(env, size);
        for (uint64_t i = 0; i < size; i++) {
            arr[i] = byteData[i];
        }
        return arr;
    }

    Napi::Value Tensor::view(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        Napi::Array shape = info[0].As<Napi::Array>();
        std::vector<int64_t > vshape;
        uint32_t len = shape.Length();
        for (uint32_t i = 0; i < len; i++) {
            vshape.push_back(shape.Get(i).ToNumber());
        }
        torch::Tensor tensor = this->tensor.view(vshape);
        auto napiTensor = Tensor::NewInstance();
        Napi::ObjectWrap<Tensor>::Unwrap(napiTensor)->setTensor(tensor);
        return napiTensor;
    }
}
