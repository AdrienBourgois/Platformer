#ifndef IMGUI_IMPL_H
#define IMGUI_IMPL_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "imgui.h"
#include <GL/gl.h>
#include "Device.h"

namespace id {

class Device;

class imgui_impl
{
public:
	static bool Init();
	static void Shutdown();
	static void NewFrame(Device* dev);
	
	static void RenderDrawLists(ImDrawData* draw_data);
	
	static bool CreateDeviceObjects();
	
	static void CreateFontsTexture();
	static bool ProcessEvent(SDL_Event* event);
private:
	static GLuint g_FontTexture;
	static int g_ShaderHandle;
	static int g_VertHandle;
	static int g_FragHandle;
	static int g_AttribLocationTex;
	static int g_AttribLocationProjMtx;
	static int g_AttribLocationPosition;
	static int g_AttribLocationUV;
	static int g_AttribLocationColor;
	static unsigned int g_VboHandle;
	static unsigned int g_VaoHandle;
	static unsigned int g_ElementsHandle;
	
	static double g_Time;
	static bool   g_MousePressed[3];
	static float  g_MouseWheel;
};

} // namespace id

#endif
