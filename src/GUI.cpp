#include "GUI.h"
#include "Utility.h"

#include <imgui.h>
#include <string>

extern ApplicationData GAppData;


// --------------------------------------------------------------------
// Data
// --------------------------------------------------------------------
const char* TestList[] =
{
	"AAAA",
	"BBBB",
	"CCCC",
	"DDDD",
};

// --------------------------------------------------------------------
// Local Function Declaration
// --------------------------------------------------------------------
static void MakeMainMenuBar();
static void MakeHeaderGroup();
static void MakeIconTab();
static void MakeComboTab();
static void MakeOptionsTab();

// --------------------------------------------------------------------
// Functions
// --------------------------------------------------------------------
void GUI::OnInitializeApplication()
{
	GAppData.CompanyName		= "YourCompanyName";
	GAppData.ProductName		= "ImGui-Boilerplate";
	GAppData.GuiSessionPath		= Util::GetConfigPath(GAppData.CompanyName, GAppData.ProductName, "GuiSession.ini");
	GAppData.SettingsConfigPath	= Util::GetConfigPath(GAppData.CompanyName, GAppData.ProductName, "Settings.ini");
	GAppData.WindowFlags		= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

}

// --------------------------------------------------------------------
void GUI::OnInitializeGL()
{
	ImGui::StyleColorsDark();
	GAppData.IconAtlas.Load("IconAtlas.tga");
}

// --------------------------------------------------------------------
void GUI::OnTick()
{
	MakeMainMenuBar();
	
	ImGui::Begin("Window", NULL, GAppData.WindowFlags);
		MakeHeaderGroup();
		if (ImGui::BeginTabBar("##TabBar"))
		{
			MakeIconTab();
			MakeComboTab();
			MakeOptionsTab();

			ImGui::EndTabBar();
		}

	ImGui::End();

#ifdef _DEBUG
	ImGui::ShowDemoWindow();
#endif
}

// --------------------------------------------------------------------
void GUI::OnClosing()
{

}

// --------------------------------------------------------------------
// Local Function Definition
// --------------------------------------------------------------------
void MakeMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "CTRL+N")) {}
			if (ImGui::MenuItem("Open", "CTRL+O")) {}
			if (ImGui::MenuItem("Save", "CTRL+S")) {}
			if (ImGui::MenuItem("SaveAs", "CTRL+SHIFT+S")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Quit", "CTRL+Q")) {glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);}
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
}

// --------------------------------------------------------------------
void MakeHeaderGroup()
{
	static int HeaderCombo[3] = {0};

	GLTextureRegion HeaderImage = GLTextureRegion(GAppData.IconAtlas, 256, 128, 0, 3);
	ImGui::BeginGroup();
		ImGui::Image((void*)HeaderImage.Texture.Id, {HeaderImage.Width, HeaderImage.Height}, 
			{HeaderImage.U0, HeaderImage.V0}, {HeaderImage.U1, HeaderImage.V1});

		ImGui::Combo("Header 1", &HeaderCombo[0], TestList, IM_ARRAYSIZE(TestList));
		ImGui::Combo("Header 2", &HeaderCombo[1], TestList, IM_ARRAYSIZE(TestList));
		ImGui::Combo("Header 3", &HeaderCombo[2], TestList, IM_ARRAYSIZE(TestList));
	ImGui::EndGroup();
}

