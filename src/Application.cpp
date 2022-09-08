#include "Application.h"

#include "SimpleBench.h"

#include <EASTL/vector.h>
#include <SkeletonMinRes/Loader.h>
#include <random>

#include "Logging.h"
LOGGER(logger, Application)


// Load motivations raw data, then on application initialize we will then split the data into lines
// and keep in memory.
static SkeletonMinRes::Resource resMotivations = LOAD_RESOURCE(Data_motivations_txt);
static ea::vector<ea::string> motivations;

static std::random_device randDev;
static std::mt19937 rng(randDev());

int RandomNumber(int min, int max)
{
	std::uniform_int_distribution r(min, max);
	return r(rng);
}

static SimpleBench simpleBenchExample(false);
static SimpleBench frameBench(false);
static double lastFrameTimeMs = 0.f;

void Application::Initialize()
{
	Super::Initialize();

	// Split motivations into their correct lines
	const ea::string s = resMotivations.Data();
	ea::string::size_type last = 0;
	ea::string::size_type next = 0;
	while((next = s.find("\n", last)) != ea::string::npos)
	{
		motivations.push_back(s.substr(last, next - last));
		last = next + 1;
	}
}

void Application::DrawImGui(double deltaTime)
{
	Super::DrawImGui(deltaTime);

	frameBench.Start();

	// - SkeletonMinRes Example
	ImGui::SetNextWindowSize({ 600, 600 }, ImGuiCond_FirstUseEver);
	if(ImGui::Begin("Examples"))
	{
		// Tags: SkeletonMinRes, resources, embedding
		if(ImGui::CollapsingHeader("SkeletonMinRes Resource Embedding"))
		{
			ImGui::TextWrapped("The following text has been embedded into the application. SkeletonMinRes can be utilized to embed resources like binaries, glsl shaders, configuration files, scripts, etc.");

			static SkeletonMinRes::Resource resSampleDataJson = LOAD_RESOURCE(Data_sample_data_json);
			ImGui::TextWrapped("%s", resSampleDataJson.Data());

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			draw_list->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(90, 90, 120, 25));
		}

		// Tags: spdlog, logging, Logging.h
		if(ImGui::CollapsingHeader("Logging (with spdlog + Logging.h)"))
		{
			ImGui::TextUnformatted("Demonstrates spdlog library and Logging.h capabilities.");
			ImGui::TextUnformatted("See application console for output.");
			ImGui::TextUnformatted("Motivations read from embedded src/motivations.txt.");

			if(ImGui::Button("Motivations (raw spdlog call)"))
			{
				spdlog::info("{}", motivations[RandomNumber(0, (int)motivations.size())]);
			}

			if(ImGui::Button("Motivations (categorized)"))
			{
				logger->info("{}", motivations[RandomNumber(0, (int)motivations.size())]);
			}
		}

		if(ImGui::CollapsingHeader("Minimal and Simple Benchmarking (with SimpleBench.h)"))
		{
			ImGui::Text("Time taken to render this window: %.3fms", lastFrameTimeMs);
			ImGui::TextUnformatted("");

			if(ImGui::Button(simpleBenchExample.IsRunning() ? "Stop SimpleBench" : "Start SimpleBench"))
			{
				if(simpleBenchExample.IsRunning())
					simpleBenchExample.Stop();
				else
					simpleBenchExample.Start();
			}
			if(simpleBenchExample.IsRunning())
				ImGui::TextUnformatted("SimpleBench Running");
			else
				ImGui::Text("SimpleBench Time: %fms", simpleBenchExample.GetDurationInMs());
		}
	}
	ImGui::End();

	frameBench.Stop();
	lastFrameTimeMs = frameBench.GetDurationInMs();
}
