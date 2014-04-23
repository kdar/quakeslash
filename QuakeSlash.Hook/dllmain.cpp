// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>

#define MB(s) MessageBox(NULL, s, NULL, MB_OK);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
    //HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE())
    break;
	case DLL_THREAD_ATTACH:
    break;
	case DLL_THREAD_DETACH:
    break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//#if _MSC_VER >= 1300    // for VC 7.0
//// from ATL 7.0 sources
//#ifndef _delayimp_h
//extern "C" IMAGE_DOS_HEADER __ImageBase;
//#endif
//#endif

//HMODULE GetCurrentModule()
//{
//#if _MSC_VER < 1300    // earlier than .NET compiler (VC 6.0)
//
//  // Here's a trick that will get you the handle of the module
//  // you're running in without any a-priori knowledge:
//  // http://www.dotnet247.com/247reference/msgs/13/65259.aspx
//
//  MEMORY_BASIC_INFORMATION mbi;
//  static int dummy;
//  VirtualQuery( &dummy, &mbi, sizeof(mbi) );
//
//  return reinterpret_cast<HMODULE>(mbi.AllocationBase);
//
//#else    // VC 7.0
//
//  // from ATL 7.0 sources
//
//  return reinterpret_cast<HMODULE>(&__ImageBase);
//#endif
//}