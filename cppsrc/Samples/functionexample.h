#include <napi.h>

namespace functionexample
{

bool tecladoConectado();
Napi::Boolean TecladoConectadoWrapped(const Napi::CallbackInfo &info);

std::string escrever(std::string palavra);
Napi::String EscreverWrapped(const Napi::CallbackInfo &info);

void apagar();
Napi::Value ApagarWrapped(const Napi::CallbackInfo &info);

std::string hello();
Napi::String HelloWrapped(const Napi::CallbackInfo &info);

int add(int a, int b);
Napi::Number AddWrapped(const Napi::CallbackInfo &info);

std::string maiusculo(std::string palavra);
Napi::String MaiusculoWrapped(const Napi::CallbackInfo &info);

Napi::Object Init(Napi::Env env, Napi::Object exports);
} // namespace functionexample