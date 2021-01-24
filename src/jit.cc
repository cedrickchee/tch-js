#include "jit.h"
#include "script_module.h"
#include <torch/torch.h>
#include <torch/script.h>
#include <stdlib.h>
#include <napi.h>

namespace tchjs {
    class LoadWorker : public Napi::AsyncWorker {
    public:
        static void load(const Napi::CallbackInfo &info) {
            std::string filename = info[0].As<Napi::String>().Utf8Value();
            Napi::Function cb = info[1].As<Napi::Function>();
            auto *worker = new LoadWorker(cb, filename);
            worker->Queue();
        }

    protected:
        void Execute() override {
            module = torch::jit::load(filename);
        }

        void OnOK() override {
            Napi::HandleScope scope(Env());
            auto scriptModule = ScriptModule::NewInstance();
            Napi::ObjectWrap<ScriptModule>::Unwrap(scriptModule)->setModule(module);
            Callback().Call({Env().Undefined(), scriptModule});
        }

    private:
        LoadWorker(Napi::Function cb, std::string &filename)
                : Napi::AsyncWorker(cb), filename(filename) {}

        torch::jit::script::Module module;
        std::string filename;
    };

    Napi::Object JitInit(Napi::Env env, Napi::Object exports) {
        exports.Set(Napi::String::New(env, "load"), Napi::Function::New(env, LoadWorker::load));
        return exports;
    }
}
