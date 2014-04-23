#ifndef _FORCECAST_H_
#define _FORCECAST_H_

template<class Dest, class Src>
Dest force_cast(Src src)
{
  union
  {
    Dest d;
    Src s;
  } convertor;

  convertor.s = src;
  return convertor.d;
}
#endif //_FORCECAST_H_