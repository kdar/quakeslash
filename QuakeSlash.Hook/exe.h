// Copyright 2012 Kevin Darlington

#ifndef EXE_H_
#define EXE_H_

namespace quakeslash {
  
//---------------------------------------
class ExeLinkage {
  public:
   ExeLinkage() : exit_(false) {}
   void Exit()
   { exit_ = true; }

  public:
    bool exit_;
};

//---------------------------------------
class Exe {
 public:
  Exe(ExeLinkage* linkage)
  : linkage_(linkage)
  {
  }
  virtual ~Exe() {}
  virtual void Run() = 0;
  virtual void Stop() = 0;

 protected:
  ExeLinkage* linkage_;
};

//---------------------------------------
class ExeFactory {
 public:
  virtual Exe* Create(ExeLinkage *linkage) = 0;
  virtual bool ShouldCreate() = 0;
};
};

#endif  // EXE_H_
