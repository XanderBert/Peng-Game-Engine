#pragma once
#include <memory>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec1.hpp>

class GameActor;

class Controller final
{
public:
	explicit Controller(int controllerIndex);
	~Controller();

	Controller(const Controller& other) = delete;
	Controller(Controller&& other)noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other)noexcept = delete;

	enum class ControllerButton
	{
		DPadUp = 0x0001,
		DPadDown = 0x002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,

		Start = 0x0010,
		Back = 0x0020,

		LeftThumb = 0x0040,
		RightThumb = 0x0080,

		LeftShoulder = 0x0100,
		RightShoulder = 0x200,

		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	void Update();

	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;

	unsigned char GetbLeftTriggerValue() const;
	unsigned char GetbRightTriggerValue() const;

	glm::vec2 GetLeftThumbValue() const;
	glm::vec2 GetRightThumbValue() const;
	int GetControllerID() const;

	GameActor* GetGameActor() const;
	bool GetIsInUse() const;

private:
	class ControllerImpl;
	std::unique_ptr<ControllerImpl> pImpl{};
};

