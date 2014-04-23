#pragma comment(lib, "opengl32.lib")

//#include "GL\freeglut.h"
#include "SOIL.h"

#include "../DetourXS/detourxs.h"
#include "../thisthunk.h"
#include "glfont2.h"
#include "opengl.h"

#define MB(s) MessageBox(NULL, s, NULL, MB_OK);
#define MBA(s) MessageBoxA(NULL, s, NULL, MB_OK);

namespace quakeslash {
//=======================================
GLuint OpenGL::LoadTexture(char *file_name)
{
  return SOIL_load_OGL_texture(
    file_name,
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT
    //SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
}

//=======================================
GLuint OpenGL::LoadTexture(unsigned char* data, int size)
{
  return SOIL_load_OGL_texture_from_memory(
    data,
    size,
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS
    );
}

//=======================================
void OpenGL::DrawText(char* text, glfont::GLFont& font, float x, float y, float color[3])
{
  OpenGLState state = SaveState();

  //glColor3f(color[0], color[1], color[2]);

  // Set the text position
  //glLoadIdentity();
  //glRasterPos2f(x, y);  
  //glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<unsigned char *>(text));

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  
  font.Begin();
  font.DrawString(text, 0.003F, x, y, color, color);

  glPopMatrix();

  RestoreState(state);
}

//=======================================
void OpenGL::DrawImage(GLuint texture, float x, float y, float z)
{
  OpenGLState state = SaveState();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, texture);  

  glPushMatrix();
  
  glTranslatef(x, y, z); // position of texture.

  glScalef( 0.1f, 0.1f, 0.1f );
  glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
  glNormal3f( 0.0f, 0.0f, 1.0f );  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex2f(-1.0f, 0.0f);
  glEnd();  
  glPopMatrix();

  RestoreState(state);
}

//=======================================
OpenGLState OpenGL::SaveState()
{
  OpenGLState state;

  // Save the GL_DEPTH_TEST mode
  state.gblDepthTest = glIsEnabled(GL_DEPTH_TEST);
  glGetIntegerv(GL_DEPTH_FUNC, &state.iDepthFunc);

  // Save the GL_DEPTH_TEST mode
  state.gblAlphaTest = glIsEnabled(GL_ALPHA_TEST);
  glGetIntegerv(GL_ALPHA_TEST_FUNC, &state.iAlphaFunc);
  glGetFloatv(GL_ALPHA_TEST_REF, &state.fAlphaRef);

  // Save the GL_LIGHTING mode
  state.gblLighting = glIsEnabled(GL_LIGHTING);

  // Save the GL_BLEND mode
  state.gblBlend = glIsEnabled(GL_BLEND);

  // Save the previous texture modes
  state.gblTexture1D = glIsEnabled(GL_TEXTURE_1D);
  state.gblTexture2D = glIsEnabled(GL_TEXTURE_2D);

  // Enable the depth test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);

  // Disable the lighting
  glDisable(GL_LIGHTING);

  // Disable the blending
  glDisable(GL_BLEND);

  // Disable the texture modes
  glDisable(GL_TEXTURE_1D | GL_TEXTURE_2D);

  // Save the matrix mode
  glGetIntegerv(GL_MATRIX_MODE, &state.iPreviousMatrixMode);

  // Set the projection matrix
  glMatrixMode(GL_PROJECTION);

  // Save the previous projection matrix
  glPushMatrix();  

  // Set the new projection matrix
  glLoadIdentity();
  glOrtho(10.0f, 10.0f, 10.0f, -10.0f, -1.0, 1.0);

  // Set the model-view matrix
  glMatrixMode(GL_MODELVIEW);

  // Save the model-view matrix
  glPushMatrix();

  // Set the new model-view matrix
  glLoadIdentity();

  return state;
}

//=======================================
void OpenGL::RestoreState(OpenGLState state)
{
  // Restore the projection matrix
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  // Restore the model-view matrix
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  // Restore the previous matrix mode
  glMatrixMode(state.iPreviousMatrixMode);

  // Restore the GL_DEPTH_TEST
  if (state.gblDepthTest == GL_TRUE)
    glEnable(GL_DEPTH_TEST);
  else
    glDisable(GL_DEPTH_TEST);
  glDepthFunc(state.iDepthFunc);

  // Restore the GL_DEPTH_TEST
  if (state.gblAlphaTest == GL_TRUE)
    glEnable(GL_ALPHA_TEST);
  else
    glDisable(GL_ALPHA_TEST);
  glAlphaFunc(state.iAlphaFunc, state.fAlphaRef);

  // Restore the GL_LIGHTING mode
  if (state.gblLighting == GL_TRUE)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  // Restore the GL_BLEND mode
  if (state.gblBlend == GL_TRUE)
    glEnable(GL_BLEND);
  else
    glDisable(GL_BLEND);

  // Restore the previous texture modes
  if (state.gblTexture1D == GL_TRUE)
    glEnable(GL_TEXTURE_1D);
  else
    glDisable(GL_TEXTURE_2D);

  if (state.gblTexture2D == GL_TRUE)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);
}

//=======================================
// Draws the overlay to screen
void OpenGL::Render()
{
  OpenGLState state = SaveState();

  // Draw our scene
  //DrawScene();
  draw_event_.Invoke();

  RestoreState(state);
}

//=======================================
void OpenGL::SwapBuffersDetour(HDC hDC) 
{
  //static bool iInitialize = false;
  //if (!iInitialize)
  //{
  //  iInitialize = true;
  //  
  //  std::istringstream s()
  //  if (!myfont.Create("aero.glf", 0)) {
  //    //MB(L"FIALED");
  //  }

  ////  // Useless initialization stuff to make Glut happy.
  ////  char* argv[] = {"some","stuff"};    int argc=2;
  ////  glutInit(&argc,argv);   
  ////  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  ////  glutInitWindowPosition(100,100);
  ////  glutInitWindowSize(800,600);
  //}

  Render();

  SwapBuffers_(hDC);
}

//=======================================
void OpenGL::Initialize(DetourXS* swap_buffers)
{
  swap_buffers_ = swap_buffers;
}

//=======================================
void OpenGL::Run() {
  if (running_) {
    return;
  }

  swap_buffers_thunk_ = thisthunk::wrap32<OpenGL*>(
    this, 
    force_cast<void*>(&OpenGL::SwapBuffersDetour), 
    thisthunk::THISTHUNK_WINAPI, 
    1, 
    sizeof(HDC));

  swap_buffers_->Create(&::SwapBuffers, swap_buffers_thunk_);
  SwapBuffers_ = static_cast<SwapBuffersType>(swap_buffers_->GetTrampoline());

  running_ = true;
}

//=======================================
void OpenGL::Stop() {
  swap_buffers_->Destroy();
  thisthunk::free(swap_buffers_thunk_);  
  running_ = false;
}

//=======================================
OpenGL* createOpenGL()
{
  OpenGL* opengl = new OpenGL;
  opengl->Initialize(new DetourXS);
  return opengl;
}
};