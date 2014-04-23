// Copyright 2012 Kevin Darlington

#include <Windows.h>

#define DLL_EXPORT __declspec(dllexport) __cdecl

#include <boost/scoped_ptr.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>
#include <boost/function.hpp>

#include "quakelive/exe_quakelive.h"

#define MB(s) MessageBox(NULL, s, NULL, MB_OK);
#define MBA(s) MessageBoxA(NULL, s, NULL, MB_OK);

namespace be = boost::extensions;

quakeslash::ExeLinkage g_linkage;

//=======================================
struct RunData
{
  wchar_t executepath[2048];
};

//=======================================
extern "C" int DLL_EXPORT Run(RunData *data)
{
  try {
    boost::extensions::type_map types;
    quakeslash::exeQuakeliveRegisterPlugin(types);

    boost::scoped_ptr<quakeslash::ExeFactory> current_factory;
    std::map<std::string, be::factory<quakeslash::ExeFactory>>& factories(types.get());
    for (std::map<std::string, 
         be::factory<quakeslash::ExeFactory>>::iterator it = factories.begin();
         it != factories.end(); ++it) {
      current_factory.reset(it->second.create());
      if (current_factory->ShouldCreate()) {
        break;
      }
      current_factory.reset();
    }

    if (current_factory) {      
      boost::scoped_ptr<quakeslash::Exe> exe(current_factory->Create(&g_linkage));
      exe->Run();
      while (true) { 
        //g_mutex.lock();
        if (g_linkage.exit_) break;
        //g_mutex.unlock();
        Sleep(10);
      }
      exe->Stop();
    }
  } catch(std::exception& e) {
    MBA(e.what());
  }

  return 0;
}  

//=======================================
extern "C" int DLL_EXPORT Stop() {
  g_linkage.Exit();
  return 0;
}