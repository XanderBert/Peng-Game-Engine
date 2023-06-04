#pragma once
#include <functional>

#include "Component.h"

class ImGuiComponent : public Component
{
public:
	ImGuiComponent(GameObject* m_pOwner);
	virtual ~ImGuiComponent() override = default;

	ImGuiComponent(const ImGuiComponent& other) = delete;
	ImGuiComponent(ImGuiComponent&& other) noexcept = delete;
	ImGuiComponent& operator=(const ImGuiComponent& other) = delete;
	ImGuiComponent& operator=(ImGuiComponent&& other) noexcept = delete;

	void Update() override;
	void Render() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;


	bool IsActive() const { return m_IsActive; }
	void SetActive(bool active) { m_IsActive = active; }

	std::string GetWindowName() const { return m_WindowName; }
	void SetWindowName(const std::string& name) { m_WindowName = name; }

	void SetImGuiRenderFunction(const std::function<void()>& func) { m_ImGuiRenderFunction = func; }
	std::function<void()>& GetImGuiRenderFunction() { return m_ImGuiRenderFunction; }

private:
	bool m_IsActive = true;
	std::string m_WindowName = "ImGui Window";
	std::function<void()> m_ImGuiRenderFunction;

};