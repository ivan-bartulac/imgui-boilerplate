#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <clocale>
#include <string>
#include <comdef.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utility.h"
#include "GLTexture.h"

struct ApplicationData
{
	char*		CompanyName			= "YourCompanyName";
	char*		ProductName			= "ImGui-Boilerplate";
	char*		GuiSessionPath		= nullptr;
	char*		SettingsConfigPath	= nullptr;
	GLTexture	IconAtlas;
	GLFWwindow*	Window;
};
ApplicationData GAppData;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void InitializeApplication()
{
	GAppData.GuiSessionPath = GetConfigPath(GAppData.CompanyName, GAppData.ProductName, "GuiSession.ini");
	GAppData.SettingsConfigPath = GetConfigPath(GAppData.CompanyName, GAppData.ProductName, "Settings.ini");
}

void InitializeGL()
{
	GAppData.IconAtlas.Load("IconAtlas.tga");
}

void UpdateGUI()
{	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Hello, world!");
		 ImGui::Text("Hello from another window!");
		 ImGui::Text("press button to quit!");
		 
		if (ImGui::Button("Quit"))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}

		float TileSize = 64.f;
		float NumVerticalTiles = GAppData.IconAtlas.Width / TileSize;
		float NumHorizontalTiles = GAppData.IconAtlas.Height / TileSize;
		float TileRowIndex = 0;
		float TileColIndex = 0;
		
		ImGui::PushID("ImageButton1");
		if (ImGui::ImageButton((void*)(intptr_t)GAppData.IconAtlas.Id, ImVec2(TileSize, TileSize), 
			ImVec2(TileRowIndex * (1 / NumVerticalTiles), TileColIndex * (1 / NumHorizontalTiles)), 
			ImVec2((TileRowIndex + 1) * (1 / NumVerticalTiles), (TileColIndex + 1) * (1 / NumHorizontalTiles)), 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		ImGui::PushID("ImageButton2");
		TileRowIndex = 1;
		TileColIndex = 0;
		if (ImGui::ImageButton((void*)(intptr_t)GAppData.IconAtlas.Id, ImVec2(TileSize, TileSize), 
			ImVec2(TileRowIndex * (1 / NumVerticalTiles), TileColIndex * (1 / NumHorizontalTiles)), 
			ImVec2((TileRowIndex + 1) * (1 / NumVerticalTiles), (TileColIndex + 1) * (1 / NumHorizontalTiles)), 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

	ImGui::End();

#ifdef _DEBUG
	ImGui::ShowDemoWindow();
#endif
}

int main(void)
{
	InitializeApplication();

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	GAppData.Window = glfwCreateWindow(800, 600, GAppData.ProductName, NULL, NULL);
	if (!GAppData.Window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(GAppData.Window, key_callback);

	glfwMakeContextCurrent(GAppData.Window);
	
	if (gl3wInit())
	{
		fprintf(stderr, "failed to initialize OpenGL\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (!gl3wIsSupported(3, 2))
	{
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSwapInterval(1);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.IniFilename = GAppData.GuiSessionPath;
	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(GAppData.Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	InitializeGL();

	while (!glfwWindowShouldClose(GAppData.Window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UpdateGUI();

		ImGui::Render();

		int width, height;
		glfwGetFramebufferSize(GAppData.Window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(GAppData.Window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(GAppData.Window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
