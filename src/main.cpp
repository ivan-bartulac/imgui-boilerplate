#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "Utility.h"
#include "GUI.h"

ApplicationData GAppData;

static void ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	GUI::OnInitializeApplication();

	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}

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
		fprintf(stderr, "Failed to Create Window.\n");
		glfwTerminate();
		return 1;
	}

	glfwSetKeyCallback(GAppData.Window, KeyCallback);

	glfwMakeContextCurrent(GAppData.Window);
	
	if (gl3wInit())
	{
		fprintf(stderr, "failed to initialize OpenGL\n");
		glfwTerminate();
		return 1;
	}

	if (!gl3wIsSupported(3, 2))
	{
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		glfwTerminate();
		return 1;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSwapInterval(1);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.IniFilename = GAppData.GuiSessionPath;
	
	ImGui_ImplGlfw_InitForOpenGL(GAppData.Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	GUI::OnInitializeGL();

	while (!glfwWindowShouldClose(GAppData.Window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		GUI::OnTick();

		ImGui::Render();

		int width, height;
		glfwGetFramebufferSize(GAppData.Window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(GAppData.Window);
	}

	GUI::OnClosing();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(GAppData.Window);
	glfwTerminate();
	return 0;
}
