﻿#pragma once
#include <string>

#include "Component.h"
class FPSCounter : public Component
{
public:
	FPSCounter(GameObject* owner);
	~FPSCounter() override;

	FPSCounter(const FPSCounter& other) = delete;
	FPSCounter(FPSCounter&& other)noexcept = delete;
	FPSCounter& operator=(const FPSCounter& other) = delete;
	FPSCounter& operator=(FPSCounter&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;

	std::string GetFPSAsString() const;
	std::string GetFPSAsIntString();

private:
	void CalculateFPS();
	float m_currentFPS{ 0.f };
	std::string m_currentFPSString{ std::to_string(m_currentFPS) };
};
