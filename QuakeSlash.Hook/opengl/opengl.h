// Copyright 2012 Kevin Darlington

#ifndef OPENGL_H_
#define OPENGL_H_

#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "../event/event.h"
#include "../opengl/glfont2.h"

class DetourXS;

namespace quakeslash {
typedef void (WINAPI* SwapBuffersType)(HDC hDC);

struct OpenGLState
{
  // Previous matrix mode
  int iPreviousMatrixMode;
  // Previous GL_DEPTH_TEST mode
  GLboolean gblDepthTest;
  int iDepthFunc;
  // Previous GL_LIGHTING mode
  GLboolean gblLighting;
  // Previous GL_BLEND value
  GLboolean gblBlend;
  // Previous texture modes
  GLboolean gblTexture1D, gblTexture2D;
  // Previous GL_DEPTH_TEST mode
  GLboolean gblAlphaTest;
  int iAlphaFunc;
  GLclampf fAlphaRef;
};

//---------------------------------------
class OpenGL
{
public:
  OpenGL() : running_(false) {}
  void Initialize(DetourXS* swap_buffers);

  void Run();
  void Stop();

  void DrawScene();
  void DrawText(char* text, glfont::GLFont& font, float x, float y, float color[3]);
  void DrawImage(GLuint texture, float x, float y, float z);
  GLuint LoadTexture(char* file_name);
  GLuint LoadTexture(unsigned char* data, int size);
  void Render();

  OpenGLState SaveState();
  void RestoreState(OpenGLState state);

  void SwapBuffersDetour(HDC hDC);

public:
  DetourXS* swap_buffers_;
  void* swap_buffers_thunk_;
  SwapBuffersType SwapBuffers_;  

  mutable events::Event<> draw_event_;

private:
  bool running_;
};

OpenGL* createOpenGL();
};

#endif