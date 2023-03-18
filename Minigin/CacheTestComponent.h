#pragma once
#include <chrono>
#include "Component.h"
#include "imgui.h"

class CacheTestComponent : public Component
{
public:
	CacheTestComponent(GameObject* owner);
	virtual ~CacheTestComponent() override;

	CacheTestComponent(const CacheTestComponent& other) = delete;
	CacheTestComponent(CacheTestComponent&& other)noexcept = delete;
	CacheTestComponent& operator=(const CacheTestComponent& other) = delete;
	CacheTestComponent& operator=(CacheTestComponent&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;

	template <typename T> void SetComponentToTest(T* pComponent);

private:
	std::vector<float> m_Timings{};
	std::vector<float> m_XData{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
	std::string m_ComponentName{};
	inline static ImU32 m_PlotLineColors [3] = {1255, 0 ,0};
	inline static uint32_t selection_start{};
	inline static uint32_t selection_length{};
	const int m_Buffer{static_cast<int>(m_XData.size())};
	float m_MaxTiming{};
	Component* m_pComponentToTest{nullptr};
	int m_Samples{10};
	bool m_IsPlotable{ false };


	void TestCacheComponent();
};

//You need to add the component you want to test to a game object because it needs an owner.
//You pass the classType as T and pass the object as parameter.
template<typename T>
inline void CacheTestComponent::SetComponentToTest(T* pComponent)
{
	static_assert(std::is_base_of<Component, T>(), "This class is not a component.");
	m_ComponentName = typeid(T).name();
	m_pComponentToTest = std::move(pComponent);
}


