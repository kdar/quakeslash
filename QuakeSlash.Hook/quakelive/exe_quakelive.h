// Copyright 2012 Kevin Darlington

#ifndef GAME_QUAKELIVE_H_
#define GAME_QUAKELIVE_H_

#include <boost/extension/extension.hpp>
#include <boost/extension/factory.hpp>
#include <boost/extension/type_map.hpp>

#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include "../exe.h"
#include "../opengl/opengl.h"
#include "datastructures.h"
#include "trackeditem.h"

class DetourXS;

namespace quakeslash {
class OpenGL;

typedef BOOL (WINAPI* Cgame_DllEntryType)(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
//typedef HMODULE (WINAPI* LoadLibraryType)(LPCSTR lpLibFileName);

typedef void (__cdecl* Cmd_ExecuteStringType)(const char *text);
typedef void (__cdecl* CG_DrawActiveFrameType)(int serverTime, uint32_t stereoView, qboolean demoPlayback);
typedef void (__cdecl* CG_EntityEventType)(centity_t* cent, vec3_t position);
//typedef cvar_t* (__cdecl* Cvar_Get2Type)(const char *var_name, const char *var_value, const char *min, const char *max, int flags);
typedef cvar_t* (__cdecl* Cvar_GetType)(const char *var_name, const char *var_value, int flags); 
typedef void (__cdecl* CG_MapRestartType)();
//typedef char* (__cdecl* Com_PrintfType)(const char *Format, ...);
//typedef /*cvar_t*/uint32_t (__cdecl* tCvar_Set2)(const char *var_name, const char *value, qboolean force);
//tCvar_Set2 Cvar_Set2 = NULL;

//---------------------------------------
class ExeQuakelive : public Exe {
 public:
   //ExeQuakelive() {}
   ExeQuakelive(ExeLinkage* linkage,
     OpenGL *open_gl,
     DetourXS* cgame_dllentry,
     DetourXS* cg_entityevent, 
     DetourXS* cg_drawactiveframe, 
     DetourXS* cg_maprestart, 
     TrackedItemManager* tim,
     glfont::GLFont* font,
     events::ConnectionSet* cs);

  static ExeQuakelive* Create();

  virtual void Run();
  virtual void Stop();

  void HookQuakeliveDll();
  void HookCgameDll(int delay = 0);
  void UnhookCgameDll();
  BOOL Cgame_DllEntryDetour(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
  //HMODULE LoadLibraryDetour(LPCSTR lpLibFileName);

  void DrawScene();

  void CG_EntityEventDetour(centity_t* cent, vec3_t position);
  void CG_DrawActiveFrameDetour(int serverTime, uint32_t stereoView, qboolean demoPlayback);
  void CG_MapRestartDetour();

 public:
  gitem_t* bg_itemlist_;
  // Found in the CG_EntityEvent function in the EV_ITEM_PICKUP case
  // where it tests if bg_numItems is less than 0x36;
  int bg_numitems_;

  /*DetourXS* loadlibrary_;
  void* loadlibrary_thunk_;
  LoadLibraryType LoadLibrary_;*/

  DetourXS* cgame_dllentry_;
  void* cgame_dllentry_thunk_;
  Cgame_DllEntryType Cgame_DllEntry_;

  DetourXS* cg_entityevent_;
  void* cg_entityevent_thunk_;
  CG_EntityEventType CG_EntityEvent_;

  DetourXS* cg_drawactiveframe_; 
  void* cg_drawactiveframe_thunk_;
  CG_DrawActiveFrameType CG_DrawActiveFrame_;

  DetourXS* cg_maprestart_; 
  void* cg_maprestart_thunk_;
  CG_MapRestartType CG_MapRestart_;

  Cmd_ExecuteStringType Cmd_ExecuteString_;
  Cvar_GetType Cvar_Get_;
  //Com_PrintfType Com_Printf_;

  OpenGL* open_gl_;
  GLuint tex_mega_;
  GLuint tex_redarmor_;
  GLuint tex_yellowarmor_;

  TrackedItemManager* trackeditem_manager_;
  glfont::GLFont* font_;

  int servertime_;

  events::ConnectionSet* cs_;
};

void exeQuakeliveRegisterPlugin(boost::extensions::type_map& types);
Exe *createExeQuakeliveRegisterPlugin(boost::extensions::factory<Exe>& factory);
};

#endif  // GAME_BOVADA_
