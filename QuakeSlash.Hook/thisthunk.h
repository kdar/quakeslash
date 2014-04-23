// Copyright 2012 Kevin Darlington

#ifndef THISTHUNK_H_
#define THISTHUNK_H_

#include <AsmJit/Assembler.h>
#include <AsmJit/MemoryManager.h>
#include <cstdarg>

#include "forcecast.h"

namespace thisthunk {
enum CallingConvention {
 THISTHUNK_STDCALL = 1,
 THISTHUNK_WINAPI = 1,
 THISTHUNK_CDECL = 2
};

//=======================================
// Wraps a class member function inside a run-time generated function
// that can be called as a C-style callback.
// TODO: Could probably optimize the ASM and eliminate instructions that
// aren't needed.
// Example:
//
// class Test {
// public:
//   void callme(int x) { std::cout << x << std::endl; }
// };
//
// Test t;
// void *functionPointer = wrap32<Test*>(&t, force_cast<void*>(&Test::callme), thisthunk::THISTHUNK_WINAPI, 1, sizeof(int));
// typedef void (*FunctionType)(int);
// FunctionType func = static_cast<FunctionType>(functionPointer);
// (*func)(5);
template <typename T>
void* wrap32(T t, void* func, CallingConvention wrap_calling_convention, int arg_count, ...)
{  
  using namespace AsmJit;

  Assembler a;
  // Arguments offset: 4 (first argument) + 4 (push ebp instructions).
  const int arg_offset = 4 + 4;

  // Prolog. Save things.
  a.push(ebp);
  a.mov(ebp, esp);
  a.push(esi);
  a.push(edi);

  // We need to re-push the arguments in reverse order from when
  // we get them. I feel like this could be done in a better way.
  if (arg_count != 0) {
    va_list ap;
    va_start(ap, arg_count);

    Mem *argvalues = new Mem[arg_count];
    for (int x = 0; x < arg_count; ++x) {
      if (x == 0) {
        argvalues[x] = dword_ptr(ebp, arg_offset + 0);
      } else {
        // the va_arg(ap, int) here will return the x-1 indexed argument
        // because of the if statement above skipping the first index;
        argvalues[x] = dword_ptr(ebp, arg_offset + va_arg(ap, int));
      }
    }

    // push arguments in reverse order
    for (int x = arg_count-1; x >= 0; --x) {
      a.mov(edi, argvalues[x]);
      a.push(edi);
    }

    delete argvalues;

    va_end(ap);
  }

  // Call the function we're mapping. This pointer
  // to the object is set inside ecx (thiscall convention).
  // The callee cleans up the stack.
  a.mov(ecx, force_cast<uint32_t>(t));
  a.call(force_cast<uint32_t>(func));

  // Epilog. Restore things.
  a.pop(edi);
  a.pop(esi);
  a.mov(esp, ebp);
  a.pop(ebp);

  switch(wrap_calling_convention) {
  case THISTHUNK_CDECL:
    // cdecl says the caller cleans up the stack.
    a.ret();
    break;

  case THISTHUNK_STDCALL:
    // Add up the total argument sizes.
    int totalsize = 0;
    va_list ap2;
    va_start(ap2, arg_count);
    for (int x = 0; x < arg_count; x++) { 
      totalsize += va_arg(ap2, int);
    }
    va_end(ap2);

    // stdcall says the callee cleans up the stack.
    a.ret(totalsize);
    break;
  }

  return a.make();
}

//=======================================
inline void free(void *p) {
  AsmJit::MemoryManager::getGlobal()->free(p);
}

};

#endif
