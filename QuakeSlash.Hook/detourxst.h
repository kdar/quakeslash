// Copyright 2012 Kevin Darlington

// !! NOT FINISHED !!

#ifndef DETOURXST_H_
#define DETOURXST_H_

#include "detourxs.h"
#include "thisthunk.h"

class DetourXST : public DetourXS
{
public:
  BOOL Create(const LPVOID lpFuncOrig, void *object, const LPVOID lpFuncDetour, thisthunk::CallingConvention convention)
  {
    thunk_ = thisthunk::wrap32<void*>(
      object, 
      lpFuncDetour, 
      thisthunk::THISTHUNK_WINAPI, 
      1, 
      sizeof(HDC));
  }

  BOOL Destroy()
  {
    DetourXS::Destroy();

  }

private:
  void *thunk_;
};

#endif
