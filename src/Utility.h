#ifndef _UTILITY
#define _UTILITY

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "GLTexture.h"

struct ApplicationData
{
	char*				CompanyName			= "YourCompanyName";
	char*				ProductName			= "ImGui-Boilerplate";
	char*				GuiSessionPath		= nullptr;
	char*				SettingsConfigPath	= nullptr;
	ImGuiWindowFlags	WindowFlags			= 0;
	GLTexture			IconAtlas;
	GLFWwindow*	Window;
};

namespace Util
{
	char* GetConfigPath(const char* CompanyName, const char* ProductName, const char* FileName = "");
}


#endif 