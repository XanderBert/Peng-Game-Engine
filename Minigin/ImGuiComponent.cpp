#include "ImGuiComponent.h"
#include "imgui.h"

ImGuiComponent::ImGuiComponent(GameObject* m_pOwner) : Component(m_pOwner)
{
}


void ImGuiComponent::Update()
{
}

void ImGuiComponent::Render()
{
	ImGui::Begin(m_WindowName.c_str());

	//Add A function Pointer right here so that the end user could just write a imgui function and it will be added here?
	//Then a seperate Gameobject will not be needed and the imgui will be per object what is is what i want
	if (m_ImGuiRenderFunction)
	{
		m_ImGuiRenderFunction();
	}

	ImGui::End();
}

void ImGuiComponent::FixedUpdate(float /*fixedTimeMStep*/)
{
}

void ImGuiComponent::LateUpdate()
{
}
