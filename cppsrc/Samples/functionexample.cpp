#include "functionexample.h"
#include <algorithm>

#include <windows.h>
#include <iostream>

//Carga da sk_access.dll
typedef char *(__stdcall *TDisp)(char *Buffer);
typedef void(__stdcall *TClear_Disp)();
typedef bool(__stdcall *TDevice_Is_Connected)();

bool functionexample::tecladoConectado()
{
    HINSTANCE hAPIDLL = LoadLibrary(".\\sk_access.dll");

    TDevice_Is_Connected Device_Is_Connected = (TDevice_Is_Connected)GetProcAddress(hAPIDLL, "Device_Is_Connected");
    if (!Device_Is_Connected)
    {
        std::cout << "Não encontrou função Device_Is_Connected" << std::endl;
        return true;
    }

    return Device_Is_Connected();
}

Napi::Boolean functionexample::TecladoConectadoWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Boolean returnValue = Napi::Boolean::New(env, functionexample::tecladoConectado());
    return returnValue;
}

std::string functionexample::escrever(std::string palavra)
{
    HINSTANCE hAPIDLL = LoadLibrary(".\\sk_access.dll");

    TDisp Disp = (TDisp)GetProcAddress(hAPIDLL, "Disp");
    if (!Disp)
    {
        std::cout << "Não encontrou função Disp" << std::endl;
        return "Erro";
    }
    char *cstr = strcpy((char *)malloc(palavra.length() + 1), palavra.c_str());
    Disp(cstr);
    return palavra;
}

Napi::String functionexample::EscreverWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String palavra = info[0].As<Napi::String>();

    Napi::String returnValue = Napi::String::New(env, functionexample::escrever(palavra));

    return returnValue;
}

void functionexample::apagar()
{
    HINSTANCE hAPIDLL = LoadLibrary(".\\sk_access.dll");

    TDevice_Is_Connected Device_Is_Connected = (TDevice_Is_Connected)GetProcAddress(hAPIDLL, "Device_Is_Connected");
    TClear_Disp Clear_Disp = (TClear_Disp)GetProcAddress(hAPIDLL, "Clear_Disp");
    if (!Clear_Disp)
    {
        std::cout << "Não encontrou função Clear_Disp" << std::endl;
        return;
    }

    Clear_Disp();
}

Napi::Value functionexample::ApagarWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    functionexample::apagar();
    return env.Null();
}

std::string functionexample::hello()
{
    return "Hello World";
}

int functionexample::add(int a, int b)
{
    return a + b;
}

std::string functionexample::maiusculo(std::string palavra)
{
    std::transform(palavra.begin(), palavra.end(), palavra.begin(), ::toupper);
    return palavra;
}

Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, functionexample::hello());

    return returnValue;
}

Napi::Number functionexample::AddWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();

    int returnValue = functionexample::add(first.Int32Value(), second.Int32Value());

    return Napi::Number::New(env, returnValue);
}

Napi::String functionexample::MaiusculoWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String palavra = info[0].As<Napi::String>();

    Napi::String returnValue = Napi::String::New(env, functionexample::maiusculo(palavra));

    return returnValue;
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("hello", Napi::Function::New(env, functionexample::HelloWrapped));
    exports.Set("add", Napi::Function::New(env, functionexample::AddWrapped));
    exports.Set("maiusculo", Napi::Function::New(env, functionexample::MaiusculoWrapped));
    exports.Set("tecladoConectado", Napi::Function::New(env, functionexample::TecladoConectadoWrapped));
    exports.Set("escrever", Napi::Function::New(env, functionexample::EscreverWrapped));
    exports.Set("apagar", Napi::Function::New(env, functionexample::ApagarWrapped));

    return exports;
}