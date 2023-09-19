#ifndef KERNELSU_H
#define KERNELSU_H

#include <napi.h>

using namespace Napi;

class BaseKernelSU : public Napi::ObjectWrap<BaseKernelSU> {
  public:
   static Napi::Object Init(Napi::Env env, Napi::Object exports);
   BaseKernelSU(const Napi::CallbackInfo& info);
   static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

  private:
   static Napi::Value BecomeManager(const Napi::CallbackInfo& info);
   static Napi::Value GetVersion(const Napi::CallbackInfo& info);
   static Napi::Value GetAllowList(const Napi::CallbackInfo& info);
   static Napi::Value IsSafeMode(const Napi::CallbackInfo& info);
   static Napi::Value UidShouldUnmount(const Napi::CallbackInfo& info);
};

#endif