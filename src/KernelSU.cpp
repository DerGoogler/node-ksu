#include <napi.h>
#include <ksu.h>
#include <KernelSU.h>

using namespace std;
using namespace Napi;

Napi::Object BaseKernelSU::Init(Napi::Env env, Napi::Object exports) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "BaseKernelSU", {
        StaticMethod<&BaseKernelSU::BecomeManager>("becomeManager", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseKernelSU::GetVersion>("getVersion", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseKernelSU::GetAllowList>("getAllowList", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseKernelSU::IsSafeMode>("isSafeMode", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseKernelSU::UidShouldUnmount>("uidShouldUnmount", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseKernelSU::CreateNewItem>("CreateNewItem", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    // Create a persistent reference to the class constructor. This will allow
    // a function called on a class prototype and a function
    // called on instance of a class to be distinguished from each other.
    *constructor = Napi::Persistent(func);
    exports.Set("BaseKernelSU", func);

    // Store the constructor as the add-on instance data. This will allow this
    // add-on to support multiple instances of itself running on multiple worker
    // threads, as well as multiple instances of itself running in different
    // contexts on the same thread.
    //
    // By default, the value set on the environment here will be destroyed when
    // the add-on is unloaded using the `delete` operator, but it is also
    // possible to supply a custom deleter.
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

BaseKernelSU::BaseKernelSU(const Napi::CallbackInfo& info) : Napi::ObjectWrap<BaseKernelSU>(info) {
  // Napi::Env env = info.Env();
}


Napi::Value BaseKernelSU::BecomeManager(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "The 'pkg' should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string pkg = info[0].As<Napi::String>();
  
  return Napi::Boolean::New(env, become_manager(pkg.c_str()));
}

Napi::Value BaseKernelSU::GetVersion(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, get_version());
}

Napi::Value BaseKernelSU::GetAllowList(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  int uids[1024];
  int size = 0;
  bool result = get_allow_list(uids, &size);
  if (result) {
   Array data = Napi::Array::New(env, size);
   for (uint32_t i = 0; i < data.Length(); i++) {
    data[i] = uids[i];
   }
   return data;
  }
  
  return Napi::Array::New(env, 0);
}

Napi::Value BaseKernelSU::IsSafeMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Boolean::New(env, is_safe_mode());
}

Napi::Value BaseKernelSU::UidShouldUnmount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "The 'uid' should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  int uid = info[0].As<Napi::Number>();
  
  return Napi::Boolean::New(env, uid_should_umount(uid));
}


// Create a new item using the constructor stored during Init.
Napi::Value BaseKernelSU::CreateNewItem(const Napi::CallbackInfo& info) {
  // Retrieve the instance data we stored during `Init()`. We only stored the
  // constructor there, so we retrieve it here to create a new instance of the
  // JS class the constructor represents.
  Napi::FunctionReference* constructor = info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({ Napi::Number::New(info.Env(), 42) });
}

Object Init(Env env, Object exports) {
  BaseKernelSU::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)
