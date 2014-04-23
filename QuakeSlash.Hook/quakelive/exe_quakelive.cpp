// Copyright 2012 Kevin Darlington

#include <string>
#include <sstream>

#include "../DetourXS/detourxs.h"
#include "../forcecast.h"
#include "../thisthunk.h"
#include "exe_quakelive.h"
#include "ui.h"
#include "offsets.h"
#include "../resources/mega.h"
#include "../resources/redarmor.h"
#include "../resources/yellowarmor.h"
#include "../resources/aero.h"

#include <boost/thread.hpp>

#define MB(s) MessageBox(NULL, s, NULL, MB_OK);
#define MBA(s) MessageBoxA(NULL, s, NULL, MB_OK);

namespace quakeslash {
//=======================================
// Gets the address of DllMain of a module
PVOID GetAddressOfEntryPoint(HMODULE hmod) {
  PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)hmod;
  PIMAGE_NT_HEADERS pinth = (PIMAGE_NT_HEADERS)((PBYTE)hmod + pidh->e_lfanew);
  PVOID pvEntry = (PBYTE)hmod + pinth->OptionalHeader.AddressOfEntryPoint;

  return pvEntry;
}

//=======================================
// Called by our OpenGL draw event. 
void ExeQuakelive::DrawScene()
{  
  std::stringstream s;
  // Detect of our font texture was deleted. If so
  // recreate our textures.
  if (!glIsTexture(UI_FONT_TEXTURE_ID)) {
    std::stringstream font;
    font.write(reinterpret_cast<const char*>(aero_font), sizeof(aero_font));
    if (!font_->Create(font, UI_FONT_TEXTURE_ID)) {
      //MB(L"FIALED");
    }

    tex_mega_ = open_gl_->LoadTexture(mega_image, sizeof(mega_image));
    tex_redarmor_ = open_gl_->LoadTexture(redarmor_image, sizeof(redarmor_image));
    tex_yellowarmor_ = open_gl_->LoadTexture(yellowarmor_image, sizeof(yellowarmor_image));
  }

  glPushMatrix();
  glLoadIdentity();

  // Location of the frame where to draw the icons and text.
  glTranslatef(UI_FRAME_X, UI_FRAME_Y, 0.0f);

  float image_y = UI_IMAGE_Y_START;
  float text_y = UI_TEXT_Y_START;

  //if (trackeditem_manager_->Changed()) {
  for(std::vector<TrackedItem*>::iterator it = trackeditem_manager_->items_.begin(); it != trackeditem_manager_->items_.end(); ++it) {
    /*s << "say " << image_y;
    Cmd_ExecuteString_(s.str().c_str());
    s.str("");*/

    int timediff = static_cast<int>((static_cast<float>(servertime_) - (*it)->servertime_) / 1000.0);
    float color1[3] = UI_TEXT_NORMAL_COLOR;
    float color2[3] = UI_TEXT_NEGATIVE_COLOR;
    // If the event was a respawn one, just make the text red.
    // Indicates that our client detected a respawn but no one has
    // picked it up yet.
    /*if ((*it)->event_ == EV_ITEM_RESPAWN) {
      color[0] = 1.0f;
      color[1] = 0.0f;
      color[2] = 0.0f;
    }*/

    if ((*it)->item_ == IT_ARMOR) {
      int timeleft = 25 - timediff;
      s << timeleft;
      if ((*it)->quantity_ == 50) {
        open_gl_->DrawText(const_cast<char*>(s.str().c_str()), *font_, UI_TEXT_X_OFFSET, text_y, timeleft > 0 ? color1 : color2);
        open_gl_->DrawImage(tex_yellowarmor_, UI_IMAGE_X_OFFSET, image_y, 0.0f);        
      } else if ((*it)->quantity_ == 100) {
        open_gl_->DrawText(const_cast<char*>(s.str().c_str()), *font_, UI_TEXT_X_OFFSET, text_y, timeleft > 0 ? color1 : color2);
        open_gl_->DrawImage(tex_redarmor_, UI_IMAGE_X_OFFSET, image_y, 0.0f);        
      }
    } else if ((*it)->item_ == IT_HEALTH) {
      int timeleft = 35 - timediff;
      s << timeleft;
      if ((*it)->quantity_ == 100) {        
        open_gl_->DrawText(const_cast<char*>(s.str().c_str()), *font_, UI_TEXT_X_OFFSET, text_y, timeleft > 0 ? color1 : color2);
        open_gl_->DrawImage(tex_mega_, UI_IMAGE_X_OFFSET, image_y, 0.0f);        
      }
    }

    image_y += UI_IMAGE_Y_INCREMENT;
    text_y += UI_TEXT_Y_INCREMENT;
    s.str("");
  }  
  //}
  
  glPopMatrix();
}