// --------------------------------------------------------------------
void MakeIconTab()
{
	if (ImGui::BeginTabItem("Icon Group"))
	{
		ImGui::Text("Icon Group");

		float TileSize = 64.f;
		
		GLTextureRegion BtnIcon1 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 0, 0);
		ImGui::PushID("ImageButton1");
		if (ImGui::ImageButton((void*)BtnIcon1.Texture.Id, {BtnIcon1.Width, BtnIcon1.Height}, 
			{BtnIcon1.U0, BtnIcon1.V0}, {BtnIcon1.U1, BtnIcon1.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon2 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 1, 0);
		ImGui::PushID("ImageButton2");
		if (ImGui::ImageButton((void*)BtnIcon2.Texture.Id, {BtnIcon2.Width, BtnIcon2.Height}, 
			{BtnIcon2.U0, BtnIcon2.V0}, {BtnIcon2.U1, BtnIcon2.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon3 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 2, 0);
		ImGui::PushID("ImageButton3");
		if (ImGui::ImageButton((void*)BtnIcon3.Texture.Id, {BtnIcon3.Width, BtnIcon3.Height}, 
			{BtnIcon3.U0, BtnIcon3.V0}, {BtnIcon3.U1, BtnIcon3.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon4 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 3, 0);
		ImGui::PushID("ImageButton4");
		if (ImGui::ImageButton((void*)BtnIcon4.Texture.Id, {BtnIcon4.Width, BtnIcon4.Height}, 
			{BtnIcon4.U0, BtnIcon4.V0}, {BtnIcon4.U1, BtnIcon4.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		GLTextureRegion BtnIcon5 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 4, 0);
		ImGui::PushID("ImageButton5");
		if (ImGui::ImageButton((void*)BtnIcon5.Texture.Id, {BtnIcon5.Width, BtnIcon5.Height}, 
			{BtnIcon5.U0, BtnIcon5.V0}, {BtnIcon5.U1, BtnIcon5.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon6 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 5, 0);
		ImGui::PushID("ImageButton6");
		if (ImGui::ImageButton((void*)BtnIcon6.Texture.Id, {BtnIcon6.Width, BtnIcon6.Height}, 
			{BtnIcon6.U0, BtnIcon6.V0}, {BtnIcon6.U1, BtnIcon6.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon7 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 6, 0);
		ImGui::PushID("ImageButton7");
		if (ImGui::ImageButton((void*)BtnIcon7.Texture.Id, {BtnIcon7.Width, BtnIcon7.Height}, 
			{BtnIcon7.U0, BtnIcon7.V0}, {BtnIcon7.U1, BtnIcon7.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::SameLine();

		GLTextureRegion BtnIcon8 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 7, 0);
		ImGui::PushID("ImageButton8");
		if (ImGui::ImageButton((void*)BtnIcon8.Texture.Id, {BtnIcon8.Width, BtnIcon8.Height}, 
			{BtnIcon8.U0, BtnIcon8.V0}, {BtnIcon8.U1, BtnIcon8.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		GLTextureRegion BtnIcon9 = GLTextureRegion(GAppData.IconAtlas, TileSize, TileSize, 0, 1);
		ImGui::PushID("ImageButton9");
		if (ImGui::ImageButton((void*)BtnIcon9.Texture.Id, {BtnIcon9.Width, BtnIcon9.Height}, 
			{BtnIcon9.U0, BtnIcon9.V0}, {BtnIcon9.U1, BtnIcon9.V1}, 0))
		{
			glfwSetWindowShouldClose(GAppData.Window, GLFW_TRUE);
		}
		ImGui::PopID();

		ImGui::EndTabItem();
	}
}

// --------------------------------------------------------------------
void MakeComboTab()
{
	static int ParamsCombo[3] = {0};

	if (ImGui::BeginTabItem("Combos"))
	{
		ImGui::Combo("Combo 1", &ParamsCombo[0], TestList, IM_ARRAYSIZE(TestList));
		ImGui::Combo("Combo 2", &ParamsCombo[1], TestList, IM_ARRAYSIZE(TestList));
		ImGui::Combo("Combo 3", &ParamsCombo[2], TestList, IM_ARRAYSIZE(TestList));

		ImGui::EndTabItem();
	}
}

// --------------------------------------------------------------------
void MakeOptionsTab()
{
	if (ImGui::BeginTabItem("Options"))
	{
		ImGui::Button("Button 1");
		ImGui::Button("Button 2");
		ImGui::Button("Button 3");

		ImGui::EndTabItem();
	}
}