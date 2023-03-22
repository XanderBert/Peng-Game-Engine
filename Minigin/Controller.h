#pragma once
#include <memory>

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
		ButtonA = 0x1000
	};

	void Update();

	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;

private:
	class ControllerImpl;
	std::unique_ptr<ControllerImpl> pImpl{};
};