//=======================================
void ExeQuakelive::CG_EntityEventDetour(centity_t* cent, vec3_t position) {
  //uint32_t es = cent;
  //uint32_t event = *reinterpret_cast<uint32_t*>(es+0x0BC) & 0x0FFFFFCFF;
  entityState_t *es = &cent->currentState;
  entity_event_t event = static_cast<entity_event_t>(es->event & ~EV_EVENT_BITS);
  std::stringstream s;

  if (event == EV_ITEM_RESPAWN || event == EV_ITEM_PICKUP) {
    int modelindex = -1;
    if (event == EV_ITEM_RESPAWN) {
      modelindex = es->modelindex;
    } else if (event == EV_ITEM_PICKUP) {
      modelindex = es->eventParam;
    }
    
    if (modelindex < 1 || modelindex >= bg_numitems_) {
      //Cmd_ExecuteString_("say Incorrect index");
    } else {
      //s << "say location: " << cent->lerpOrigin[0] << " " << cent->lerpOrigin[1] << " " << cent->lerpOrigin[2];
      //Cmd_ExecuteString_(s.str().c_str());
      gitem_t	*item = &bg_itemlist_[modelindex];
      // Filter only for yellow and red armor, and mega health
      if ((item->giType == IT_ARMOR && (item->quantity == 50 || item->quantity == 100)) ||
        item->giType == IT_HEALTH && item->quantity == 100) {
        TrackedItem *trackeditem = new TrackedItem(item->giType, item->quantity, cent->lerpOrigin, servertime_, event);
        trackeditem_manager_->Action(trackeditem);
      }
    }
  }

  CG_EntityEvent_(cent, position);
}

//=======================================
void ExeQuakelive::CG_DrawActiveFrameDetour(int serverTime, uint32_t stereoView, qboolean demoPlayback)
{
  static int x = 0;
  CG_DrawActiveFrame_(serverTime, stereoView, demoPlayback);
  
  if (x % 20 == 0) {
    servertime_ = serverTime;
  }

  if (x % 1000 == 0) {

  }
  x++;
}

//=======================================
void ExeQuakelive::CG_MapRestartDetour()
{
  trackeditem_manager_->Clear();
  CG_MapRestart_();
}

//=======================================
ExeQuakelive::ExeQuakelive(ExeLinkage* linkage,
  OpenGL *open_gl, 
  DetourXS* cgame_dllentry,
  DetourXS* cg_entityevent, 
  DetourXS* cg_drawactiveframe,
  DetourXS* cg_maprestart,
  TrackedItemManager* tim,
  glfont::GLFont* font,
  events::ConnectionSet* cs)
  : Exe(linkage),
  bg_itemlist_(NULL),
  tex_mega_(-1),
  tex_redarmor_(-1),
  tex_yellowarmor_(-1),
  servertime_(0)
{
  // Found in the CG_EntityEvent function in the EV_ITEM_PICKUP case
  // where it tests if bg_numItems is less than 0x36;
  bg_numitems_ = 0x36;

  open_gl_ = open_gl;
  trackeditem_manager_ = tim;
  font_ = font;
  cs_ = cs;
  cs_->Add(open_gl_->draw_event_.Register(*this, &ExeQuakelive::DrawScene));

  cgame_dllentry_ = cgame_dllentry;
  cg_entityevent_ = cg_entityevent;
  cg_drawactiveframe_ = cg_drawactiveframe;
  cg_maprestart_ = cg_maprestart;
}

//=======================================
void ExeQuakelive::Run() {
  HookQuakeliveDll();
  HookCgameDll();
}

