#include "ApplicationBase.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
	#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#include "Logging.h"
LOGGER(logger, ApplicationBase)


ApplicationBase* ApplicationBase::_instance = nullptr;
ApplicationBase::CreateInstanceFunction ApplicationBase::CreateInstance = nullptr;
int ApplicationBase::_exitCode = 0;

static void glfw_error_callback(int error, const char* description)
{
	//fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int ApplicationBase::GlobalMain(int argc, const char* argv[])
{
	_instance = CreateInstance();
	// TODO: Guard _instance
	_exitCode = _instance->Main(argc, argv);
	_instance->InternalInitialize();

	return _exitCode;
}

void ApplicationBase::InternalInitialize()
{
	SetupWindow();
	InitializeImGui();
	Initialize();

	MainLoop();
}

void ApplicationBase::SetupWindow()
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if(!glfwInit())
	{
		return;
	}

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	_glslVersion = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	 _glslVersion = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	_glslVersion = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	_glfwWindow = glfwCreateWindow(1280, 720, GetWindowTitle().c_str(), NULL, NULL);
	if(_glfwWindow == nullptr)
	{
		return;
	}

	glfwMakeContextCurrent(_glfwWindow);
	glfwSwapInterval(1); // Enable vsync
}

void ApplicationBase::DrawImGuiBegin()
{
	// Poll and handle events (inputs, window resize, etc.)
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	glfwPollEvents();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ApplicationBase::MainLoop()
{
	bool bWindowWantsToClose = false;
	while(!_bShouldQuitMainLoop && !bWindowWantsToClose)
	{
		DrawImGuiBegin();
		Tick(0.f);
		InternalDrawImGui(0.f);
		DrawImGuiEnd();

		bWindowWantsToClose = glfwWindowShouldClose(_glfwWindow);
	}

	MainLoopExit();
}

void ApplicationBase::InternalDrawImGui(double deltaTime)
{
	if(_bShowDemoWindow)
		ImGui::ShowDemoWindow(&_bShowDemoWindow);

	DrawImGui(deltaTime);
}

void ApplicationBase::DrawImGuiEnd()
{
	// Rendering
	ImGui::Render();
	int displayWidth, displayHeight = 0;
	glfwGetFramebufferSize(_glfwWindow, &displayWidth, &displayHeight);
	glViewport(0, 0, displayWidth, displayHeight);
	glClearColor(_clearColor.x * _clearColor.w, _clearColor.y * _clearColor.w, _clearColor.z * _clearColor.w, _clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(_glfwWindow);
}

void ApplicationBase::MainLoopExit()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

void ApplicationBase::InitializeImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_glfwWindow, true);
	ImGui_ImplOpenGL3_Init(_glslVersion.c_str());
}
