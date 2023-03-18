#include "CacheTestComponent.h"
#include "imgui_plot.h"

CacheTestComponent::CacheTestComponent(GameObject* owner) : Component(owner)
{
}

CacheTestComponent::~CacheTestComponent() = default;


void CacheTestComponent::Update()
{
}

void CacheTestComponent::FixedUpdate([[maybe_unused]]float fixedTimeStep)
{
}

void CacheTestComponent::LateUpdate()
{
}

void CacheTestComponent::Render()
{
	const std::string windowLabel{ "Cache Testing for " + m_ComponentName };
    ImGui::Begin(windowLabel.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	const std::string inputLabel{ "# Samples for  " + m_ComponentName };
    ImGui::InputInt(inputLabel.c_str(),&m_Samples,10);

	const std::string buttonLabel{ "Test " + m_ComponentName };
    if(ImGui::Button(buttonLabel.c_str(), { 200,25 }))
    {
		//Todo Put this in the update function?
		TestCacheComponent();
    }
	if(m_IsPlotable)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_XData.data();
		conf.values.count = m_Buffer;
		conf.values.ys = m_Timings.data();
		conf.values.ys_count = m_Buffer;
		conf.values.colors = m_PlotLineColors;
		conf.scale.min = 0;
		conf.scale.max = m_MaxTiming;
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.show = true;
		conf.grid_y.size = 50;
		conf.grid_y.subticks = 2;
		conf.selection.show = true;
		conf.selection.start = &selection_start;
		conf.selection.length = &selection_length;
		conf.frame_size = ImVec2(400, 200);
		Plot("Plot", conf);
	}
	
    ImGui::End();
}

void CacheTestComponent::TestCacheComponent()
{
	if (m_pComponentToTest == nullptr)
	{
		assert(false);
	}

	if(m_Samples == 0)
	{
		return;
	}

	//Make Big Vector of Components to Test
	std::vector<decltype(m_pComponentToTest)> components{};
	constexpr size_t dataSize{ 100000 };
	components.resize(dataSize);

	for (auto& component : components)
	{
		component = m_pComponentToTest;
	}

	//Set the amount of timings
	m_Timings.resize(m_Buffer);

	//Declare Start, Ending and elapsedTime
	std::chrono::time_point<std::chrono::steady_clock> start{}, end{};
	long long elapsedTime{};

	for (size_t iterator{}; iterator < m_Samples; ++iterator)
	{
		//Declaring index to put the right timing at the right place in the vector
		size_t index{};
		for (const auto& stepSize : m_XData)
		{
			//Start Timing
			start = std::chrono::high_resolution_clock::now();

			for (size_t i{0}; i < components.size(); i += static_cast<size_t>(stepSize))
			{
				//Doing something with the component to be sure it will be fetched
				const auto value = components[i];
				value;
			}

			//End Timing and Calculate ElapsedTime
			end = std::chrono::high_resolution_clock::now();
			elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_Timings[index] += elapsedTime;
			++index;
			index %= m_Samples;
		}
	}

	for (auto& timing : m_Timings)
	{
		//Calculating Average
		timing /= m_Samples;
	}

	m_IsPlotable = true;
	//Setting the highest time
	const auto& it = std::ranges::max_element(m_Timings.begin(), m_Timings.end());
	m_MaxTiming = *it;
}
