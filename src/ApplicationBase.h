#pragma once

#include "Common.h"

#include <EASTL/string.h>
#include <imgui.h>

struct GLFWwindow;


class ApplicationBase
{
public:
	static int GlobalMain(int argc, const char* argv[]);

	// Dynamically swapped out at the start of the process
	using CreateInstanceFunction = ApplicationBase* (*)();
	static CreateInstanceFunction CreateInstance;

	static ApplicationBase* Instance() { return _instance; }
	template<class T>
	static T* Instance() { return dynamic_cast<T*>(_instance); }

	virtual ea::string& GetWindowTitle()
	{
		static ea::string title("");
		return title;
	}

	virtual int Main(int argc, const char* argv[]) { return 0; }
	virtual void Initialize() {}
	virtual void Tick(double deltaTime) {}
	virtual void DrawImGui(double deltaTime) {}

protected:
	void InternalInitialize();
	void SetupWindow();

	void InitializeImGui();
	void DrawImGuiBegin();
	virtual void MainLoop();
	void InternalDrawImGui(double deltaTime);
	void DrawImGuiEnd();

	void MainLoopExit();

protected:
	static int _exitCode;

	bool _bShouldQuitMainLoop = false;
	GLFWwindow* _glfwWindow = nullptr;
	ea::string _glslVersion = "#version 130";
	bool _bShowDemoWindow = true;
	ImVec4 _clearColor = { 0.1f, 0.1f, 0.1f, 1.f };

private:
	static ApplicationBase* _instance;
};