//=======================================
void ExeQuakelive::Stop() {
  //try {
  UnhookCgameDll();
  delete cgame_dllentry_;
  delete cg_entityevent_;
  delete cg_drawactiveframe_;
  delete cg_maprestart_;

  open_gl_->Stop();

  delete trackeditem_manager_;

  font_->Destroy();
  delete font_;

  delete cs_;
  //} catch(...) {

  //}
}

//=======================================
void ExeQuakelive::HookQuakeliveDll()
{
  uint32_t quakelive_address = reinterpret_cast<uint32_t>(GetModuleHandle(L"quakelive.dll"));
  if (quakelive_address <= 0) {
    //MBA("Quakelive not found");
    linkage_->Exit();
    return;
  }

  //Com_Printf = static_cast<tCom_Printf>(reinterpret_cast<LPVOID>(quakelive_address + 0x9C9B0));
  //Cvar_Set2 = static_cast<tCvar_Set2>(reinterpret_cast<LPVOID>(quakelive_address + 0xA1B50));
  Cmd_ExecuteString_ = static_cast<Cmd_ExecuteStringType>(reinterpret_cast<LPVOID>(quakelive_address + QUAKELIVE_Cmd_ExecuteStringType));
  // Cmd_ExecuteString_("print \"QuakeSlash successfully loaded\"\n");
  //Cvar_Get2_ = static_cast<Cvar_GetType>(reinterpret_cast<LPVOID>(quakelive_address + 0xA1520));  
  Cvar_Get_ = static_cast<Cvar_GetType>(reinterpret_cast<LPVOID>(quakelive_address + QUAKELIVE_Cvar_Get));
}

//=======================================
// Only set the delay if we're inside a thread.
void ExeQuakelive::HookCgameDll(int delay)
{
  if (delay != 0) {
    boost::this_thread::sleep(boost::posix_time::seconds(delay));
  }

  HMODULE hmodule = GetModuleHandle(L"cgamex86.dll");
  if (hmodule == NULL) {
    return;
  }

  uint32_t cgame_address = reinterpret_cast<uint32_t>(hmodule);

  cgame_dllentry_thunk_ = thisthunk::wrap32<ExeQuakelive*>(
    this, 
    force_cast<void*>(&ExeQuakelive::Cgame_DllEntryDetour), 
    thisthunk::THISTHUNK_WINAPI,
    3,
    sizeof(HMODULE), 
    sizeof(DWORD),
    sizeof(LPVOID));
  cgame_dllentry_->Create(GetAddressOfEntryPoint(hmodule), cgame_dllentry_thunk_);
  Cgame_DllEntry_ = static_cast<Cgame_DllEntryType>(cgame_dllentry_->GetTrampoline());

  /*loadlibrary_thunk_ = thisthunk::wrap32<ExeQuakelive*>(
  this, 
  force_cast<void*>(&ExeQuakelive::LoadLibraryDetour), 
  thisthunk::THISTHUNK_WINAPI,
  1,
  sizeof(LPCSTR));
  loadlibrary_->Create(LoadLibraryA, loadlibrary_thunk_);
  LoadLibrary_ = static_cast<LoadLibraryType>(loadlibrary_->GetTrampoline());*/

  bg_itemlist_ = static_cast<gitem_t*>(reinterpret_cast<LPVOID>(cgame_address + CGAME_bg_itemlist_item_armor_shard - sizeof(gitem_t)));
  //Com_Printf_ = static_cast<Com_PrintfType>(reinterpret_cast<LPVOID>(cgame_address + 0x49470));
  //Com_Printf_("QuakeSlash LOADED");

  cg_entityevent_thunk_ = thisthunk::wrap32<ExeQuakelive*>(
    this, 
    force_cast<void*>(&ExeQuakelive::CG_EntityEventDetour), 
    thisthunk::THISTHUNK_CDECL,
    2,
    sizeof(centity_t*), 
    sizeof(vec3_t));  
  cg_entityevent_->Create(reinterpret_cast<LPVOID>(cgame_address + CGAME_CG_EntityEvent), cg_entityevent_thunk_);
  CG_EntityEvent_ = static_cast<CG_EntityEventType>(cg_entityevent_->GetTrampoline());

  cg_drawactiveframe_thunk_ = thisthunk::wrap32<ExeQuakelive*>(this, 
    force_cast<void*>(&ExeQuakelive::CG_DrawActiveFrameDetour), 
    thisthunk::THISTHUNK_CDECL, 
    3,
    sizeof(int),
    sizeof(uint32_t),
    sizeof(qboolean));
  cg_drawactiveframe_->Create(reinterpret_cast<LPVOID>(cgame_address + CGAME_CG_DrawActiveFrame), cg_drawactiveframe_thunk_);
  CG_DrawActiveFrame_ = static_cast<CG_DrawActiveFrameType>(cg_drawactiveframe_->GetTrampoline());

  cg_maprestart_thunk_ = thisthunk::wrap32<ExeQuakelive*>(this, 
    force_cast<void*>(&ExeQuakelive::CG_MapRestartDetour), 
    thisthunk::THISTHUNK_CDECL, 
    0);
  cg_maprestart_->Create(reinterpret_cast<LPVOID>(cgame_address + CGAME_CG_MapRestart), cg_maprestart_thunk_);
  CG_MapRestart_ = static_cast<CG_MapRestartType>(cg_maprestart_->GetTrampoline());

  open_gl_->Run();

  //Cmd_ExecuteString_("print \"QuakeSlash successfully loaded\"\n");
}

