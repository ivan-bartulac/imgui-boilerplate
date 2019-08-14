#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <clocale>
#include <string>
#include <comdef.h>
#include <stdlib.h>
#include <stdio.h>

#include "GetConfigPath.h"

static char* CompanyName = "YourCompanyName";
static char* ProductName = "ImGui-Boilerplate";

static int AtlasWith, AtlasHeight, AtlasChannels;
static GLuint AtlasTextureID;
static GLFWwindow* window;
static char* GuiSessionPath = nullptr;
static char* SettingsConfigPath = nullptr;

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
	GuiSessionPath = GetConfigPath(CompanyName, ProductName, "GuiSession.ini");
	SettingsConfigPath = GetConfigPath(CompanyName, ProductName, "Settings.ini");
}

void Initialize()
{
	unsigned char *AtlasPixelData = stbi_load("IconAtlas.tga", &AtlasWith, &AtlasHeight, &AtlasChannels, 4);

	glGenTextures(1, &AtlasTextureID);
	glBindTexture(GL_TEXTURE_2D, AtlasTextureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AtlasWith, AtlasHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, AtlasPixelData);

    glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(AtlasPixelData);
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
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		float TileSize = 64.f;
		float NumVerticalTiles = AtlasWith / TileSize;
		float NumHorizontalTiles = AtlasHeight / TileSize;
		float TileRowIndex = 0;
		float TileColIndex = 0;
		
		ImGui::PushID("ImageButton1");
		if (ImGui::ImageButton((void*)(intptr_t)AtlasTextureID, ImVec2(TileSize, TileSize), 
			ImVec2(TileRowIndex * (1 / NumVerticalTiles), TileColIndex * (1 / NumHorizontalTiles)), 
			ImVec2((TileRowIndex + 1) * (1 / NumVerticalTiles), (TileColIndex + 1) * (1 / NumHorizontalTiles)), 0))
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		ImGui::PushID("ImageButton2");
		TileRowIndex = 1;
		TileColIndex = 0;
		if (ImGui::ImageButton((void*)(intptr_t)AtlasTextureID, ImVec2(TileSize, TileSize), 
			ImVec2(TileRowIndex * (1 / NumVerticalTiles), TileColIndex * (1 / NumHorizontalTiles)), 
			ImVec2((TileRowIndex + 1) * (1 / NumVerticalTiles), (TileColIndex + 1) * (1 / NumHorizontalTiles)), 0))
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
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

	window = glfwCreateWindow(800, 600, ProductName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	
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
	io.IniFilename = GuiSessionPath;
	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	Initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UpdateGUI();

		ImGui::Render();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