//=======================================
void ExeQuakelive::UnhookCgameDll()
{
  // Remove all of our hooks.
  cgame_dllentry_->Destroy();
  thisthunk::free(cgame_dllentry_thunk_);
  cg_entityevent_->Destroy();
  thisthunk::free(cg_entityevent_thunk_);
  cg_drawactiveframe_->Destroy();
  thisthunk::free(cg_drawactiveframe_thunk_);
  cg_maprestart_->Destroy();
  thisthunk::free(cg_maprestart_thunk_);
}

//=======================================
// We detour the cgame dll's entry point because it is
// possible that quake will reload it while quake is still running.
// At which point we just rehook all of our stuff.
BOOL ExeQuakelive::Cgame_DllEntryDetour(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    break;
  case DLL_THREAD_ATTACH:
    break;
  case DLL_THREAD_DETACH:
    break;
  case DLL_PROCESS_DETACH:
    UnhookCgameDll();
    trackeditem_manager_->Clear();
    // Rehook cgamedll after a delay of 3 seconds.
    boost::thread(&ExeQuakelive::HookCgameDll, this, 3);
    break;
  }
  return Cgame_DllEntry_(hModule, ul_reason_for_call, lpReserved);
}

//=======================================
//HMODULE ExeQuakelive::LoadLibraryDetour(LPCSTR lpLibFileName)
//{
//  if (strstr(lpLibFileName, "cgamex86.dll") == 0) {
//    // Just delete the thunks. No reason to destroy
//    // the detour because the Dll is unloaded anyway.
//    thisthunk::free(cg_entityevent_thunk_);
//    thisthunk::free(cg_drawactiveframe_thunk_);
//    thisthunk::free(cg_maprestart_thunk_);
//    HookCgameDll();
//  }
//  return LoadLibrary_(lpLibFileName);
//}

//---------------------------------------
class ExeQuakeliveFactory : public quakeslash::ExeFactory
{
public:
  //=======================================
  virtual bool ShouldCreate() {
    return (GetModuleHandle(L"plugin-container.exe") != NULL) ||
      (GetModuleHandle(L"quakeliveoffline.exe") != NULL);
  }

  //=======================================
  virtual Exe* Create(ExeLinkage* linkage) {
    return new ExeQuakelive(linkage,
      createOpenGL(),
      new DetourXS, 
      new DetourXS, 
      new DetourXS, 
      new DetourXS, 
      new TrackedItemManager, 
      new glfont::GLFont, 
      new events::ConnectionSet);
  }
};

//=======================================
//BOOST_EXTENSION_TYPE_MAP_FUNCTION {
void exeQuakeliveRegisterPlugin(boost::extensions::type_map& types) {
  std::map<std::string, boost::extensions::factory<ExeFactory>>& exe_factories(types.get());
  exe_factories["Quakelive"].set<ExeQuakeliveFactory>();
}
};
